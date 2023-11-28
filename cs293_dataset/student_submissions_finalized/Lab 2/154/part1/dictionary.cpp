#include "dictionary.h"
#include<math.h>

int Dictionary::hashValue(char* key){
    int x = 33;   // x value for polynomial accumulation
    double PHI = (sqrt(5) - 1)/2;  // fibonacci constant for compression mapping

    long long hash = 0;
    long long m = 1610612741; // large prime number

    for(int i=0; i<32 && key[i]!= 0; i++){
        hash = (hash*x + key[i] - 'A' + 1) % m;  // polynomial accumulation
    }
    double frac = hash*PHI - int(hash*PHI); // fractional part
    return int(frac*N); // compresssed hash value

}

int Dictionary::findFreeIndex(char* key){
    // go over index starting from initial hash value until we get a NULL_KEY or a TOMBSTONE
    int index = hashValue(key); 
    int idx;
    for(int i=0; i<N; i++){
        // check only N indexes as length of array fixed
        idx = (index + i)%N;
        if(A[idx].key[0] == NULL_KEY || A[idx].key[0] == TOMBSTONE)
            return idx;
    }
    return -1;  // if no free index
}

Dictionary::Dictionary(){
    // initialisation
    N = DICT_SIZE;
    A = new Entry[N];
}

bool isequal(char* a, char*b){
    // manually defined function to check if two char strings are equal or not
    for(int i=0; i<32; i++){
        if(a[i] != b[i]) return false;
        if(a[i]==0 && b[i] == 0) return true;
    }
    return true;
}

Entry* Dictionary::get(char* key){
    // go over indexes starting from initial hash value until we encounter the given key
    int index = hashValue(key);
    int idx = index;
    for(int i=0; i<N && A[idx].key[0] != NULL_KEY; i++){  
        // check only N indexes as length of array fixed
        idx = (index + i)%N;
        if(isequal(key, A[idx].key)) 
            return &A[idx];
    }
    return NULL;  // if not found return NULL
}

bool Dictionary::put(Entry e){
    // find a freeindex and insert that element
    int idx = findFreeIndex(e.key);
    if(idx == -1) return false;  // if no index available return false
    
    for(int i=0; i<32; i++){
        A[idx].key[i] = e.key[i];
    }
    A[idx].value = e.value;
    return true;
}

bool Dictionary::remove(char* key){
    // go over indexes starting from initial hash value until we encounter the given key to delete
    int index = hashValue(key);
    int idx = index;
    for(int i=0; i<N && A[idx].key[0] != NULL_KEY; i++){
        // check only N indexes as length of array fixed
        idx = (index + i)%N;
        if(isequal(key, A[idx].key)) {
            A[idx].key[0] = TOMBSTONE;  // put tombstone in that place
            return true;
        }
    }
    return false; // if no such element present return false
}

