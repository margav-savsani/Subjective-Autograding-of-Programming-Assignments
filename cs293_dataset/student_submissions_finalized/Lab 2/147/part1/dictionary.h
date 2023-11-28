#include<iostream>
#include<string.h>

#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "journey.h"

using namespace std;

// Can change this value for debugging
#define DICT_SIZE 64
#define MAX_JOURNEYS 16  

struct Entry {
  char key[MAXLEN];
  Journey value[MAX_JOURNEYS];
  int num_journeys;
  bool isTomb; // to check if this Entry is a tombstone.
  bool isEmpty; // to indicate unoccupied.
  Entry(): isTomb(false), isEmpty(true){}
  Entry(Journey &journey): isTomb(false), isEmpty(true), num_journeys(1){
      strcpy(key, journey.getstart());
      value[0] = journey;
  }
  bool add(const Journey &journey){
      if (num_journeys >= MAX_JOURNEYS) return false;
      value[num_journeys++] = journey;
      return true;
  }
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

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(char key[]);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry &e);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]);

  // void print(){
  //   cout << A[4].key << endl;
  //   for (int i = 0; i < N; i++){
  //     std::cout << A[i].key << " " << " " << A[i].isEmpty << " " << A[i].isTomb << std::endl;
  //   }
  // }
};

#endif
