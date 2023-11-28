#ifndef PLANNER_H
#define PLANNER_H
#include <iostream>
using namespace std;
#include "planner.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include <vector>
#include <cmath>

const int DICT_SIZE = 64;
const double FIB = (sqrt(5) - 1) / 2;

struct Dest {
  Dest *next;
  Dest *prev;
  char dest_name[32];
  float start_time;
  float finish_time;
  Dest(Dest *n, Dest *p, char name[], float st, float ft){
    next = n;
    prev = p;
    strcpy(dest_name, name);
    start_time = st;
    finish_time = ft;
  }
};

struct Station {
  // define suitable fields here
  Station *next;
  Station *prev;
  char source_name[32];
  Dest *head;
  Dest *tail;
  Station(){
    next = NULL;
    prev = NULL;
    head = NULL;
    tail = NULL;
  }

  Station(Dest *h, Dest *t, char name[], Station *n, Station *p){
    next = n;
    prev = p;
    head = h;
    tail = t;
    strcpy(source_name, name);
  }
};

struct Hash_Node{
  Station *head;
  Station *tail;
  Hash_Node(){
    head = NULL;
    tail = NULL;
  }
};

struct Journey {
  // define suitable fields here
  float start;
  char intermediate[32];
  float leave_time;
  Journey(){
    start = 2500;
    leave_time = 2500;
  }
};

struct Query{
  // define suitable fields here
  char destination[32];
  float starttime;

  //Will be used to point the next element in the queue in which this node will be added
  Query * next;

  //Will be used to free up the memory after deletion of the node
  Query * prev;
  Query(char name[], float time){
    strcpy(destination, name);
    starttime = time;
    next = NULL;
    prev = NULL;
  }
};

class query_queue{
  //For removing the query results
  Query * head;

  // For adding the new query results
  Query * tail;
  int length;
  public:
  query_queue(){
    head = NULL;
    tail = NULL;
    length = 0;
  }

  void remove(){
    if(length > 0){
      if (length == 1){
        delete head;
        head = NULL;
        tail = NULL;
        length = 0;
        return;
      }
      head = (*head).next;
      delete (*head).prev;
      (*head).prev = NULL; //this was giving error as we were trying to get back info from null(when we enter with length as 1), lmao
      length -= 1;
    }
  }

  void add(char name[], float time){
    //Making the new node that is to be added in the queue
    Query *node = new Query(name, time);

    //Adjusting the tail pointer and next pointer of the tail to make sure queue is well connected
    (*node).prev = tail;
    if (length == 0){
      head = node;
    }
    else{
      (*tail).next = node;
    }
    tail = node;
    length += 1;
  }

  Query * get_head(){
    return head;
  }

  Query * get_tail(){
    return tail;
  }

  int get_length(){
    return length;
  }
};

class Planner {
  // define suitable fields here
  Hash_Node *junction;
  public:
  Planner(){
    junction = new Hash_Node[DICT_SIZE];
  }

  //To compute Hash Value of any given key
  int hashValue(char key[]){
    double t = 0, p = 0;
    if (key[0] != '\0'){
        t += (int(key[0])*FIB);
        int i = 1;
        int x = 37;
        while(key[i] != '\0'){
            t = (modf(((modf(t,&p))*x),&p)) + modf(modf((int(key[i])*FIB),&p),&p);
            i += 1;
        }
        t = modf((modf(t,&p)*x),&p);
    }
    return int(floor(t*DICT_SIZE));
  }

  //Add function implementation
  void add(char source[], float start, char destin[], float finish){
    //Finding the hash value of the source station 
    int hashV = hashValue(source);
 
    //Creating a variable pointer to find the location of the source station in the linked list attached \
    at each junction
    Station *s_p;

    //s_p is our station pointer, we would like to start our search from head of the linked list
    s_p = junction[hashV].head;

    //As we will anyhow need our destination node, lets make it now only
    Dest *d = new Dest(NULL,NULL, destin, start, finish);

    while(s_p != NULL){
      if(strcmp((*s_p).source_name, source) == 0){
        //If node of station was already present,
        //Added the destination to the tail of station and modified the tail of the station
        (*d).prev = (*s_p).tail;

        //Done to make sure last element before addition makes a continuous link
        (*((*s_p).tail)).next = d;
        (*s_p).tail = d;

        //Once addition is done, escape the loop, to avoid infinite checking
        break;
      }
      else{
        s_p = (*s_p).next;
      }
    }

    //Since we couldn't find station source name yet in linked list, lets add it, and also since this source station\
    is being added for the first time, its head and tail would point to the same destination station 
    s_p = new Station(d, d, source, junction[hashV].tail, NULL);

    //Checking if the junction for that particular hash value have some member already or not
    //If not, then head and tail for now, would point at the same station
    if (junction[hashV].head == NULL){
      junction[hashV].head = s_p;
    }
    else (*(junction[hashV].tail)).next = s_p;
    junction[hashV].tail = s_p;
  }

