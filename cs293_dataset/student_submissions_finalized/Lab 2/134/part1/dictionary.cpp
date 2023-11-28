#include <iostream>
#include <cmath>
#include "dictionary.h"

bool comp_str(char* s1, char* s2){    // this is created to compare the char arrays
        for(int i=0; i<32; i++){
        if(s1[i]!=s2[i])
            return false;           
        if(s1[i]==0) break; 
    }
    return true;
}
int Dictionary :: hashValue(char* key){
    key[32] = 0; 
    double keyvalue=0;
    int poly_x=1;                  
    for(int i=0; i<32; i++){
        if(key[i]==0)
            break;
        keyvalue += key[i]*pow(poly_x,i); //polynomial methond
    }
    int hval = floor(N*((keyvalue*(sqrt(5)-1)/2.0)-floor(keyvalue*(sqrt(5)-1)/2.0))); //fibonacci compression
    return hval;
}

int Dictionary :: findFreeIndex(char key[]){
    int hvalue = hashValue(key);
    for(int i=0; i<64; i++){
        if(A[(hvalue+i)%N].null == true || A[(hvalue+i)%N].tombstone == true)
            return (hvalue+i)%N; //return the index of any nearest empty or tombstone
    }
    return -1; //otherwise return -1
}

Dictionary :: Dictionary(){
    N = 64;
    A = new struct Entry[N]; //set the dictionary size
}

struct Entry* Dictionary :: get(char key[]){
    int index = hashValue(key);   // starting point of search
    for(int i=index; i<64+index; i++){
        if(A[i%N].null){
            if(A[i%N].tombstone)
                continue; //skip if its tombstone
            else
                return NULL; 
        }
        if(comp_str(key, A[i%N].key)){  //complare two char lists
            return &A[i%N];  //return the pointer of Entry we found to have same key as asked
        }
    }
    return NULL;
}

bool Dictionary :: put(struct Entry e){
    int index = findFreeIndex(e.key);
    if(index == -1)
        return false;      //if theres no space
    A[index].key = e.key;    //copy the value and key of e to entry of dictionary list 
    A[index].value = e.value;
    A[index].tombstone = false; //set tombstone and null to false
    A[index].null = false;
    return true;
}

bool Dictionary :: remove(char key[]){
    Entry *e = get(key); 
    if(e == NULL)  // if theres no element with asked key 
        return false;
    e->null = true;  //if there is, set null and tombstone to true
    e->value = 0;
    e->tombstone = true;
    return true;
}
