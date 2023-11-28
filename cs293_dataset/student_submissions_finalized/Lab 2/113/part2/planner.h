#include<iostream>
#include<string.h>
using namespace std;


#ifndef DICTIONARY_H
#define DICTIONARY_H

const int SIZE = 64; // maximum number of stations

//struct to define the journey
struct Journey {
  string start,finish;  //stores starting and ending values of a journey
  float start_time,finish_time;   //stores the starting and ending time of the journey
  
  Journey *next, *prev; //stores pointers to the previous and next journeys to this one as it appears while creating the planner
  
  //constructor
  //initializing to empty strings, NULL pointers and -1(not possible time) 
  Journey(){
    start = "";
    start_time = -1;
    finish = "";
    finish_time = -1;
    next = NULL;
    prev = NULL;
  }
};

//struct named Node to define a particular station which will contain all the journeys strating from there
struct Node{
  string start;   //storing the name of starting station
  Journey *head, *tail;   //implementing an double linked list to store all the journeys from this station
  int tag;    //tag to keep track whether the node is filled (1), empty(0), or deleted(-1)

  //constructor 
  //initializing tag to 0 as empty
  Node(){
    start = "";
    head = NULL;
    tail = NULL;
    tag = 0;
  }  
};

//class Planner to implement the time table of all the journeys and queries
class Planner{
 private:
  int N; // size of array A
  Node *A; // Array of stations i.e. Nodes

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(string key){

    //defining constants for hash value calculation using polynomial rolling hash
    const int PRIME = 37;   
    const int MOD = 10000007;

    //some variables to store the current calculations
    long int hash_val = 0;
    long int power_prime = 1;

    //loop of rolling hash
    int i=0;
    while (key[i]!='\0'){   
        hash_val = (hash_val + key[i]*power_prime)%MOD; //just equations of rolling hash
        power_prime = (power_prime*PRIME)%MOD;  //this variable just keeps track of power of prime to be multiplied but 
                                                //also takes modulus to prevent overflow
        i++;
    }

    hash_val = hash_val%N; //creating final hash value by taking modulus with max size of array
    return hash_val; 

  }

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(string key){
    int hash_val = hashValue(key);  //getting the hash value of the key
    int current_index = hash_val;   //creating an variable to store the possible free index

    while (A[current_index].tag == 1 && A[current_index].start != key){  //tag defines whether the place is deleted/empty or full
        current_index += 1; //until we reach an empty or deleted index or key match, increasing the index
        if (current_index == hash_val){ //if somehow index comes bach to the original hash value then no space left and so return -1
            return -1;
        }
    }

    return current_index;
  }
  
  // Default constructor
  Planner(){
    N = SIZE;
    A = new Node[N];
  } 

  // Return the node corresponding to given starting point, or NULL if the given station does not exist in the planner staring points
  Node *get(string start){

    int hash_val = hashValue(start);  //getting the hash value of the starting point
    int current_index = hash_val;   //creating an variable to store the possible free index

    while (A[current_index].tag != 0 && (A[current_index].start != start || A[current_index].tag == -1)){  //tag defines whether the place is deleted/empty
        current_index += 1; //until we reach an empty index or start station match (with tag != -1 i.e. it should not be a deleted node)
                            // or increasing the index
        if (current_index == hash_val){ //if somehow index comes bach to the original hash value then no space left and so return -1
            return NULL;
        }
    }

    if (A[current_index].tag == 0) //if tag reaches 0 means the starting point is not added hence no match found and returning null
      return NULL;

    return &(A[current_index]); //otherwise returning address of node where we stopped which will be having the given starting point

  }

