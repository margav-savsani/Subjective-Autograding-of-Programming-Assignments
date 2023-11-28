#include<iostream>
#include<string.h>
#include "planner.h"


#ifndef DICTIONARY_H
#define DICTIONARY_H


// Can change this value for debugging
int DICT_SIZE = 100;

template <typename T> struct Entry{
    std::string key;
    int marker = -1; // Marker is 1 if this entry is in Dict (occupied), 0 if this was deleted (tombstone), -1 if never added (null).
    T element;
};

template <typename T> class Dictionary {
 private:
  int N; // size of array A
  

 public:

  struct Entry<T> *A; // Array of dictionary entries
  
  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(std::string key);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(std::string key);
  
  // Default constructor
  Dictionary(); 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  Entry<T> *get(std::string key);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(Entry<T> e);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(std::string key);
};

#endif