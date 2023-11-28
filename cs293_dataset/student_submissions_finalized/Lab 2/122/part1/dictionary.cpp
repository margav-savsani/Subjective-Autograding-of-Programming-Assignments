#include<iostream>
#include "dictionary.h"
#include<cmath>
#include<string.h>
using namespace std;


Entry::Entry(){
 key=new char[32];
 }

 // Default constructor
  Dictionary::Dictionary(){
  N = 64;
  A = new Entry[N];}

   int  Dictionary ::  hashValue(char key[]){
  long int x=1,sum=0;
  for (int i=0; i<=32;i++){
  if(key[i]==NULL){
  break;}
    
  sum +=(int)key[i] * x;
  x=(x*33)%64;}
   double m= (sqrt(5)-1)/2;
   double n=  m*sum;
  return 64*(n-(int)n);}
 
 int  Dictionary :: findFreeIndex(char key[]){
  bool flag = false;int x;
for(int i = hashValue(key);i<N;i++){
if(A[i].key[0]== '\0'|| &(A[i])==NULL){
flag= true;
}
if(flag) {x=i;break;}}
if(flag) {return x;}
else{
if(!flag){
for(int i = 0;i<hashValue(key);i++){
if(A[i].key[0]== '\0'|| &(A[i])==NULL){
flag= true;
}
  if(flag) {x=i;break;}}
  if(flag) {return x;}
}
}
if(!flag){
return -1;
}
}
  
 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry*  Dictionary::get(char key[]){
  bool fly=true;
  int x;
  for(int i=hashValue(key);i<N;i++){
 int res= strcmp(A[i].key,key);
 if(res==0){
  fly=false;
  }
  if(!fly){
  x=i;
  break;
  }}
  if(!fly){
return &A[x];}
if(fly){
  for(int i=0;i<hashValue(key);i++){
  int res= strcmp(A[i].key,key);
 if(res==0){
  fly=false;}
  if(!fly){
x=i;
break;
  }}
  if(! fly){
return &A[x];}}
  if(fly){
  return NULL;}
  }
  

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
   bool Dictionary::put(struct Entry e){
  if(!(findFreeIndex(e.key) == -1)){
  int i=findFreeIndex(e.key);
  A[i].key = e.key;
  A[i].value =e.value;
  
  return true;
 }
  
  else {return false;}
  }

  // Remove the given key; return true if success, false if failure (given key not present)
  bool Dictionary :: remove(char key[]){
  bool t= true;
  for(int i = hashValue(key);i<N;i++){
  int res= strcmp(A[i].key,key);
 if(res==0){
  t = false;
  A[i].key[0]='\0';
  break;}}
 if(! t){
return true;
  }
  if(t){
  return false;}
  }
  

