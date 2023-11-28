#include "./dictionary.h"
#include <cmath>
#include <iostream>
using namespace std;

// Hashing constants
const double M = (sqrt(5)-1)/2;
const int p = 33;

// Special identifiers
char emptyKey = '-';
char tombstoneKey = '?';

int Dictionary::hashValue(char key[]){
    double coeffs[32];
    int size = 0;

    // Get array of all key[i]*M
    for (int i = 0; key[i] != '\0'; i++)
    {   
        coeffs[i] = ((double(key[i]))*M) - floor((double(key[i]))*M);
        size++;
    }

    double hashc=0;
    // get value of polynomial
    for(int i=size-1; i>=0; i--){
        hashc += coeffs[i];
        hashc = hashc-floor(hashc);
        hashc *= p;
        hashc = hashc-floor(hashc);
    }

    // find hashvalue
    int hashval = floor(DICT_SIZE * hashc);
    return hashval;
}

int Dictionary::findFreeIndex(char key[]){
    if(N == DICT_SIZE) return -1;      // check if full
    else{
        int look = Dictionary::hashValue(key);
        while(A[look].key[0] != emptyKey){
            look = (look+1) % DICT_SIZE;
        }
        return look;
    }
}

Dictionary::Dictionary(){
    A = new Entry[DICT_SIZE];
    N = 0;

    Entry empty;
    empty.key[0] = emptyKey;
    empty.value = 0;

    for (int i = 0; i < DICT_SIZE; i++)
    {
        A[i] = empty;
    }
    
}

struct Entry* Dictionary::get(char key[]){
    int look = Dictionary::hashValue(key);

    for (int i = look; i < DICT_SIZE; i++)
    {   
        if(A[i].key[0] == emptyKey) return NULL;
        if(A[i].key[0] == tombstoneKey) continue;
        if(string(A[i].key) == string(key)) return &A[i];
    }
    
    return NULL;
}

bool Dictionary::put(struct Entry e){
    if(N == DICT_SIZE) return false;       // check if full
    else{
        int i = Dictionary::findFreeIndex(e.key);
        A[i] = e;
        N++;
        return true;
    }
}

bool Dictionary::remove(char key[]){
    Entry* toRemove = Dictionary::get(key);
    if(toRemove == NULL) return false;
    else{
        Entry tombstone;
        tombstone.key[0] = tombstoneKey;
        tombstone.value = -1;

        *toRemove = tombstone;
        N--;
        return true;
    }
}

Dictionary::~Dictionary(){
    delete[] A;
}