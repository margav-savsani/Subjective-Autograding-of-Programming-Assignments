#include "planner.h"
#include<cmath>

const int FULL = 1;
const int EMPTY = 0;
const int TOMBSTONE = -1;
const float CONJUGATE_GOLDEN = (std::sqrt(5) - 1)/2;

int Dictionary::hashValue(std::string key){ //Returns hash value of string
    unsigned int hash = 0;
    const int FACTOR = 33;
    const int M = 10061; 

    for(int i = key.size(); i >= 0; i--){
        hash = (hash*FACTOR + int(key[i])) % M;
    }

    float reduced_hash = hash*CONJUGATE_GOLDEN;
    reduced_hash = reduced_hash - int(reduced_hash);
    
    int final_hash = reduced_hash*N;
    return final_hash;
}

int Dictionary::findFreeIndex(std::string key){ //Finds free index for string in dictionary
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
    A = new Station[N];
}

Station* Dictionary::get(std::string key){ //Returns pointer to station with given name
    int index = hashValue(key);

    for(int i = 0; i < N; i++){
        if(A[(index + i) % N].type == TOMBSTONE){
            continue;
        }

        if(A[(index + i) % N].type == EMPTY){
            return nullptr;
        }

        if(key == A[(index + i) % N].name){
            return &A[index];
        }
    }

    return nullptr;
}

bool Dictionary::put(Station e){ //Inserts station in dictionary
    int index = findFreeIndex(e.name);
    
    if(index >= 0){
        e.type = FULL;
        A[index] = e;
        return true;
    }

    else return false;
}

bool Dictionary::remove(std::string key){ //Removes from dictionary
    Station* elem = get(key);

    if(elem != nullptr){
        elem->type = TOMBSTONE;
        return true;
    }

    else return false;
}