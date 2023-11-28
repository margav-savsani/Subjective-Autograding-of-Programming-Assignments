#include <iostream>
#include "dictionary.h"

using namespace std;

Dictionary::Dictionary(){
    N = 64;
    A = new Entry[64];
    for (int i = 0; i < N; i++){
        strcpy(A[i].key, "");
        A[i].value = 0;
    }
}

int Dictionary::hashValue(char key[]){
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++){
        int dig = key[i] - 'a';
        for (int j = i; j > 0; j--){
            dig = (dig * 31) % N;
        }
        sum = (sum + dig) % N;
    }
    return sum;
}

int Dictionary::findFreeIndex(char key[]){
    int pos = hashValue(key);
    while (pos < N){
        if (strcmp(A[pos].key, "") == 0 || strcmp(A[pos].key, "tombstone") == 0) return pos;
        else pos ++;
    }
    return -1;
}

struct Entry *Dictionary::get(char key[]){
    int pos = hashValue(key);
    for (int i = pos; strcmp(A[i].key, "") != 0; i++){
        if (strcmp(key, A[i].key) == 0){
            return &A[i];
        }
    }
    return NULL;
}

bool Dictionary::put(struct Entry e){
    int pos = findFreeIndex(e.key);
    if (pos == -1) return false;
    else{
        strcpy(A[pos].key, e.key);
        A[pos].value = e.value;
        return true;
    }
}

bool Dictionary::remove(char key[]){
    for (int i = 0; i < N; i++){
        if (strcmp(key, A[i].key) == 0){
            strcpy(A[i].key, "tombstone");
            A[i].value = 0;
            return true;
        }
    }
    return false;
}