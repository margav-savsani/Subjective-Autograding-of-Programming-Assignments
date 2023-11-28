#include<iostream>
#include<string.h>
#include<cmath>
#include "dictionary.h"
using namespace std;

// Can change this value for debugging
   
 int Dictionary::hashValue(char key[]){
      int x=33;
      int y=1;
      double z=0;
      for(int i=0;key[i]!='\0';i++){
          z=(key[i]*y+z);
          y=y*x;
          }
      int m=64;
      float A=(sqrt(5)-1)/2;
      float c;
      c=z*A-float(int(z*A));
      int p=m*c;
      return p;
      }
  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int Dictionary::findFreeIndex(char key[]){
       int x;
       int a;
       x=hashValue(key);
       a=x;
       if(strlen(A[x].key)==0){
          return x;
          }
       else{
          x=(x+1)%N;
         while(strlen(A[x].key)!=0 && (x!=a)){
            x=(x+1)%N;
            }
          if(x==a){
            return -1;
            }
            return x;
         }
       }
  // Default constructor
   Dictionary::Dictionary() {
      N=64;
      A=new Entry[64];
    
     }

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
   struct Entry *Dictionary::get(char key[]){
        int s=hashValue(key);
        int t=s;
        if(!strcmp(A[s].key,key) && (A[s].value!=-1)){
          return &A[s];
          }
        else{
          s=(s+1)%N;
          while(strcmp(A[s].key,key) && t!=s){
             s=(s+1)%N;
             }
           if(t==s){
            return NULL;
            }
           else{
             if(A[s].value!=-1){
             return &A[s];
             }
             return NULL;
          }
        }
       }
  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool Dictionary::put(struct Entry e){
         int d;
         d=findFreeIndex(e.key);
         if(d==-1){
           return false;
           }
         else{
           A[d]=e;
           return true;
           }
       }
  // Remove the given key; return true if success, false if failure (given key not present)
  bool Dictionary::remove(char key[]){
      if(get(key)==NULL){
        return false;
        }
      else{
        get(key)->value=-1;
        return true;
        }
       }
    

