#ifndef DICTIONARY_H
#define DICTIONARY_H

#include<iostream>
#include<string.h>


// Can change this value for debugging
int DICT_SIZE = 64;

template <typename T> class Dictionary {
 private:
  int N; // size of array A
  T *A; // Array of dictionary entries

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]);

  // Find the position where given key can be inserted or already present (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findIndex(char key[]);

  // Default constructor
  Dictionary();

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  T *get(char key[]);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(char key[]);

};

#endif
