#include<iostream>
#include<string.h>
using namespace std;
#include<cmath>
#include "dictionary.h"
Entry::Entry(){
     key=new char[32];
     }
Dictionary::Dictionary(){
     N=64;
     A=new Entry[N];
     }
int Dictionary::hashValue(char key[]){
    const int x=37;
    long int a=0;
    double A=0.618;
    int i=0;
    while(key[i]!='\0'){
    a=(a*x+(key[i]));
    i++;}
    double h=a*A;
    int r=N*(h-int(h));
    return r;
    }
int Dictionary::findFreeIndex(char key[]){
     int h=hashValue(key);
     int j=0;
     for(int i=h;i<N;i=remainder(i+1,N)){
     if(j!=0 && i==h) return -1;
     if(A[i].tombstone==1) return i;
     if(A[i].key[0]=='\0')return i;
     j++;}
     }
bool Dictionary::put(struct Entry e){
     int y=findFreeIndex(e.key);
      if(y==-1) return false;
      else{
      A[y]=e;
      return true;}
      }
     
bool Dictionary::remove(char key[]){
     int j=0;
     int h=hashValue(key);
     for (int i=hashValue(key);i<N;i=remainder(i+1,N)){
       if(strcmp(key,A[i].key)==0) {A[i].tombstone=1;A[i].value=0;return true;}
       if(A[i].key[0]=='\0')return false;
       if(A[i].tombstone==1)continue;
       if(j!=0 && i==h) return false;
       j++;
       } 
     
    }
struct Entry* Dictionary:: get(char key[]){
     int j=0;
     int h=hashValue(key);
     for (int i=hashValue(key);i<N;i=remainder(i+1,N)){
       if(strcmp(key,A[i].key)==0) return &A[i];
       if(A[i].key[0]=='\0') return NULL;
       if(A[i].tombstone==1)continue;
       if(j!=0 && i==h) return NULL;
       j++;
       } 
     }
