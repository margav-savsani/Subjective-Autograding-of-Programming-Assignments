#include<iostream>
#include <stdio.h>
#include<string.h>
#include <map>
#include<cmath>
#include "dictionary.h"
using namespace std;

int Dictionary::hashValue(char key[]){
  int hash_value=0;
  const int n = sizeof(A->key);
  for (int i = 0; i < n; ++i) {
           hash_value += key[i]*pow(31,n-i-1);
   }
  return hash_value%N;
}    
int Dictionary::findFreeIndex(char key[]){
  int ffi;
  ffi = hashValue(key);
  if (ffi != A->value){
    return ffi;
  }    
  return -1;
} 

Dictionary::Dictionary(){
 map<char*,int>k;
 Entry A;
 k[A.key]=A.value;
} 

struct Dictionary::Entry *get(char key[]){
 map<char*,int>k;
 value=k[key];
 Entry e;
 e.value=value;
 e.key=key[];
 return e;
}


bool Dictionary::remove(char key[]){
 map<char*,int>k;
 Entry A;
 k[A.key]=A.value;
 if(key = A.key){
   return true;}
 else {
   return false;}  
}

bool Dictionary::put(struct Entry e){
 e.value= hashValue(e.key);
 map<char*,int>k;
 Entry A;
 k[A.key]=A.value;
 if(k[A.key] != e.value){
  k[e.key] =e.value;
  return true;}
 else{
  return false;}
}  
  
  
