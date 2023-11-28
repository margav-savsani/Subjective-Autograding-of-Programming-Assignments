#include<iostream>
#include<string.h>

#ifndef DICTIONARY_H
#define DICTIONARY_H


// Can change this value for debugging
int DICT_SIZE = 64;

struct Entry {   
  char *key ;      // define suitable fields here
  Entry(){
    key = new char[32] ;
  }
};

class Dictionary {
 private:
  int N; // size of array A
  struct Entry *A; // Array of dictionary entries
  
 public:
   int index[N] ;

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]);
  
  // Default constructor
  Dictionary(){
    for(int y=0;y<32;y++){
      index[y] = 0 ;
    }
  }
  

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(char key[]);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]);
};

#endif
