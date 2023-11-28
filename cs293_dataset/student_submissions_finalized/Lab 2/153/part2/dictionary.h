#include<iostream>
#include<string.h>
#include<math.h>
#include <stdlib.h>

#include "planner.h"
// #include "queue.h"
#include "structures.h"

#ifndef DICTIONARY_H
#define DICTIONARY_H


// Some constants which define the procedures of the dictionary
int DICT_SIZE = 64;

const double FIB_MULT = (sqrt(5)-1)/2;
const int VAL_TOMBSTONE = -314159;
const int VAL_NULL = 314159;

struct Entry {
  // define suitable fields here
  char* key = (char*) malloc(KEY_MAX_LENGTH);
  int value = VAL_NULL;
  // DynamicQueue<Journey> journeyQueue;
  Journey* journey_queue = (Journey *) malloc(128*sizeof(Journey));
  int journey_index=0;
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

  ~Dictionary(){
    delete A;
  }

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(char key[]);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]);

  //A getter for the array (majorly for testing purposes)
  Entry* getDictArray(){
    return A;
  }
};

#endif
