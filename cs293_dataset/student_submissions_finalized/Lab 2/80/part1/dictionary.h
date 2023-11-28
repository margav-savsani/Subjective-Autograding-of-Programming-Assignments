#include<iostream>
#include<string.h>


#ifndef DICTIONARY_H
#define DICTIONARY_H


// Can change this value for debugging
int DICT_SIZE = 64;

struct Entry {
 public:
  char key[32];
  int value;
  int property;
  
  Entry(){
  	property = 0;//signifies empty entry
  }
  Entry(char key_[], int value_){
  	value = value_;
  	int pos = 0;
  	while(key_[pos] != '\0'){
    		key[pos] = key_[pos];
    		pos += 1;
  	}
  	key[pos] = '\0';
  	property = 1; //signifies full entry
    
  }
  
  int give_val(){
  	return value;
  }
  
  char* give_key(){
  	return key;	
  	
  }
  
  void make_non_empty(){
  	property = 1;
  }
  
  void make_tombstone(){
  	property = 2; //signifies tombstone
  }
  
  int give_property(){
  	return property;
  }
  
  
  // define suitable fields here
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
