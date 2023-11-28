#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;
#include "dictionary.h"
int Dictionary :: hashValue(char key[]){
    float sum=0;
    float x=31;
    int p=1;
    int n=sizeof(key);
    for(int i=0;i<n;i++){
        sum=(key[i]-'a'+1)*p;
        p=p*x;
    }
    float has=(sum*(sqrt(5)-1)/2);
    float has1=has-floor(has);
    int hashval=floor(N*has1);
    return hashval;
};
int Dictionary :: findFreeIndex(char key[]){
    int probe;
    if(no_of==N){return -1;}
    else{
        probe=hashValue(key);
        while (A[probe].kay!=NULL){
            probe=(probe+1)%N;
        }
        return probe;
};
Dictionary :: Dictionary(){
    A=new Entry[N];
    for(int i=0;i<N;i++){
        A[i].kay=NULL;
    }
    no_of=0;
};
struct Entry Dictionary::  *get(char key[]){
    int x=hashValue(key);
    int finded;
    bool found;
    int i=0;
    while (A[x].kay!=NULL && i<N){
        if (A[x].kay==key){
            finded=x;
            found=true;
            break;
        }
        else{
            x=(x+1)%N;
            i++;
        }
    if(found) return &(A[finded]);
    else return NULL;    
    }
}
bool Dictionary :: put(struct Entry e){
    char* c=e.kay;
    int b=findFreeIndex(c);
    if(b==-1) return false;
    else {
        A[b]==e;
        return true;
    }
}
bool Dictionary:: remove(char key[]){
    struct Entry e= get(key[]);
    if(e==NULL){return false;}
    else{
        char *c=e.kay;
        int x=hashValue(c);
        A[x].kay=NULL;
        return true;
    }
}
    

