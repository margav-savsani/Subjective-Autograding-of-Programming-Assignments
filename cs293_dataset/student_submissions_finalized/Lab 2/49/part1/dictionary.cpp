#include "dictionary.h"
#include <cmath>
#include<iostream>
using namespace std;

Dictionary :: Dictionary(){
   N=64;  
   A=new Entry[N]; 
   for(int i = 0;i<N;i++){
        A[i].value = 0;
   }
}

int Dictionary :: hashValue(char key[]){
    long long unsigned int keyvalue=0;
    string y=key;
    int x = 33;
    int i = y.length();
    while(i>=0){
      int ascii = key[i];       
      keyvalue=keyvalue*x+ascii; 
      keyvalue=(keyvalue)%64;     
      i--;
    }
    double a= (sqrt(5)-1)/2;
    double h = keyvalue*a;
    int hash = h;
    int hk = (N*(h - hash));
    hk=hk%N;    
    return hk;
    
}
int Dictionary :: findFreeIndex(char key[]){
    int probe = hashValue(key);
    int count=0;
    while(count<=N){
        if((A[probe].value==0)||(A[probe].value==-1))return probe; 
        probe = ((probe + 1)%N);
        count++;
    }
    return -1;
}
struct Entry* Dictionary :: get(char key[]){
    int b=hashValue(key);
    for(int i=0;i<N;i++){
        while((A[b].value!=0)){
            string x=A[b].key;
            string y=key;
            if(x==y && A[b].value!=-1)return &(A[b]);
            b=(b+1)%N;
        }
    }
    return NULL;  
}    
bool Dictionary :: put(struct Entry e){
    if(findFreeIndex(e.key)==-1) return false;
    A[findFreeIndex(e.key)]=e;
    return true;       
}    
bool Dictionary :: remove(char key[]){
    Entry *e = get(key);
    if(e==NULL)return false;
    (*e).value= -1;
    return true;
}