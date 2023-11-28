#include <iostream>
#include<string.h>
#include<cmath>

using namespace std; 
 
#include "dictionary.h"
 
 Dictionary :: Dictionary(){
   N=DICT_SIZE;
   A=new Entry [DICT_SIZE];           
  }
 
int Dictionary :: hashValue(char key[]){
  int hash;
  int n=0,x=7;
  long int sum=0;
  for(int i=0; key[i]!='\0';i++)    
          n=n+1;
             
  for(int i=n; i>=0; i--)        
      sum=sum*x+int(key[i]);
      
  int m=64;
  double B=(sqrt(5)-1)/2;
   double k=int(sum*B);
   hash=m*((sum*B)-k);    
  return hash;
 }
 
 int Dictionary :: findFreeIndex(char key[]){
    int k=hashValue(key);
    
    for(int i=k;i<N;i++){
      if(A[i].stat==0) return i;
        else if(A[i].T==1) return i;
        }  
        for(int i=0; i<k; i++){
        if(A[i].stat==0) return i;
        else if(A[i].T==1) return i;
        }      
    return -1;  
 }
 

  
struct Entry* Dictionary :: get(char key[]){
   int k=hashValue(key);      
     for(int i=k; i<N; i++) 
      { 
        if(strcmp(A[i].key,key)==0) 
          if(A[i].stat==1)
             return &A[i];
           }
     for(int i=0; i<k; i++)  
      {
         if(strcmp(A[i].key,key)==0) 
          if(A[i].stat==1)
             return &A[i];
             }            
     return NULL;   
 }
 
 bool Dictionary :: put(struct Entry e){
   int k=findFreeIndex(e.key);
   if (k==-1) return false;
   else 
     {
       A[k]=e;
       A[k].stat=1;
       }
   return true;
 }
 
bool Dictionary :: remove(char key[]){
    int k=hashValue(key);
    int j;      
    for(int i=k; i<N; i++)   
      {
        if(strcmp(A[i].key,key)==0) j=i;
        else
          { 
            for(int i=0; i<k; i++)   
             if(strcmp(A[i].key,key)==0) j=i;
          }        
        }  
   if(A[j].stat==0) return false;
   else
     { 
       A[j].stat=0;
       A[j].T=1;
       }
   return true;  
 }   
