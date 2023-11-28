#include<iostream>
#include<string.h>


#ifndef PLANNERHELP_H
#define PLANNERHELP_H


// Can change this value for debugging
int DICT_SIZE = 64;

struct Station{
  
	char name[32];
	float time;
  Station* end;
  Station* start;
  bool isStart;
};

class Dictionary {
 private:

  int N; // size of array A
  struct Station *A; // Array of dictionary entries
  //struct Station *EndStation;
 public:
  // Default constructor
  Dictionary();
 
  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]);

  // Find the position where given key can be insertetd (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]);
  


  // Return the Station corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Station *getStart(char key[]);
  
  struct Station *getEnd(char key[]);

  void giveStart(char name[], Station* start);
  void giveEnd(char name[],Station* end);

  // Put the given Station in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Station e);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]);
};

#endif
