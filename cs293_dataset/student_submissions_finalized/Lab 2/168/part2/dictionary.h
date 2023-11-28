#include<iostream>
#include<string.h>


#ifndef DICTIONARY_H
#define DICTIONARY_H


// Can change this value for debugging
const int DICT_SIZE = 64;
const int tombstone=0;
const int empty=-1;
const int full=1;

struct Entry {
	//for now, all values will be 1 if there is a key-value pair present. 0 will signify tombstones and -1 will signify that there is no entry.
	char key[32];
	float value;
	int marker;

	Entry(){
		marker=empty;	
    strcpy(key,"");
	}

	Entry(char* a){
		strcpy(key,a);
		marker=full;
	}
};

class Dictionary {
 private:
  int N; // size of array A
  struct Entry *A; // Array of dictionary entries

 public:

  bool getDict(int i);

  char* getKey(int i);

  float getValue(int i);

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]);
  
  // Default constructor
  Dictionary(); 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(char key[]);

  int* getIndices(char key[],int* indices);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]);
};

#endif