#include<iostream>
#include<string.h>
#ifndef DICTIONARY_H
#define DICTIONARY_H
// Can change this value for debugging
int DICT_SIZE = 64;

struct Entry {
  float starting_time;
  float ending_time;
  char starting_station[32];
  char ending_station[32];
  Entry(){
    starting_time =0;
    ending_time=0;
  }
  // define suitable fields here
};

class Dictionary {
 public:
  int N; // size of array A
  struct Entry *A; // Array of dictionary entries
 public:
  int hashValue(char starting_station[32]);
  Dictionary(); 
  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e);
};

#endif