  //adding a journey to the planner
  bool add(Journey *e){
    int index = findFreeIndex(e->start); // finding the place/index to add the journey
    if (index == -1){   //if the result is -1 then no space left and return false
      return false;
    }

    //if there are no elements stored in the linked list of given node then updating that node and linked list accordingly
    if (A[index].head == NULL){
      A[index].start = e->start;
      A[index].head = e;  //note that the journey pointer will be provided from outside 
      A[index].tail = e;
      A[index].tag = 1;
      return true;
    }

    //if the linked list alredy have some journeys stored then just add this new one at the tail
    ((A[index]).tail)->next = e;
    e->prev = (A[index]).tail;
    (A[index]).tail = e;
    return true;
  }

  //function to find an optimal journey (in terms of starting time) between two stations with given min start time
  void optimal_jrny(string start, float start_time, string finish){
    
    Node *n=get(start);   //finding the given starting point in the planner array A by get function
    
    if (n == NULL){ //if n is NULL then the station doesn't exist and so printing so
      cout << "No matches found" << endl;
      return;
    }

    Journey *j = n->head; // staring from head of linked list of journeys , we will go through all the journeys in that list 
    //and check for the given query

    //variables to store the current, i.e. most optimal, solution found
    string intermediate = "";//initializing these to out of bound values
    float opt_start = -1;
    float opt_leave = -1;
    float delay = 100000;

    while (j != NULL){ //loop to go through all the journeys from given starting point
      
      if (j->start_time >= start_time){ //we want time to be greater than the givenstart time
      
        if (j->finish == finish){   //if end point of journey matches then 
          if ((j->start_time - start_time) <= delay){   //checking if it is better than earlier solution in terms of delay time
            // if so then updating all the variables
            opt_start = j->start_time;
            delay = opt_start - start_time;
            opt_leave = -1;   //to specify that this is direct journey
            intermediate = "";
          }
        }
        else{

          //if finish point not same then going to the list of journeys starting from this finish point
          Node *m=get(j->finish); //getting the location/pointer of finishing station in array 
          
          //if null then continue the outer loop
          if (m == NULL){
            j = j->next;
            continue;
          }

          Journey *k = m->head; // creating new variable to store journeys of this second station  

          while (k != NULL){  //looping through all the values in this double linked list
            if (k->start_time >= j->finish_time){   //checking time constraint   
              if (k->finish == finish){   //checking whether final station is what is asked or not
                if ((j->start_time - start_time) < delay){    //if we find improvement in delay then just store these values to variables and then break
                  opt_start = j->start_time;
                  delay = opt_start - start_time;
                  opt_leave = k->start_time;
                  intermediate = j->finish;
                  break;
                }
                else if ((j->start_time - start_time) == delay){ //if the starting delay is same then checking for the leave time from next station
                  //if leave time of this is lower than previously stored value then update and break 
                  if (k->start_time < opt_leave){   //this won't override the direct journey if it was there because direct journey will have leave time -1
                    opt_start = j->start_time;
                    delay = opt_start - start_time;
                    opt_leave = k->start_time;
                    intermediate = j->finish;
                    break;
                  }  
                }
              }
            }
            k = k->next; //updating the loop  
          }
        }
      }
      j = j->next;  //updating the loop
    }

    //and finally printing the values carefully
    if (opt_start == -1){
      cout << "No Matches Found" << endl;
      return;
    }

    cout << opt_start << " ";
    if (opt_leave == -1){
      cout << endl;
      return;
    }
    cout << intermediate << " " << opt_leave << endl;
    return;
  }

  //function to print all the journeys from a particular station
  void station(string start, float start_time){
    Node *n = get(start); //finding the given start in planner array A by get function 

    //if not found then print error msg
    if (n == NULL){
      cout << "No Matches Found" << endl;
      return;
    }
    
    //then going through all the elements in the linked list and printing them based on time constraint given 
    int count = 0;
    Journey *j = n->head;
    while (j!=NULL){
      if (j->start_time >= start_time){
        cout << j->start_time << " " << j->finish << endl; 
        count ++;
      }
      j = j->next;
    }

    if ( count == 0 ){ // this means that no journey was found 
      cout << "No Matches Found" << endl;
    }
    return;
  }
};

#endif
