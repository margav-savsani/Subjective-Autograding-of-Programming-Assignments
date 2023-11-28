#include<iostream>
#include<string>


#ifndef DICTIONARY_H
#define DICTIONARY_H


// Can change this value for debugging
const int DICT_SIZE = 64;

struct Entry {
  char key[32];
  std::string value;
};

class Dictionary {
 private:
  int N=DICT_SIZE; // size of array A
  struct Entry A[DICT_SIZE]; // Array of dictionary entries
  int hash_prime=41; //prime for hashing

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]){
    int current_pow=0;
	int current_char;
	int current_pow_of_p=1;
	int hash_val=0;
	while(key[current_pow]!='\0') {
		current_char=int(key[current_pow]);
		hash_val+=((current_char*current_pow_of_p)%N);
		current_pow_of_p=current_pow_of_p*hash_prime%N;
		current_pow+=1;
	}
	return hash_val;
  }

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]) {
    int start_index=hashValue(key);
	int current_index;
	for(int theta=0; theta<N; theta++) {
		current_index=(start_index+theta)%N;
		if (A[current_index].key[0]=='\0'||A[current_index].key[0]=='\t') {
			return current_index;
		}
	}
	return -1;
  }
  
  // Default constructor
  Dictionary() {
    for(int alpha=0; alpha<N; alpha++) {
		A[alpha].key[0]='\0';
	}
  }

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(char key[]);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]);
};

#endif
