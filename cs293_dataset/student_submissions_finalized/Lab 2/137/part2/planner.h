#ifndef PLANNER_H
#define PLANNER_H
#include<cmath>
#include<iostream>
using namespace std;

int INIT_SIZE = 64;

struct Station {
//Structure for stations
  char B[32] = {0};
};

struct Journey {
//Structure for train journey
  struct Station s1,s2;
  float start_time=0, finish_time=0; 
  int value=0;
};

struct Query{
//Structure to store query items
  struct Station s;
  float start_time=0, finish_time=0;
  
};

class Planner {
  private:
    int N; // size of array A
    struct Journey *A; // Array of dictionary entries

  public:
    Planner(){
    //Default constructor to initialise class elements 
      N = INIT_SIZE;
      A = new Journey[N];
      for(int i = 0; i<N; i++)
      {
        struct Journey a;
        A[i] = a;  
      }
    }

    int hashValue(char key[]){
    //Function to compute hash value 
    int i = 0;
    float k=0, x=3, a=(sqrt(5)-1)/2;
    while(key[i] != NULL)
    {
      k = k + a*pow(x,i)*key[i] - int(a*pow(x,i)*key[i]) ;
      i++;
    }
    k = N*(k - int(k));
    return k;
  }

  int findFreeIndex(char key[]){
  //Function to find free index
    int y = hashValue(key);
    int temp = y;
    while(true)
    {
      if(strcmp(A[y].s1.B, "\0") == 0)                              //Checking for free index
      {
        break;
      }
      y = (y+1)%N;
      if(y==temp)
      {
        y = -1;
        break;
      }
    }
    return y;
  }

  bool put(struct Journey e){
  //Function to insert elements into the dictionary
    int k = findFreeIndex(e.s1.B);
    if(k == -1)
    {
      return false;
    }
    else
    {
      strcpy(A[k].s1.B, e.s1.B);                                   //Inserting elements
      strcpy(A[k].s2.B, e.s2.B);
      A[k].start_time = e.start_time;
      A[k].finish_time = e.finish_time;
      A[hashValue(e.s1.B)].value++;
      return true;
    }
  }

  void query_station(char key[] , struct Query* &E, int &count, float start=0){
  //Function to output station schedule
    int y = hashValue(key);
    int value = A[y].value;
    E = new Query[value];                                         //Initialising the query array
    count = 0;
    while (true)
    {
      if(strcmp(A[y].s1.B, key) == 0 && A[y].start_time > start)     //Checking for station
      {
        E[count].start_time = A[y].start_time;                       //Reinitialising query array with current station elements
        strcpy(E[count].s.B , A[y].s2.B);
        E[count].finish_time = A[y].finish_time;
        value--;
        count++;
      }
      y = (y+1)%N;
      if(value == 0 || y == hashValue(key))
      {
        break;
      }
    }
    for(int i=0; i<count; i++)                                       //Sorting the query array with asceding time
    {
      for(int j=0; j<count - i - 1; j++)
      {
        if(E[j].start_time > E[j+1].start_time)
        {
          struct Query temp;
          temp.start_time = E[j+1].start_time;
          temp.finish_time = E[j+1].finish_time;
          strcpy(temp.s.B, E[j+1].s.B);
          E[j+1].start_time = E[j].start_time;
          E[j+1].finish_time = E[j].finish_time;
          strcpy(E[j+1].s.B, E[j].s.B);
          E[j].start_time = temp.start_time;
          E[j].finish_time = temp.finish_time;
          strcpy(E[j].s.B , temp.s.B); 
        }
      }
    }
    return;
  }

  int query_journey(char key1[], float start, char key2[], char *outkey, float &start1, float &start2){
  //Function to get train journey details between 2 stations
    int count1 = 0;
    struct Query *E1;
    int count2 = 0;
    struct Query *E2;
    query_station(key1, E1, count1, start);                  //Getting the station schedule of first station
    for(int i=0; i<count1; i++)
    {
      if(strcmp(E1[i].s.B,key2) == 0)                        //Checking if the nearest train has direct connection to the destination
      {
        start1 = E1[i].start_time;
        return 0;
      }
      else
      {
        query_station(E1[i].s.B, E2, count2, E1[i].start_time);      //Getting station schedule of the intermediate station
        for(int j=0; j<count2; j++)
        {
          if(strcmp(E2[j].s.B,key2) == 0)                            //Checking if it has connection to the specified destination 
          {
            if(E1[i].finish_time>E2[j].start_time)                   //Checking for time constraint
            {
              return 1;
            }
            start1 = E1[i].start_time;
            strcpy(outkey, E1[i].s.B);
            start2 = E2[j].start_time;
            return 2;
          }
        }
      }
    }
    return 3;
  }
};

#endif