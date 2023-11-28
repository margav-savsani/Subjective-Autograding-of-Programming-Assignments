#include "dictionary.h"
#include<cmath>

const int FULL = 1;
const int EMPTY = 0;
const int TOMBSTONE = -1;
const float CONJUGATE_GOLDEN = (std::sqrt(5) - 1)/2;

Entry::Entry(){
    this->type = EMPTY;
}

int Dictionary::hashValue(char key[]){

    unsigned int hash = 0;
    const int FACTOR = 33;
    const int M = 10061; 

    while(*key != 0){ 
        hash = (hash*FACTOR + int(*key)) % M;
        key++;
    }

    float reduced_hash = hash*CONJUGATE_GOLDEN;
    reduced_hash = reduced_hash - int(reduced_hash);
    
    int final_hash = reduced_hash*N;
    return final_hash;
}

int Dictionary::findFreeIndex(char key[]){
    int index = hashValue(key);

    for(int i = 0; i < N; i++){
        if(A[(i + index)%N].type == EMPTY || A[(i+index) % N].type == TOMBSTONE){
            return ((i + index)%N);
        }
    }
    return -1;    
}

Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new Entry[N];
}

Entry* Dictionary::get(char key[]){
    int index = hashValue(key);

    for(int i = 0; i < N; i++){
        if(A[(index + i) % N].type == TOMBSTONE){
            continue;
        }

        if(A[(index + i) % N].type == EMPTY){
            return nullptr;
        }

        if(std::string(key) == std::string(A[(index + i) % N].key)){
            return &A[index];
        }
    }

    return nullptr;
}

bool Dictionary::put(Entry e){
    int index = findFreeIndex(e.key);
    
    if(index >= 0){
        e.type = FULL;
        A[index] = e;
        return true;
    }

    else return false;
}

bool Dictionary::remove(char key[]){
    Entry* elem = get(key);

    if(elem != nullptr){
        elem->type = TOMBSTONE;
        return true;
    }

    else return false;
}