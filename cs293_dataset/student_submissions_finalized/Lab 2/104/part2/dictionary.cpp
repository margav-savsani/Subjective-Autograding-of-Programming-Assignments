#include"dictionary.h"
#include<cmath>

Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new Entry[N];
}

int Dictionary::hashValue(char key[]){

    // value for cpmuting polynomial at that value
    const int x = 37;

    // number of characters in string
    int n = 0;

    // calculating n i.e number of characters in string
    for(int i=0; i<32; ++i){
        if(key[i] != '\0') n++;
        else{
            break;
        }
    }

    // to store value of polynomial
    unsigned int poly_val = key[n-1];

    // calculating value of polynomial
    for(int i=n-2; i>=0; i--){
        poly_val = poly_val*x;
        poly_val = poly_val + key[i];
    }

    double knuth = (sqrt(5)-1)/2;

    long double fib = poly_val*knuth;
    long long int intFib = fib;

    long long int ret = N*(fib - intFib);

    return ret;

}

int Dictionary::findFreeIndex(char key[]){

    // computed hash value for given key
    int hashVal = hashValue(key);

    // we will return the first null or tombstone index we encounter starting from hash value
    for(int i=hashVal; i < N + hashVal; i++){
        int j = i%N;
        if(A[j].isFNT == 1 || A[j].isFNT == 2) return j;
    }

    // if we reach this point then the table is full
    return -1; 
}

struct Entry* Dictionary::get(char key[]){
    int hashVal = hashValue(key);

    for(int i=hashVal; i < N + hashVal; i++){

        int j = i%N;

        // if we encounter null index then that key isn't in hash table
        if(A[j].isFNT == 1) return nullptr;

        // if we encounter tombstone then we will continue our search
        else if(A[j].isFNT == 2) continue;

        // if we encounter filled index
        else if(A[j].isFNT == 0){

            // if string matches then we will return address of that index
            if(strcmp(A[j].key, key) == 0) return &(A[j]);

            // if string doesn't matches then we will coontinue our search
            else continue;
        }
    }

    // if we reach this point then we have searcheded whole table and key is not present
    return nullptr;
}

bool Dictionary::put(struct Entry e){
    int freeIndex = findFreeIndex(e.key);

    if(freeIndex == -1) return false;
    else{
        A[freeIndex] = e;
        A[freeIndex].isFNT = 0;
        return true;
    }
}

bool Dictionary::remove(char key[]){
    struct Entry *ret = get(key);

    if(ret == nullptr) return false;
    else{
        ret->isFNT = 2;
        return true;
    }
}