#include<iostream>
#include"dictionary.h"
#include<cmath>

int Dictionary :: hashValue(char key[]){
  int hash;
  int n=0,x=33,sum=0;
  for(int i=0; i<32; i++)
   {
      if(key[i]='\0') break;
      else
        n=n+1;
     }  
  for(int i=n; i>=0; i--)        
      sum=sum*x+(int)key[i];
  int m=64;
  double B=(sqrt(5)-1)/2;
   double k=int(sum*B);
   hash=m*((sum*B)-k);    
  
  return hash;
 }
 
int Dictionary :: findFreeIndex(char key[]){
    int k=hashValue(key);
    for(int i=k; i<N; i++)
        if(A[i]=NULL) return i;
        else if(A[i].T==1) return i;
    return -1;  
 }
 
struct Entry Dictionary :: *get(char key[]){
   int k=hashValue(key);      
     for(int i=k; i<N; i++)  
       if(A[i].s==key) return A[i];
     return NULL;   
 }
 
bool Dictionary :: put(struct Entry e){
   int k=findFreeIndex(e.s);
   if (k==-1) return false;
   else 
      A[k]=e;
   return true;
 }
 
bool Dictionary :: remove(char key[]){
   struct x=Entry *get(key);
   if(x=NULL) return false;
   else
     x.T==1;
   return true;  
 }    
      
     
   
     
