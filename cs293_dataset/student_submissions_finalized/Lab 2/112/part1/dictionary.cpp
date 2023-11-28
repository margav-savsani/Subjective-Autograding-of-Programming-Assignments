#include "dictionary.h"
#include <cmath>

Dictionary::Dictionary() {
    N = DICT_SIZE;
    A = new Entry[N];
}

int Dictionary::hashValue(char key[]) {
    int x = 3;              // value of x in polynomial accumulartion
    long long integerKey = 0;       // stringkey converted to int key

    for(int i = 0; key[i] != '\0'; i++) {
        integerKey = (integerKey*x) + key[i];
    }

    long double phi=(sqrt(5)-1)/2;       //conjugat of golden ratio
    long double kA = integerKey * phi;
    long double intPart;
    double fracPart = modf(kA, &intPart);

    double floorMe = N*fracPart;       // floor this number to get final hash

    modf(floorMe, &intPart);

    return round(intPart);
}

int Dictionary::findFreeIndex(char key[]) {
    int initialHashValue = hashValue(key);
    int freeIndex = initialHashValue;

    while((A[freeIndex].is_tombstone == true) || (A[freeIndex].is_filled == true)) {
        freeIndex = (freeIndex+1)%N;
        if (freeIndex == initialHashValue) {
            return -1;
        }
    }
    return freeIndex;
}

struct Entry *Dictionary::get(char key[]) {
    int initialHashValue = hashValue(key);
    int freeIndex = findFreeIndex(key);
    int index=initialHashValue;

    for(;index != freeIndex; index = (index+1)%N) {
        if (strcmp(A[index].key,key)==0) {
            return &A[index];
        }
    }
    return NULL;
}

bool Dictionary::put(struct Entry e) {
    int freeIndex = findFreeIndex(e.key);
    if (freeIndex == -1) return false;

    e.is_tombstone = false;
    e.is_filled = true;

    A[freeIndex] = e;
    return true;
}

bool Dictionary::remove(char key[]) {
    int initialHashValue = hashValue(key);
    int freeIndex = findFreeIndex(key);
    int index=initialHashValue;

    for(;index != freeIndex; index = (index+1)%N) {
        if (strcmp(A[index].key,key)==0) {
            A[index].is_tombstone = true;
            return true;
        }
    }
    return false;
}
