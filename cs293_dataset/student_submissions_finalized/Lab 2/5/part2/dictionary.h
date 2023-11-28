#include<iostream>
#include<string.h>
#include <climits>
#include <vector>
#include "Journey.h"
using namespace std;

#ifndef DICTIONARY_H
#define DICTIONARY_H


// Can change this value for debugging
const int DICT_SIZE = 64;


class Dictionary {
 private:
  int N; // size of array A
  struct Journey *A; // Array of dictionary journeys

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]);
  
  // Default constructor
  Dictionary(); 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  vector<struct Journey*> get(char key[]);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Journey j);
  
};

#endif
