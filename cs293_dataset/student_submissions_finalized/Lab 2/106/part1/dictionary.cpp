#include<iostream>
#include<string.h>


#ifndef DICTIONARY_H
#define DICTIONARY_H


// Can change this value for debugging
int DICT_SIZE = 64;

struct Entry {
	char *name; //name of the entry
	int value; //value assigned to entry	
	struct Entry *next; //next entry in the dictionary
  // define suitable fields here
};

class Dictionary {
 private:
  int N; // size of array A
  struct Entry *A; // Array of dictionary entries

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]) {
  	int hvalue;
  	for (int i=0; key[i] != null && i<32; i++) {
  		hvalue = key[i] + hvalue*31;  // multiplied by 31 to reduce probability of hash collisions
  	};
  	return hvalue % N; //divided by N to get value between 0 and N-1
  };

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]){
  	int fi = -1;
  	//int fi = hashValue(key[]); //finding hashvalue
  	//if(A[fi] == null) return fi;
  	for(int i =0; A[i] != null; i++){
  		if(A[i] = null) fi = i;
  	};
  	return fi;
  };
  
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
