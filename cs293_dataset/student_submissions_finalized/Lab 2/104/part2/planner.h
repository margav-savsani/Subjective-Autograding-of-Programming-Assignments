#include<iostream>
#include<string.h>
using namespace std;

#ifndef PLANNER_H
#define PLANNER_H

// Can change this value for debugging
const int DICT_SIZE = 64;
const int ARR_SIZE = 100;
const int ARR_INCR = 100;

// function to compare floats
bool floatCmp(float f1, float f2){
    const float eps = 10e-8;

    return(abs(f1-f2)<eps);
}

// to store a journey
struct Destination {
  char dest[32];
  float deptTime;
  float arrTime;

  
  Destination(char d[], float t1, float t2){
    strcpy(dest, d);
    deptTime = t1;
    arrTime = t2;
  }

  Destination(){};
};


// to store list of journeys from a particular station
struct Departures {
  Destination* ptr;
  int size;
  int arrSize;

  Departures(){
    ptr = new Destination[ARR_SIZE];
    size = 0;
    arrSize = ARR_SIZE;
  }

  // search a journey with departure time equal or greater than specified time
  int search(float t){
    for(int i=0; i<size; ++i){
      if(floatCmp(ptr[i].deptTime, t) || ptr[i].deptTime>t){
        return i;
      }
    }
    return size;
  }

  // insert a journey to list
  void insert(float t1, char d[], float t2) {
    int indx = search(t1);
    Destination toInsert(d, t1, t2);

    // if array is full then grow the array
    if(size == arrSize){
      Destination* newPtr = new Destination[arrSize+ARR_INCR];
      for(int i=0; i<size; ++i){
        newPtr[i].deptTime = ptr[i].deptTime;
        newPtr[i].arrTime = ptr[i].arrTime;
        strcpy(newPtr[i].dest, ptr[i].dest);
      }

      delete [] ptr;
      ptr = newPtr;
      arrSize += ARR_INCR;
    }

    for(int i=size; i>indx; --i){
      ptr[i].deptTime = ptr[i-1].deptTime;
      ptr[i].arrTime = ptr[i-1].arrTime;
      strcpy(ptr[i].dest, ptr[i-1].dest);
    }

    ptr[indx].deptTime = t1;
    ptr[indx].arrTime = t2;
    strcpy(ptr[indx].dest, d);

    size++;

  }


};

//  entries for dictionary
struct Entry {
  // define suitable fields here
  char key[32];
  Departures value;
  int isFNT; // is Filled(0) or Null(1) or Tomb(2)

  Entry() {
    isFNT = 1;
  }
};

class Dictionary {
 private:
  int N; // size of array A
  struct Entry *A; // Array of dictionary entries

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]);
  
  // Default constructor
  Dictionary(); 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(char key[]);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]);

  ~Dictionary();
};

// planner for journies
class Planner {
  Dictionary Stations;

  public:
    void add(char st1[], float t1, char st2[], float t2);
    void query_station(char st[], float t);
    void query_journey(char st1[], float t, char st2[]);
};

#endif