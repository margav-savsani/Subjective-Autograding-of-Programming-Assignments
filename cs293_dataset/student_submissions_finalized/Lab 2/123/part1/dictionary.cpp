#include <iostream>
#include <cmath>
#include <string.h>
#include "dictionary.h"
using namespace std;
//Empty = '\0' Tombstone = '\n'

Dictionary::Dictionary(){ //Constructor
    N = DICT_SIZE;
    A = new Entry[N];   //Initialising everything to Empty
    for(int i=0; i<N; i++){
        strcpy(A[i].key,"\0");
    }
    full = 0; //count of no. of full boxes
}

int Dictionary::hashValue(char key[]){ //Hash Function is h(x) = a0 + x(a1 + a2(x ........ an)))..)
    int s = 0;  //size of key
    while (key[s] != '\0')
    {
        s++;
    }
    int hashVal = key[s];
    int x = 31; // x is some random prime
    for (int i = 0; key[i] != '\0'; i++){ //Updating hash value
        hashVal = hashVal*x + key[s-1];
    }
    double fib = (sqrt(5) - 1)/2; //fibonacci hashing
    int lowVal = fib*hashVal; //compressing hash value
    int comphashVal = lowVal%DICT_SIZE;
    return comphashVal;
}

bool Dictionary::put(Entry e){
    int put = 0; //check if e is added or not
    int k  = hashValue(e.key);
    if (full == N){ //check if list is full or not
        return false;
    }
    else{ // start from k and  do linear probing
        for(int i=k; put != 1; i = (i+1)%64){
            if((strcmp(A[i].key,"\0") == 0) || (strcmp(A[i].key,"\n") == 0)){
                A[i] = e;
                full++;
                return true;
            }
        }
        return -1;
    }
}

Entry* Dictionary::get(char k[]){
    int hashVal = hashValue(k);
    int pos = hashVal;
    int got = 0;
    for(int i = 0; i < N;  i++){
        if(strcmp(A[pos].key,k) ==0){ //if both are same then 'got' will be 1
            got = 1;
            break;
        }
        else{
            pos = (pos+1)%64;
        }
    }
    if (got == 1)
    {
        return &(A[pos]);
    }
    else{
        return NULL;
    }
}

bool Dictionary::remove(char key[]){ //Removing same way as finding
    int hashVal = hashValue(key);
    int pos = hashVal;
    for(int i = 0; i < N; i = (i+1)){
        if(strcmp(A[pos].key,key)==0){
            strcpy(A[pos].key,"\n");
            full--;
            return true;
        }
        else{
            pos = (pos+1)%64;
        }
    }
    return false;
}

int Dictionary::findFreeIndex(char key[]){ //same way as finding
    int pos = -1;
    int k  = hashValue(key);
    if (full == N){
        return pos;
    }
    else{
        for(int i=k; pos == -1; i = (i+1)%64){
            if((strcmp(A[i].key,"\0") == 0) || (strcmp(A[i].key,"\n") == 0)){
                pos = i;
            }
        }
        return pos;
    }
}