  // Query Function Implementation
  // For now let's print the result of query function
  query_queue * query(char start[], float time){
    //First let's go the start station linked list by finding it's hash value index
    int hashV = hashValue(start);

    //In the linked list attached to that junction, we need to find the station
    Station *s_p;
    s_p = junction[hashV].head;
    //Making a query queue to store the results
    query_queue *q = new query_queue;

    while(s_p != NULL){
      if (strcmp((*s_p).source_name, start) == 0){
        //If station found
        // We need a destination pointer, to go through the entire linked list of trains\
        departing the given station and find those stations for whol the train does depart after \
        the given start time
        Dest *d_p;
         
        // We will start at the head of the linked list
        d_p = (*s_p).head;

        //Let's iterate through all the destination stations
        while(d_p != NULL){
          if ((*d_p).start_time >= time){
            //Correct train found, let's do what we need to do with this info
            (*q).add((*d_p).dest_name, (*d_p).start_time);
          }
          // Keep looking for more trains, by moving to the next station pointer
          d_p = (*d_p).next;
        }

        // found_any variable was created to just print the correct output as to any train was found or not
        if ((*q).get_length() == 0){
          cout << "ERROR" << endl;
        }
        return q;
      }
      else{
        s_p = (*s_p).next;
      }
    }
    cout << "ERRor" << endl;
    return q;
  }

  Journey * query_journey(char source[], float start, char dest[]){
    int hashV = hashValue(source);

    //In the linked list attached to that junction, we need to find the station
    Station *s_p;
    s_p = junction[hashV].head;

    //Making a journey object to store the results
    Journey *j = new Journey;

    while(s_p != NULL){
      if (strcmp((*s_p).source_name, source) == 0){
        //If station found
        // We need a destination pointer, to go through the entire linked list of trains\
        departing the given station and find those stations for whol the train does depart after \
        the given start time
        Dest *d_p;
         
        // We will start at the head of the linked list
        d_p = (*s_p).head;

        //Let's iterate through all the destination stations
        while(d_p != NULL){
          if ((*d_p).start_time >= start){
            //Reached a start time for which atleast start time condition matches

            //First let's check if this is the final destination station
            if (strcmp((*d_p).dest_name, dest) == 0){
              if ((*d_p).start_time < (*j).start){
                (*j).start = (*d_p).start_time;
                //Not changing the leave time as it is of no concern to us
              }
              d_p = (*d_p).next;
              continue;
            }

            //Below few lines of code are similar to the query function, but since we do need error messages\
            we have copied that few lines here to avoid unnecessary output
            int hashVV = hashValue((*d_p).dest_name);

            Station *s_pp;
            s_pp = junction[hashVV].head;
  
            query_queue *q = new query_queue;
            while(s_pp != NULL){
              if (strcmp((*s_pp).source_name, (*d_p).dest_name) == 0){
                Dest *d_pp;
                d_pp = (*s_pp).head;
                while(d_pp != NULL){
                  if ((*d_pp).start_time >= (*d_p).finish_time){
                    (*q).add((*d_pp).dest_name, (*d_pp).start_time);
                  }
                  d_pp = (*d_pp).next;
                }
                break;
              }
              else{
                s_pp = (*s_pp).next;
              }
            }
            // We have in above block found all the trains leaving the intermediate station after the \
            reaching time of first train starting from source


            //Here we check if satisfying this timing constraint is there any train which can take us to our\
            destination
            while((*q).get_length() != 0){
              Query *val = (*q).get_head();
              if (strcmp((*val).destination, dest) == 0){
                if ((*d_p).start_time < (*j).start){
                  (*j).start = (*d_p).start_time;
                  strcpy((*j).intermediate, (*d_p).dest_name);
                  (*j).leave_time = (*val).starttime;
                }
                break;
              }
              (*q).remove();
            }
          }
          // Keep looking for more trains, by moving to the next station pointer
          d_p = (*d_p).next;
        }

        // found_any variable was created to just print the correct output as to any train was found or not
        if ((*j).start == 2500){
          cout << "ERROR" << endl;
        }
        return j;
      }
      else{
        s_p = (*s_p).next;
      }
    }
    cout << "ERROR" << endl;
    return j;
  } 
};

#endif