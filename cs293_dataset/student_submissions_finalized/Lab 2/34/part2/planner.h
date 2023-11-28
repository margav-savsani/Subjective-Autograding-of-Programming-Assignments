#include<iostream>
#include<string.h>
#include<cmath>

#ifndef PLANNER_H
#define PLANNER_H

using namespace std;

//Total size of dictionary.Here it is journey
int DICT_SIZE = 64;
//Query_journey error time;
int error_time = 100000;

struct Station {
  // define suitable fields here
  char* station;
  Station(){
    station = NULL;
  }
};

struct Journey {
  // define suitable fields here
  char *start;
  char *end;
  int time_start;
  int time_end;
  char* key;
  Journey(){
    key = NULL;
    start = nullptr;
    end = nullptr;
    time_start = -1;
    time_end = -1;
  }
};

struct Query{
  // define suitable fields here
  int time;
  char* intermediate;
  int intermediate_time;
  Query(){
    time = error_time;
    intermediate = NULL;
    intermediate_time = error_time;
  }
};

class Planner {
  // define suitable fields here
  private:
    int N;
    struct Journey *A;
  public:
    //Constructor
    Planner();

    // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
    int hashValue(char key[]);

    // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
    int findFreeIndex(char key[]);

    //To return a struct Query with time , intermediate station, intermediate time and if station not found then return struct Query with error time
    int query_journey(string key, string end_journey, int start_time, bool intermediate);

    //To print all the start time of station provided 
    bool query_station(char key[], int check_start);
    
    // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
    bool put(struct Journey e);

    //To compare two char arrays
    bool compare(string a, string b);

    void show(){
      for(int i = 0; i < N; i++){
        if(A[i].key != NULL)
          cout << "show : " << i << " " << A[i].start << " " << A[i].time_start << " " << A[i].end << " " << A[i].time_end << "\n";
      }
    }
};

#endif