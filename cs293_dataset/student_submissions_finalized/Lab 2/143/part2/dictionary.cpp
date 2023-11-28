#include<iostream>
#include<cmath>
#include<string.h>
using namespace std;
#include "dictionary.h"


Dictionary::Dictionary(){
        N = DICT_SIZE;
        A = new Entry[N];
        for(int i = 0 ;i < N;i++){
            A[i].assign = 0;
        }
}
int Dictionary::hashValue(char key[]){
    int x = 33;
    long long unsigned int y = 0;
    int num = 0;
    for(int i = 0;key[i]!= '\0';i++){
        num++;
    }
    for(int i = num - 1 ;i>=0;i--){
        y = y*x + key[i];
    }
    int hash;
    double c = y*((sqrt(5) - 1)/2.0); 
    int d = N*(c - int(c));
    hash = d%N;
    return hash;
}
bool Dictionary::put(struct Entry e){
    if(findFreeIndex(e.key)!= -1){
        A[findFreeIndex(e.key)] = e;
        A[findFreeIndex(e.key)].assign = 1;
        return true;
    }
    else{
        return false;
    }
}
int Dictionary::findFreeIndex(char key[]){
    int count = 0;
    int a = hashValue(key);
    while(count<=N){
        if(A[a].assign==0 || A[a].assign== -1){
            return a;
        }
        a = (a+1)%N;
        count++;
    }
    return -1;
}
struct Entry* Dictionary::get(char key[]){
    int b = hashValue(key);
    int count = 0;
    while(A[b].assign!=0 && count<N){
        string x = A[b].key;
        string y =key;
        if(x == y && A[b].assign!=-1){
            return &A[b];
        }
        b = (b+1)%N;
        count++;
    }
    return NULL;
}
bool Dictionary::remove(char key[]){
    if(get(key)!=NULL){
        get(key)->assign = -1;
        return true;
    }
    else{
        return false;
    }
}

