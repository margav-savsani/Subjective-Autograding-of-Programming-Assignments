#include "dictionary.h"
#include <iostream>
#include <cmath>
using namespace std;

Dictionary::Dictionary() {
    N = DICT_SIZE;                  // N takes the max size possible
    A = new Entry[N];               // creating an array of Entries
    for(int i=0; i<N; i++) {
        strcpy(A[i].key, "\0");     // initialising key to null character
        A[i].value = -1;            // initialising value to -1
    }
}

int Dictionary::hashValue(char key[]) {
    int x = 31;                     // x for polynomial
    double a = (sqrt(5)-1)/2;        // a for fibonacci hashing
    int n=0;                        // stores the index of the end of key , i.e. null char
    double intpart=0;               // dummy unused variable for modf function

    for(; n<32; n++) {                  // finding n or basically the length of string
        if(key[n]=='\0')    break;
    }

    double hash = int(key[n-1]);
    for(int i=n-2; i>=0; i--) {
        hash = hash*x + int(key[i]);    // calculation of polynomial using horner's rule
    }
    hash = floor(N*(modf((hash*a), &intpart)));  // fibonacci hashing
    
    return (int)hash;
}

int Dictionary::findFreeIndex(char key[]) {
    int hash = hashValue(key);
    int i=0;
    for(; i<N; i++) {
        if(strcmp(A[hash].key, "\0") == 0)      // encountering empty space or tombstone
            break;
        else
            hash = (hash+1) % N;            // checking next index when coliision occurs
    }
    if (i==N)           // when no free index found
        return -1;
    else
        return hash;    // free index value
}

struct Entry* Dictionary::get(char key[]) {
    int hash = hashValue(key);
    for(int i=0; i<N; i++) {
        if(A[hash].value == -1)                 // encountering empty space before an element
            return NULL;                        // meaning element not present
        else if(strcmp(key,A[hash].key) == 0)   // key match successful
            return &(A[hash]);
        else                        // key mismatch or tombstone
            hash = (hash+1)%N; 
    }
    return NULL;
}

bool Dictionary::put(struct Entry e) {
    int index = findFreeIndex(e.key);
    if(index == -1)      // no free index available
        return false;
    else                // free index available
        A[index] = e;   // assigning entry to given entry
    return true;
}

bool Dictionary::remove(char key[]) {
    int hash = hashValue(key);
    for(int i=0; i<N; i++) {
        if(A[hash].value == -1)     // encountered an empty space before finding element
            return false;           // element cannot be present

        else if(strcmp(A[hash].key, key) == 0) {    // key match successful
            strcpy(A[hash].key, "\0");              // chaning key value to null before deleting (i.e. decalring as tombstone)
            return true;
        }

        else                    // encountered tombstone or key mismatch
            hash = (hash+1)%N;
    }
    return false;
}

/* TOMBSTONE : key = "\0"
               value = (value of previously stored element)

   EMPTY SPACE : key = "\0"
                 value = -1

   OCCUPIED : key not empty
              value non-negative

    the constraint here is that the value entered cannot be -1 and it's a perfectly okay assumption
    as it is a program for a railways*/
