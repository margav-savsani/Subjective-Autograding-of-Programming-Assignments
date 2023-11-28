#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"dictionary.h"


Dictionary::Dictionary(){
    N=64;
    A = new Entry[64];
    for(int i=0;i<N;i++){
      A[i].key=new char[32];
      A[i].key=Ba;
    
    }
}

int Dictionary::hashValue(char key[]){
    int p=37;
    int i=0;
    for(i ; i< 32 ; i++){
        if(key[i] == '\0' ) break;
    }
    int ans=key[0];
    for(int k=1 ; k <i ; k++){
        ans = (ans*p + int(key[i])-int('a')+20)%613; 
    }
    
  
    double a=0.618;
    a*=ans;
    int b=64;
    b= b*(a-(int)a);
    return b;
   
  }

int Dictionary::findFreeIndex(char key[]){
    int i = hashValue(key);
    for(int j=0;j<64;j++){
      if (A[i].value==0||A[i].value==-1){return i;}
      i=(i+1)%64;}
    return -1;
    }
struct Entry *Dictionary::get(char key[]){
    int pos= hashValue(key);int size=0;
    for(int size=0;size<64;size++){

     if(strcmp(A[pos].key,key)==0){
            return &A[pos];
        }
        pos = (pos+1)%64;}
  return NULL;}
  

bool Dictionary::put(struct Entry e){
    int i = findFreeIndex(e.key);
    if (i==-1)return 0;
    A[i].key=e.key;
    A[i].value=e.value;
    return 1;
  

  }

bool Dictionary::remove(char key[]){ 
  if(get(key)==NULL) return 0;
    int pos=hashValue(key);
    int size=0;
    while(true){        
        if(strcmp(A[pos].key,key)==0){
            A[pos].value=-1;A[pos].key=Ca;
            return 1; 
        }  
        pos = (pos+1)%64;
        size++;
        if(size==64)return 0;
    }}
