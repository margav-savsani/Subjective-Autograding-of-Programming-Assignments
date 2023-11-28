#include<iostream>
#include<string.h>
#include "planner.h"

#ifndef DICTIONARY_H
#define DICTIONARY_H


// Can change this value for debugging
int DICT_SIZE = 64;

/*struct Entry {
  char key[32];
  int value;
  int TOMBSTONE;


};*/



class Dictionary {
 private:
  int N; // size of array A
  

 public:
  Journey *A;

  int hashValue(char key[]);
  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]);
  
  // Default constructor
  Dictionary(); 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Journey *get(char key[]);

  int getTrains(char key[]);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Journey e);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]);
};

#endif
