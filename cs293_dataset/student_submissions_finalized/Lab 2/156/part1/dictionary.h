#include<iostream>
#include<string.h>

using namespace std;

#ifndef DICTIONARY_H
#define DICTIONARY_H


// Can change this value for debugging
int DICT_SIZE = 64;

struct Entry {
  // define suitable fields here
  public:
    char key[32];//station name
    //char* gives segfault (geeks for geeks)
    //specify size else is giving errors
    float value;//time
    //let time 2500 act as a null pointer and 2600 act as a tombstone , but to avoid any clashes just write code
    //to give error if anything greater than 2400 is added as time
    //For inlab null=0 and tombstone=-1 considering those values aren't allowed
    Entry(){
      value = 0;
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
  bool put(struct Entry e);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]);
};


#endif
