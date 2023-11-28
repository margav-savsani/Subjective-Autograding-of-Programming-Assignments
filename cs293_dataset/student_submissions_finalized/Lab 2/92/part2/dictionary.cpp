#include<iostream>
#include<cmath>
#include<string.h>
#include "dictionary.h"
using namespace std;

// Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
int Dictionary::hashValue(int value){
    float y=(sqrt(5)-1)/2;
    float ans;
    ans=value*y-floor(value*y);int p=ans*DICT_SIZE;
    return p;
}

// Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int Dictionary::findFreeIndex(int value){
    int x=hashValue(value);
    int y;y=(x+1)%N;
    if(A[x].value==0||A[x].value==-1){return x;}
    else {
        while((A[y].value!=0) && (y!=x) && (A[y].value!=-1)){
            y=(y+1)%N;}
        if(y!=x){return y;}
        else {return -1;}
    }
  }

// Default constructor
  Dictionary::Dictionary(){
    A=new Entry[DICT_SIZE];
    N=DICT_SIZE;
    for(int i=0;i<N;i++){
        A[i].value=0;
    }
  }

 // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
 bool Dictionary::put(struct Entry e){
    int x;x=findFreeIndex(e.value);
    if(x==-1){return 0;}
    else{
        A[x]=e;
        return 1;
    }
}

// Remove the given key; return true if success, false if failure (given key not present)
  bool Dictionary::remove(char key[],int value,char key1[]){
    Entry *ans;
    ans=get(key,value,key1);
    if(ans==NULL){return 0;}
    else{ans->value=-1;
    return 1;}
  }

// Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
 Entry* Dictionary::get(char key[],int value,char key1[]){
    int x=hashValue(value);int y=(x+1)%N;
    if(strcmp(A[x].key,key)==0 &&strcmp(A[x].key1,key1)==0 && A[x].value!=-1){return &A[x];}
    else {while(strcmp(A[y].key,key)!=0 &&strcmp(A[y].key1,key1)!=0 && y!=x){
      y=(y+1)%N;
    }
    if(y==x){return NULL;}
    if(A[y].value!=-1){return &A[y];}
    return nullptr; 
  }
 }
