#include "dictionary.h"

 // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]){
	const int p = 29;
	int hash = 0;
	unsigned int h = 1;
	for(int i = 0; i < 32; i++) {
		if (key[i]='\n')
			break;
	
		hash = (hash + (key[i] - 'a' ) * h) % N;
		h = (h * p) % N;
	}
	return hash;
}


  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]){
      int index =hashValue( key[]);
      while (A[index]!= NULL && A[index]-k!=k){
      	A[index]= key
      }}
  // Default constructor
  Dictionary(); 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(char key[]){
  
  

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e){
     

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]){
  int hash_value =hashValue(key[]);
  int q=-1;
  bool m= false 
  while( A[hash_value]!=NULL ){
  	A[hash_value]= NULL;
  	
  
};
