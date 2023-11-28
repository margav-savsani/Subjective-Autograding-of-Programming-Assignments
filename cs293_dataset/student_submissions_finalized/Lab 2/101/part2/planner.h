#include<vector>
#include<iostream>
#include <string.h>

#ifndef DICTIONARY_H
#define DICTIONARY_H


//This file contains the declaration of dictionary and other structs and classes.

int DICT_SIZE = 64;

struct Journey {                                              //Journey Struct - Stores all info about the journey
  char StationStart[32];
  char StationEnd[32];
  int TimeStart;
  int TimeEnd;
  Journey(char* SS, int TS , char* SE, int TE){
      for(int i = 0 ; i < 32 ; i++){
        StationStart[i]=SS[i];
        StationEnd[i]=SE[i];
      }
      TimeStart = TS;
      TimeEnd = TE;
  }
};

struct Entry {                                                //0 when key is not assigned, 1 when it is assigned, -1 when it's deleted
    std::vector<struct Journey> value;
    char key[32];
    bool is_tomb; 
    bool is_assigned;
  
    Entry(){
      is_tomb = false;
      is_assigned = false;
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