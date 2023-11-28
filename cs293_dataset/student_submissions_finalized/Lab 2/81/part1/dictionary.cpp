#include <bits/stdc++.h>
using namespace std;
#include "dictionary.h"
int Dictionary::hashValue(char key[]){
    int hash=0;
    int x=31;
    long x_pow = 1;
    int i=0;
    while(int(key[i]!=0)) {
        hash = (hash + (int(key[i])) * x_pow);
        x_pow = (x_pow * x) % N;// to sustain the over flow
        i++;
    }
    double a=0.618;
    hash=N*((hash*a)-floor(hash*a));
    return floor(hash);
}
int Dictionary::findFreeIndex(char key[]){
    int probe;
    probe=hashValue(key);
    int check=0;
    while(A[probe].value!=0){
        probe=(probe+1)%N;
        check++;
        if(check==N){return -1;}
    }
    return probe;
}
 Dictionary::Dictionary(){
    N=64;
    A=new Entry[N];
}
Entry* Dictionary::get(char key[]){
    int probe;
    probe=hashValue(key);
    int check=0;
if(A[probe].value==-1){return NULL;}
    while(A[probe].value!=0){
        bool same=true;
        int i=0;
        while(int(key[i])!=0&&int(A[probe].key[i])!=0){
        if(int(A[probe].key[i])!=int(key[i])) same=false;
        i++;}
        if(same){return &(A[probe]);}
         probe=(probe+1)%N;
        check++; 
        if(check==N){return NULL;}
    }
    return NULL;
}
bool Dictionary:: put(struct Entry e){
    if(findFreeIndex(e.key)!=-1){
    A[findFreeIndex(e.key)].value=e.value;
    A[findFreeIndex(e.key)].key=e.key;
    return true;}
    else return false;
}
 bool Dictionary::remove(char key[]){
    if(get(key)==NULL){return false;}
    else {get(key)->value=-1;
          return true;}
 }

