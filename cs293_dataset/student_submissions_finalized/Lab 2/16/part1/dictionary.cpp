#include <iostream>
#include "dictionary.h"
#include <cmath>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
using namespace std;

const double FIB = (sqrt(5) - 1) / 2;

// Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
int Dictionary::hashValue(char key[]){
    //I have defined an extra variable p to take have a return pointer for int part of number returned bby modf function
    double t = 0, p = 0;

    //Here rather than first doing polynoimial accumulation and then doing fibonacci compression, I have recursively \
    found the mod 1 by opening up the brackets so that I never get an overflow

    // Checking if empty string is given or not, if given its empty the generator should give 0 as intermediate value
    if (key[0] != '\0'){
        t += (int(key[0])*FIB);
        int i = 1;
        int x = 37;
        while(key[i] != '\0'){
            //This is the way I have handled overflow by using mod 1 in each intermediate steps complying with correctness \
            of math.
            t = (modf(((modf(t,&p))*x),&p)) + modf(modf((int(key[i])*FIB),&p),&p);
            i += 1;
        }
        t = modf((modf(t,&p)*x),&p);
    }
    return int(floor(t*DICT_SIZE));
}

// Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
int Dictionary::findFreeIndex(char key[]){
    int hashV = hashValue(key);
    //Checking if for the chain of elements present after hash value produced, is there an empty slot or not, as insert don't care about \
    tombstone, that is not handled here
    for (int i = hashV; i < hashV + N; i++){
        int j = i % N;
        if(!A[j].ispresent){
            return j;
        }
    }
    return -1;
}

// Default constructor
Dictionary::Dictionary(){
    //initialising the required variables 
    N = DICT_SIZE;
    A = new Entry[N];
    for (int i = 0; i < N; i++){
        A[i].tombstone = false;
        A[i].ispresent = false;
    }
}

// Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
struct Entry *Dictionary::get(char key[]){
    int hashV = hashValue(key);
    for (int i = hashV; i < hashV + N; i++){
        int j = i % N;
        if(!A[j].ispresent && !A[j].tombstone){
            return NULL;
        }
        else if(A[j].tombstone) continue;
        else{
            if (strcmp(A[j].key,key) == 0) return &A[j];
        }
    }
    return NULL;
}


// Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
bool Dictionary::put(struct Entry e){
    int hashV = findFreeIndex(e.key);
    if (hashV < 0) return false;
    A[hashV].ispresent = true;
    A[hashV].tombstone = false;
    strcpy(A[hashV].key,e.key);
    A[hashV].value = e.value;
    return true;
}

// Remove the given key; return true if success, false if failure (given key not present)
bool Dictionary::remove(char key[]){
    // Checking if any element with given keyb is present or not, and then deleting and returning true or false accordingly.
    int hashV = hashValue(key);
    for (int i = hashV; i < hashV + N; i++){
        int j = i % N;
        if(!A[j].ispresent && !A[j].tombstone){
            return false;
        }
        else if(A[j].tombstone) continue;
        else{
            if (strcmp(A[j].key,key) == 0){
                A[j].ispresent = false;
                A[j].tombstone = true;
                return true;
            }
        }
    }
    return false;
}