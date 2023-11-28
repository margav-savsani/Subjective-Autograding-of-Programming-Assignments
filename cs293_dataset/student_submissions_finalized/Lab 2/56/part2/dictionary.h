#include<iostream>
#include<string.h>


#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "planner.h"
// Can change this value for debugging
int DICT_SIZE = 64;

/*struct Entry {
  // define suitable fields here
  int value;
  char key[32];
  char id;  //0 if empty, -1 if tombstone, 1 if filled

};*/

class Dictionary {
 private:
  int N; // size of array A
  //struct Entry *A; // Array of dictionary entries
  struct Station* A;
 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]);
  
  // Default constructor
  Dictionary(); 

  // Return the station corresponding to given name, or NULL if the given key does not exist in the dictionary
  struct Station* get(char key[]);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Station e);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]);
};

#endif
