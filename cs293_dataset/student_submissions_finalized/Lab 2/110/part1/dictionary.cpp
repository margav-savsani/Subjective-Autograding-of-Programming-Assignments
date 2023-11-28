#include "dictionary.h"
#include <cmath>
#include <iostream>
#include <string.h>
using namespace std;

Dictionary :: Dictionary(){
    N = DICT_SIZE;
    A = new Entry[N];

}

int Dictionary :: hashValue(char key[]){
    int x = 37;
    long long int poly=0;
    int i = 0;
    while(key[i] != '\0'){
        poly = x*poly+key[i];
        poly = poly%N;
        i++;
    }
    return poly;
}

int Dictionary :: findFreeIndex(char key[]){
    int index = hashValue(key);
    for(int i=0;i<N;i++){
        if(A[(index+i)%N].o == 0 || A[(index+i)%N].o == 2){
            return (index+i)%N;
        }
    }
    return -1; // array is full
}

bool Dictionary :: put(struct Entry e){
    int m = findFreeIndex(e.key);
    if(m == -1)   return false;
    else{
        A[m] = e;
        A[m].o = 1;
        return true;
    }
}

bool Dictionary :: remove(char key[]){
    Entry* rem = get(key);
    if(rem == NULL) return false;
    rem->o = 2;
    return true;   
}

struct Entry *Dictionary :: get(char key[]){
    int val = hashValue(key); 
    int i = 0;
    int j;
    // int g = 0;
    // while(A[j].key[g] != '\0' && key[g] != '\0'){
    //     for( i=0;i<N;i++){
    //         j = (val+i)%N;
    //         if(A[j].key[g] == key[g] && A[j].o==1) return &A[j];
    //         if(A[j].o == 0) return NULL;
    //     }
    //     g++;
    // } 
    for(i=0;i<N;i++){
        j=(val+i)%N;
        if(strcmp(A[j].key, key)==0 && A[j].o ==1) return &A[j];
        if(A[j].o == 0) break;
    }
    return NULL;
}
