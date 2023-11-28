#include <iostream>
#include <string.h>
#include <cmath>

#include "dictionary.h"

Dictionary::Dictionary(){
    N = DICT_SIZE;
}

int Dictionary::hashValue(char key[32]){
    //finding the hash value of the function
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

int Dictionary::findFreeIndex(char key[32]){
    //finding if there is any space in the dictionary to insert a new element
    int idx = hashValue(key);
    if(A[idx].cap != -1)return idx;
    for(int i = idx+1; i != idx; i = (i+1)%N){
        if(A[i].cap != -1)return i;
    }
    return -1;
}

int Dictionary::get(char key[32]){
    //returning the index of the element if it's already present
    int idx = hashValue(key);
    if(A[idx].cap == 0)return -1;
    if(strcmp(A[idx].key,key)==0)return idx;
    for(int i = idx+1; i != idx; i = (i+1)%N){
        if(strcmp(A[i].key,key)==0)return i;
    }
    return -1;
}

bool Dictionary::put(struct Path pt){
    int in = get(pt.start);
    if(in==-1){
        // adding an element if doesn't exist already
        int idx = findFreeIndex(pt.start);
        if(idx==-1)return false;
        strcpy(A[idx].key,pt.start);
        A[idx].cap=1;
        int l = A[idx].len;
        A[idx].p[l]=pt;
        A[idx].len += 1;
        return true;
    }
    //Appending the new element to the already created array
    int ln = A[in].len;
    A[in].p[ln]=pt;
    A[in].len += 1;
    return true;
}

bool Dictionary::remove(char key[32]){
    //Removing an element
    int idx = hashValue(key);
    if(strcmp(A[idx].key,key)==0){A[idx].cap=-1;return true;}
    for(int i = idx+1; i !=idx; i = (i+1)%N){
        if(strcmp(A[i].key,key)==0){A[i].cap=-1;return true;}
    }
    return false;
}