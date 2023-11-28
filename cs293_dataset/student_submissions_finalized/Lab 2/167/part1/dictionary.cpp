#include<iostream>
#include<string.h>
#include<cmath>
#include"dictionary.h"
using namespace std;

int Dictionary :: hashValue(char key[]){
  int h=0;
  string s=key;
  for(int i=s.length()-1;i>=0;i--){
    h=h*33+key[i];
  } 
   double x=(sqrt(5)-1)/2; //fibanacci
   double y=64*(h*x-int(h*x));
   h=y; 
   return h;
    
  }
int Dictionary :: findFreeIndex(char key[]){
    int i=hashValue(key); 
    int a=0;
    while(1){   
     if(A[i].value==0 || A[i].s==-1) return i;
     a++;
     i=(i+1)%N;
     if(a==64) return -1;
    }
     
   }
    
   
Dictionary :: Dictionary(){
 N=64;
 A=new Entry[64];
 for(int j=0;j<N;j++){
   A[j].value=0;
   }
 }


struct Entry* Dictionary :: get(char key[]){
  int i=hashValue(key);
  while(A[i].value!=0 ){
   if(A[i].s==-1){
     i=(i+1)%N;
     continue;
     }
   if(strcmp(A[i].key,key)==0)
    return &A[i];
   i=(i+1)%N; 
  }
  return NULL;
}
   
   
   
bool Dictionary :: put(struct Entry e){
 int x=findFreeIndex(e.key);
 if(x==-1)
   return false;
 else 
  A[x]=e;
  return true;
}
    
    
bool Dictionary :: remove(char key[]){
  int i=hashValue(key);
  while(A[i].value!=0 ){
   if(strcmp(A[i].key,key)==0 && A[i].s!=-1)  {
    A[i].s=-1;
    return true;
   }
   i=(i+1)%N;
  }
  return false;}
