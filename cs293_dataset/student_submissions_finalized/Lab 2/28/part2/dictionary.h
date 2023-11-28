#include<iostream>
#include<math.h>
#include<string.h>
using namespace std;


#ifndef DICTIONARY_H
#define DICTIONARY_H


// Can change this value for debugging
int DICT_SIZE = 64;

struct Entry {   //Journeys
  // define suitable fields here
  char station1[32];
  float starttime;
  float finishtime;
  char station2[32];

};

class Dictionary {
 private:
  int N; // size of array A
  //struct Entry *A; // Array of dictionary entries

 public:

  struct Entry *A; // Array of dictionary entries
  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char station1[]);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char station1[]);
  
  // Default constructor
  Dictionary(); 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(char station1[]);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char station1[]);
  struct Entry * findpath(char station1[],char station2[],float t);
  void print(char station[],float t);
  struct Entry * gett(char station1[],float t);
  
};

#endif
