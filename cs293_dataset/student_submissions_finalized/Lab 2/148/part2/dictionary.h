#include<iostream>
#include<string.h>

#include <limits>
#include "planner.h"
#ifndef DICTIONARY_H
#define DICTIONARY_H


// Can change this value for debugging
const int DICT_SIZE = 64;

struct Entry {
  // define suitable fields here
 string key;
 Station *value;

 Entry(){
         // value = nullptr signifies empty value, without tombstone
         value = nullptr;
 }

 Entry(Station *s){
    value = s;
    key = s->name;
 }

 ~Entry(){
    delete value;
 }
};

class Dictionary {
 private:
  int N; // size of array A
  struct Entry *A; // Array of dictionary entries

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(string key);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(string key);
  
  // Default constructor
  Dictionary(); 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(string key);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Station* s);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(string key);

  ~Dictionary(){
    delete[] A;
  }
};

#endif
