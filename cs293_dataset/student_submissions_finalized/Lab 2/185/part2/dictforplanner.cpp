#include<iostream>
#include<string.h>
#include<cmath>
#include "dictforplanner.h"
using namespace std;


 // Default constructor
  Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new Entry[N];
    for(int i=0; i<N; i++){
      A[i].key = NULL;
    }
  }

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int Dictionary::hashValue(char key[]){

    int hvalue =0; 
    int x = 33, y = 1e9 + 7;
    long m = 1;
    for(int i = 0; i < strlen(key); i++) {
        hvalue = (hvalue + (key[i] - 'a' + 1) * m) % y;
        m = (m * x) % y;
    }

    double knuth = (sqrt(5.0)-1/2.0);
    hvalue = (hvalue*knuth+1)/41;
    return hvalue%N;

  }

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int Dictionary::findFreeIndex(char key[]){
    int b = hashValue(key);
    int stop =0;
    if(A[b].key == NULL){
      //A[b].key = key;
      return b ;
      }
    else{
      while(A[b].key!= key && A[b].key != NULL){
        
        if(stop<N){
          stop++;
          b++;
          b = b%N;
      }
      else break;
      }
      return b;

    }
    return -1;
  }
  

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *Dictionary::get(char key[]){
    
    int c = hashValue(key);
    int s=0;
    for(int i=c; s<N; i=(i+1)%N){
      s++;
      if(strcmp(key, A[i].key)==0){
        return &A[i];
      }
      }
    return NULL;
    };


  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool Dictionary::put(struct Entry e){
    if(findFreeIndex(e.key)!= -1){
      int place = findFreeIndex(e.key);
      A[place].key = e.key;
      //A[place].start[D] = e.start;
      //A[place].finish[D] = e.finish;
      A[place].destination = e.destination;;
      return 1;
    }
    return 0;
  }

  // Remove the given key; return true if success, false if failure (given key not present)
  bool Dictionary::remove(char key[]){
    int v = hashValue(key);
    int h=0;
    for(int i=v; h<N; i++ ){
      h++;
      if(strcmp(key, A[i].key )==0){
        A[i].key = NULL;
        free(A[i].key);
        return 1;
      }
    }
    return 0;
  }