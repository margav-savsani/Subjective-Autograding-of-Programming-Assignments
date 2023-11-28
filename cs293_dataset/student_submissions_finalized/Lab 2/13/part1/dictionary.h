#include<iostream>
#include<string.h>
#include<cmath>


#ifndef DICTIONARY_H
#define DICTIONARY_H


// Can change this value for debugging
int DICT_SIZE = 64;

struct Entry {
  // define suitable fields here
  char key[32];
  int value;
};

class Dictionary {
 private:
  int N=DICT_SIZE; // size of array A //max kength as given in problem statement is 64
  Entry *A; // Array of dictionary entries

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]){
  	int x=33;//for using polynomial accumulation
  	int k=int(key[l]);//hashvalue
  	int l;//index of last element of key[], excluding \0
  	for(int i=0; key[i]!='\0'; i++) l=i;
  	for(int i=l; i>0; i--){
  		k=(k*x+key[i-1])%x;
  	}
  	double a=(sqrt(5)-1)/2;
  	k=int(64*((k*a)%1.0))
  	return k;
  };

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]){
  	if(A(hashValue(key[]))=='\0') return hashValue(key[]);
  	else if(A(hashValue(key[]))!='\0'){
  		for(int i=0; i<N; i++){
  			if(A[(i+hashValue(key[]))%N]=='\0') return (i+hashValue(key[]))%N;
  		}
  	}
  	else return -1;
  }
  
  // Default constructor
  Dictionary(){
  	A=new Entry[N];
  	for(nt i=0; i<N; i++) A[i].key='\0';
  }; 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  Entry *get(char key[]){
  	for(int i=0; i<N; i++){
  		if(A[i].key==key[]) return &A[i];
  		else if(i==N-1) return NULL;
  	}
  };

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(Entry e){
  	if(findFreeIndex(e.key)!=-1) A[findFreeIndex(e.key)]=e;
  }

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]){
  	
  }
};

#endif
