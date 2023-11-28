#include <iostream>
#include <string.h>
#include <cmath>
#include "dictionary.h"
using namespace std;

Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new Entry [N];
    for(int i = 0; i < N; i++){
        A[i].key[0] == NULL;
    }
}

int Dictionary::hashValue(char key[]){
    int count = 0;
    for(; key[count] != NULL; count++){}
    int coeff[count], x = 33;
    unsigned long long int R = 0;
    for(int i = count-1; i >= 0; i--){
        coeff[i] = key[i];
        R = (R*x + coeff[i])%1000000007;
    }
    long double A = 0.618033988;
    long double f = R*A-int(R*A);
    int result = int(f*N);
    return result;
}

int Dictionary::findFreeIndex(char key[]){
    int hash = hashValue(key);
    for(int i = hash; A[hash].key[0] != NULL && hash < N; hash++){}
    if(hash < N) return hash;
    else return -1; 
}

struct Entry* Dictionary::get(char key[]){
    int hash = hashValue(key);
    string check1 = key; 
    for(int i = hash; i < 64; i++){
        string check2 = A[hash].key;
        if(check1 == check2) return &A[hash];
        if(check2[0] == NULL) return nullptr;
    }
    return nullptr;
}

bool Dictionary::put(struct Entry e){
    int x = findFreeIndex(e.key);
    if(x == -1) return false;
    else{
        A[x] = e;
        return true;
    }
}

bool Dictionary::remove(char key[]){
    Entry *e;
    e = get(key);
    if(e == nullptr) return false;
    else{
        e->key[0] == NULL;
        return true;
    }
}
