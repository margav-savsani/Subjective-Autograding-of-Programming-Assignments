#include "dictionary.h"
#include <cmath>
Dictionary::Dictionary(){
    N = 64; // size of array
    A = new Entry[N];
    for(int i=0; i<N; i++){
        A[i].key=NULL; // initializing every key to NULL
    }
}

int Dictionary::hashValue(char key[]){
    double euler=(sqrt(5)-1)/2; // used in fibonacci hashing

    int i=0, prehash=0; // defining variables for polynomial accumulation
    int factor=1;
    while(key[i]!='\0'){
        prehash += ((key[i])*factor) % 379931; // modulo division by large prime number,
        factor = (factor*41) % 379931;         // to avoid overflow
        i++;
    }
    float fibhash = prehash*euler - floor(prehash*euler); // fibonacci hashing
    fibhash = floor(fibhash*DICT_SIZE);
    int hash = fibhash;
    return hash;
}

int Dictionary::findFreeIndex(char key[]){
    if(strcmp(key,"tombstone") == 0){ // banning use of "tombstone" as a key
        std::cout << "\"tombsone\" is a keyword, cannot use it as a key" << std::endl;
        return -1;
    }
    int hash = hashValue(key);
    int index = hash;
    while( A[index].key != NULL && strcmp(A[index].key, "tombstone")){ // both null pointers and tombstones denote free indices
        index = (index+1)%DICT_SIZE; 
        if(index == hash) return -1; // if index looped back to original position, array is full
    }
    return index;
}

struct Entry *Dictionary::get(char key[]){
    if(strcmp(key,"tombstone") == 0){ // banning use of "tombstone" as a key
        std::cout << "\"tombsone\" is a keyword, cannot use it as a key" << std::endl;
        return NULL;
    }
    int hash = hashValue(key);
    int index = hash;
    while(A[index].key != NULL){
        if(strcmp(A[index].key, key) == 0){ // comparing key with each entry's key
            return A+index;
        }
        index = (index+1)%DICT_SIZE;
        if(index == hash) break; // dictionary full, key not found     
    }
    return NULL;
}

bool Dictionary::put(struct Entry e){
    int index = findFreeIndex(e.key);
    if(index == -1) return 0;
    A[index] = e; // inserting new entry at first valid index (can be tombstone or null entry)
    return 1;
}

bool Dictionary::remove(char key[]){
    struct Entry *e = get(key);
    if (e == NULL) return 0;
    strcpy(e->key,"tombstone"); // removing entry by changing key to "tombstone", dummy value used to denote tombstone
    return 1;
}