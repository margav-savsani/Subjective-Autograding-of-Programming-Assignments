#include<iostream>
#include<string.h>
#include"circularQueue.cpp"


#ifndef DICTIONARY_H
#define DICTIONARY_H



int DICT_SIZE = 640;
template <typename T>
struct Entry {
  T value;
  char key[32];
  bool IS_TUMBSTONE = false;
  // define suitable fields here
};

template<typename T>
class Dictionary {
 private:
  int N; // size of array A
  struct Entry<T> *A; // Array of dictionary entries

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]);
  
  // Default constructor
  Dictionary(); 
  ~Dictionary(){delete[]A;}

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry <T> *get(char key[]);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry<T> e);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]);
};

#endif
