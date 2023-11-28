#include<iostream>
#include<cmath>
#include<string.h>
using namespace std;
#include "dictionary.h"


Dictionary::Dictionary(){
        N = DICT_SIZE;
        A = new Entry[N];
        for(int i = 0 ;i < N;i++){
            A[i].value = 0;
        }
}
int Dictionary::hashValue(char key[]){
    int x = 33;
    long long unsigned int y = 0;
    for(int i = 0;key[i]!= '\0';i++){
        y = y*x + key[i];
    }
    double hash;
    double c = y*((sqrt(5) - 1)/2.0);
    hash = N*(c - int(c));
    return hash;
}
bool Dictionary::put(struct Entry e){
    if(findFreeIndex(e.key)!= -1){
        A[findFreeIndex(e.key)] = e;
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
        if(A[a].value==0 || A[a].value== -1){
            return a;
        }
        a = (a+1)%N;
        count++;
    }
    return -1;
}
struct Entry* Dictionary::get(char key[]){
    int b = hashValue(key);
    while(A[b].value!=0){
        if(A[b].key==key){
            return &A[b];
        }
        b = (b+1)%N;
    }
    return NULL;
}
bool Dictionary::remove(char key[]){
    if(get(key)!=NULL){
        get(key)->value = -1;
        return true;
    }
    else{
        return false;
    }
}

