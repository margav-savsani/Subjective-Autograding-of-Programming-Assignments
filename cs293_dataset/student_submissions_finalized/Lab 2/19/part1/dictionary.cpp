#include<iostream>
#include<cmath>
#include<string.h>
#include "dictionary.h"
using namespace std;

int Dictionary :: hashValue(char key[]){
    int hash = 0;
    int pow = 1;
    int i = 0;
    while(key[i]){
        hash = (hash + int(key[i])*pow) % 64;
        pow = (pow*37) % 64;
        i += 1;
    }
    return hash;
}

int Dictionary :: findFreeIndex(char key[]){
    int hash = hashValue(key);
    int i = 0;
    while(hash + i < N){
        if(A[hash + i].value == 0 || A[hash +1].value == -1){
            return hash + i;
        }
        i ++;
    }
    return -1;
}

Dictionary :: Dictionary(){
    N = 64;
    A = new Entry[64];
}

bool Dictionary :: put(struct Entry e){
    int loc = findFreeIndex(e.key);
    if(loc == -1){
        return false;
    }
    else{
        int i = 0;
        while(e.key[i]){
            A[loc].key[i] = e.key[i];
            i += 1;
        }
        return true;
    }
}

bool Dictionary :: remove(char key[]){
    int hash = hashValue(key);
    for(int i=0; hash + i < N; i++){
        if(A[hash + i].value == 0){
            return false;
        }
        else if(A[hash + i].value == -1){
            continue;
        }
        else{
            if(strcmp(key, A[hash+i].key)==0){
                A[hash+i].value = -1;
                return true;
            }
        }
    }
    return false;
}

struct Entry* Dictionary :: get(char key[]){
    int hash = hashValue(key);
    for(int i=0; hash+i < N; i++){
        if(A[hash].value == -1){
            continue;
        }
        else{
            if(strcmp(key, A[hash+i].key)==0){
                return &A[hash+i];
            }
        }
    }
    return NULL;
}