#include<iostream>
#include<string.h>


#ifndef DICTIONARY_H
#define DICTIONARY_H


// Can change this value for debugging
int DICT_SIZE = 64;

struct Path {
  // define suitable fields here
  char start[32];
  float stime;
  char dest[32];
  float ftime;
};

struct Entry {
  // define suitable fields here
  int cap;
  int len;
  char key[32];
  Path p[64];
  Entry(){cap=0;len=0;} 
};



class Dictionary {
 private:
  

 public:
  int N; // size of array A
  struct Entry A[64];// Array of dictionary entries
  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[32]);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[32]);
  
  // Default constructor
  Dictionary(); 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  int get(char key[32]);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Path pt);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[32]);
};

#endif
