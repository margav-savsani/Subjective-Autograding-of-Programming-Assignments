#include <iostream>
#include <string.h>
#include <cmath>

#include "dictionary.h"

Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new Entry[N];
    for(int i = 0; i < N; i++){
        A[i].cap=0;
    }
}

int Dictionary::hashValue(char key[]){
    int pow=1;
    int code=0;
    int mod = 1e7 +7;
    for(int i = 0; key[i] != '\0'; i++){
        code = (code + key[i]*pow)%mod;
        pow = (pow*31)%mod;
    }
    double a = (sqrt(5)-1)/2;
    int m = N;
    double ip,fp;
    fp =modf(code*a,&ip);
    int val = floor(m*fp);
    return val;
}

int Dictionary::findFreeIndex(char key[]){
    int idx = hashValue(key);
    if(A[idx].cap != -1)return idx;
    for(int i = idx+1; i != idx; i = (i+1)%N){
        if(A[i].cap != -1)return i;
    }
    return -1;
}

struct Entry *Dictionary::get(char key[]){
    int idx = hashValue(key);
    struct Entry *ptr;
    if(strcmp(A[idx].key,key)==0){ptr = A+idx;
                        return ptr;}
    for(int i = idx+1; i != idx; i = (i+1)%N){
        if(A[i].cap=0)break;
        if(strcmp(A[i].key,key)==0){ptr = &(A[i]);
                        return ptr;}
    }
    ptr = NULL;
    return ptr;
}

bool Dictionary::put(struct Entry e){
    int idx = findFreeIndex(e.key);
    if(idx == -1)return false;
    A[idx].key = e.key;
    A[idx].value = e.value;
    A[idx].cap = 1;
    return true;
}

bool Dictionary::remove(char key[]){
    int idx = hashValue(key);
    if(strcmp(A[idx].key,key)==0){A[idx].cap=-1;return true;}
    for(int i = idx+1; i !=idx; i = (i+1)%N){
        if(strcmp(A[i].key,key)==0){A[i].cap=-1;return true;}
    }
    return false;
}