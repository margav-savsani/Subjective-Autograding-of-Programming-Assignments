#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<cmath>
#include"dictionary.h"
#include<string.h>

using namespace std;

Dictionary :: Dictionary(){
  N=64;
  A=new Entry[N];
  for(int i=0;i<N;i++){
    A[i].value = 0;
  }
}

int Dictionary :: hashValue(char key[]){
  long long unsigned int x=0;
  string y=key;
  int l = y.length();
  double a = (sqrt(5)-1)/2;
  for(int i=l-1;i>=0;i--){
    int asc = key[i];
    x= asc+x*33;
  }
  double h = x*a;
  long int hash = h;
  a = (N*(h - hash));
  return int(a);
}

int Dictionary :: findFreeIndex(char key[]){
  int hash = hashValue(key);
  int count = 0;
  while(1){
    if(A[hash].value==0 || A[hash].value==-1)
      return hash;
      hash=(hash+1)%64;
      count++;
    if(count==64)
      return -1;
  }

  }

struct Entry* Dictionary :: get(char key[]){
  int k = hashValue(key);
  while(A[k].value!=0){
    if(A[k].value==-1){
      k=(k+1)%64; 
      continue;
    }
    else if(strcmp(A[k].key,key)==0)
       return &A[k];
      k=(k+1)%64;   
  }
  return NULL;
}

bool Dictionary :: put(struct Entry e){
  if(findFreeIndex(e.key)==-1)
    return false;
  else {
    A[findFreeIndex(e.key)]=e;
    return true;
  }
    
}

bool Dictionary :: remove(char key[]){
  int hash = hashValue(key);
  while(A[hash].value!=0){
    if(A[hash].value==-1)
      return false;
    else if(strcmp(A[hash].key,key)==0){
      A[hash].value=-1;
      return true;
    }
    else
      hash=(hash+1)%64;
  }
  return false;
}
  
  



