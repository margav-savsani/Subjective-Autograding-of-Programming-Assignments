#include<iostream>
#include<string.h>


#ifndef DICTIONARY_H
#define DICTIONARY_H


// Can change this value for debugging
int DICT_SIZE = 64;

struct Journey {
  // define suitable fields here
  char station1[30];
  char station2[30];
  float start;
  float finish;
  void dump(const char* action){ // prints relevant details of train according to the specific query
    if(strcmp(action, "QUERY_STATION") == 0){
      std::cout << start << " " << station2 << std::endl;
    }
    else if(strcmp(action, "QUERY_JOURNEY_NO_STOP") == 0){
      std::cout << start << std::endl;
    }
    else if(strcmp(action, "QUERY_JOURNEY_STOP_0") == 0){
      std::cout << start << " " << station2 << " ";
    }
    else if(strcmp(action, "QUERY_JOURNEY_STOP_1") == 0){
      std::cout << start << std::endl;
    }
    else{ // present just for debugging
      std::cout << station1 << " " << start << " " << station2 << " " << finish << std::endl;
    }
  }
};

struct Entry {
  // define suitable fields here
  char *key;
  Journey value;
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

  // Return ALL the entries corresponding to given key as an array of values, or NULL if the given key does not exist in the dictionary
  void getall(char key[], Journey *result, int &num_results, float start);

  void FastestNonStop(char station1[], char station2[], float start, Journey *result, int &num_results, float &fastest);

  void FastestOneStop(char station1[], char station2[], float start, Journey *result, int &num_results, float &fastest);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry &e);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]);

};

#endif
