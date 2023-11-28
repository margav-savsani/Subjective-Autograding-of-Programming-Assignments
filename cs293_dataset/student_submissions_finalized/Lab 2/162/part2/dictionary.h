#include<string.h>
#include "circularQueue.cpp"


#ifndef DICTIONARY_H
#define DICTIONARY_H


// Can change this value for debugging
int DICT_SIZE = 64;



struct Entry {
  // define suitable fields here
  char stationName[32] = "NULL";
  DynamicQueue journeys;
};

class Dictionary {
 private:
  int N; // size of array A
  struct Entry *A; // Array of dictionary entries
  
 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char stationName[]);

  // Find the position where given stationName can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char stationName[]);
  
  // Default constructor
  Dictionary(); 

  // Return the entry corresponding to given stationName, or NULL if the given stationName does not exist in the dictionary
  struct Entry *get(char stationName[]);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e);

  // Remove the given stationName; return true if success, false if failure (given stationName not present)
  bool remove(char stationName[]);
};


#endif