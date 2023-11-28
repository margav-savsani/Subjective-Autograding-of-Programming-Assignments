#include "dictionary.h"
#include <cmath>
// #include <iostream>
using namespace std;

const double a = 0.618;
int Dictionary::hashValue(char stationName[])
 {
    double x = 33.0;
    double *intPart = new double; // never
    double res = modf(stationName[0] * a,intPart);
    
    for (int i = 1; stationName[i] != '\0'; i++)
    {   
        // cout<<res<<endl;
        res = modf(res*x + stationName[i]*a,intPart);
        
    }
    res = DICT_SIZE * res;
    // cout<<res<<endl;
    return res;
    
 }

  // Find the position where given stationName can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int Dictionary::findFreeIndex(char stationName[])
  { 
    if(N == DICT_SIZE) return -1; 
    int actualIndex = hashValue(stationName);
    int j = actualIndex;
    // cout<<j<<endl;
    // cout<<strcmp(A[j].stationName,"NULL")<<endl;
    while(strcmp(A[j].stationName,"NULL") !=0 && strcmp(A[j].stationName,"TOMBSTONE") !=0)
    { 
      // std::cout<<"inhere"<<std::endl;
      j = (j+1)%DICT_SIZE;
    }

    return j;

    
  }
  
  // Default constructor
  Dictionary::Dictionary()
  { 
    N = 0;
    A = new struct Entry[DICT_SIZE];
  }; 

  // Return the entry corresponding to given stationName, or NULL if the given stationName does not exist in the dictionary
  struct Entry * Dictionary::get(char stationName[])
  {
      int actualIndex =  hashValue(stationName);
      int j = actualIndex;

      while (strcmp(A[j].stationName,stationName) != 0)
      { 
        if(strcmp(A[j].stationName,"NULL") == 0) return NULL;
        j = (j+1)%DICT_SIZE;
        
      }
      return &A[j];
      

  }

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool Dictionary::put(struct Entry e){

    char stationName[32];
    strcpy(stationName, e.stationName);
    int freeIndex = findFreeIndex(stationName);
    if(freeIndex == -1) return false;
    A[freeIndex] = e;
    return true;

  }

  // Remove the given stationName; return true if success, false if failure (given stationName not present)
  bool Dictionary::remove(char stationName[])
  { 

    Entry* entry = get(stationName);
    if(entry == NULL) return false;

    strcpy(entry->stationName,"TOMBSTONE");
    return true;
    
  }