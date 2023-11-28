

#include<iostream>
#include<string.h>
#include<cmath>
#include "dictionary.h"
using namespace std;



 // Default constructor
  Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new Entry[N];
    for(int i=0; i<N; i++){
     A[i].key = NULL;
     A[i].free = true;
    }
  }

  

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int Dictionary::hashValue(char key[]){


int oddp=31;
int over = 1e9+7;
int hvalue = 0;
long m = 1;
    for(int i = 0; i < strlen(key); i++) {
        int temp = key[i];
        hvalue = (hvalue+ (temp - 'a' +1)*m )%over;
        m = (m*oddp)%over;

  }
if(hvalue<0){
  return (-hvalue)%N;
}
else{
  return hvalue%N;
}

  
  }

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int Dictionary::findFreeIndex(char key[]){
    int b = hashValue(key);
    int stop =0;
    for(int i=b; stop<N; i=(i+1)%N){
    //if(A[i].key == nullptr || A[i].is_ts == true){
      if(A[i].free || A[i].is_ts){
      //A[b].key = key;
      return i ;
      }
    
    stop++;
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
      A[place].value = e.value;
      A[place].free = false;
      return 1;
    }
    return 0;
  }

  // Remove the given key; return true if success, false if failure (given key not present)
  bool Dictionary::remove(char key[]){
    int v = hashValue(key);
    int h=0;
    char * ts = new char();
    for(int i=v; h<N; i=(i+1)%N ){
      h++;
      if(strcmp(key, A[i].key )==0){

        A[i].key = ts;
        A[i].is_ts = true;
        A[i].free = false;
        return 1;
      }
      
    
  }
  }



