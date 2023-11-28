#include<iostream>
#include<string.h>
#include<cmath>

#ifndef DICTIONARY_H
#define DICTIONARY_H


// Can change this value for debugging
const int DICT_SIZE = 64;

struct Entry {
  // define suitable fields here
  char key[32];
  int value;
};

class Dictionary {

 private:

  int N; // size of array A
  struct Entry *A; // Array of dictionary entries

 public:

  // Default constructor
  Dictionary(){
    N=DICT_SIZE;
    A=new Entry[N];
    for(int i=0;i<N;i++){
      strcpy(A[i].key,"NULL"); //represents that the entry is empty(but not after deletion, TOMBSTONE is used to denote an entry which becomes empty after deletion of a key)
      A[i].value=0;
    }
  }

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]){
    //Polynomial accumulation scheme is used to convert strings to integers
    int n=strlen(key);
    const int m=23,x=31;
    int s=key[n-1];
    for(int i=n-2;i>=0;i--){
      s=key[i]+s*x;
    }
    //Now, the fibonacci hashing scheme is used on the above obtained integers to get the hash value.
    const double a=(sqrt(5)-1)/2;
    return floor(N*(s*a-floor(s*a)));
  }

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]){

    //checks if the array is full
    bool isFull=true;
    for(int i=0;i<N;i++){
      if(strcmp(A[i].key,"NULL")==0 || strcmp(A[i].key,"TOMBSTONE")==0) isFull=false;     //checks if the entry is empty
    }
    if(isFull) return -1;

    //searches for free index if array is not full using the linear probing scheme
    int i=hashValue(key);
    while(strcmp(A[i].key,"NULL")!=0 && strcmp(A[i].key,"TOMBSTONE")!=0){     //terminates when we find an empty entry
      i=(i+1)%N;
    }
    return i;
  }
  
   
  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(char key[]){
    int i=hashValue(key);
    while(true){
      if(strcmp(A[i].key,key)==0) return &A[i];         //checks the entry corresponding to the hash value of the given key
      else if(strcmp(A[i].key,"NULL")==0) return NULL;        //if the entry is empty and not a tombstone,then the key does not exist in the dictionary
      else i++;     //subsequent entries are checked until the key matches or we encounter a "NULL" key.
    }
  }

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e){
    int index=findFreeIndex(e.key);
    if(index==-1) return false; //checks whether the array is full
    else{
      A[index]=e;
      return true;
    }
  }

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]){
    if(get(key)==NULL) return false;    //checks if the given key is present
    else{
      strcpy(get(key)->key,"TOMBSTONE");    //stores "TOMBSTONE" in the key of the entry after its key is removed
      return true;
    }
  }
};

#endif