#include"dictionary.h"
#include<cmath>

using namespace std;

int Dictionary::hashValue(char key[]){

    int slot;
    int polyVar = 33;
    double polySum = 0;
    double phi = (sqrt(5) - 1.0) / 2.0 ;



    // implementing polynomial accumulation
    for (int i = 0; key[i] != '\0'; i++){
        polySum = (polyVar * polySum + int(key[i]) * phi) - floor(polyVar * polySum + int(key[i]) * phi);
    }


    //Fibonacci hashing
        

    slot = floorf128(N * (polySum - floorf128(polySum)));

    return slot;
}

Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new struct Entry[DICT_SIZE];
}

int Dictionary :: findFreeIndex(char key[]){
    int slot = hashValue(key);
    int numProbed = 0;
    bool found  = false;

    
    while (!found && numProbed < N){
        if (A[slot].isOccupied != 1){

            numProbed++;
            return slot;
            found = true;
        } else {
            numProbed++;
            slot = (slot + 1) % N;
        }

    }
    return -1;

}

struct Entry* Dictionary::get(char key[]){
    int slot = hashValue(key);
    int numProbed = 0;
    bool found = false;

    while (numProbed < N && A[slot].isOccupied != 0){
        numProbed++;

        if (strcmp(key, A[slot].key)){
            return &A[slot];
        }

        
        slot = (slot + 1) % N;
    }

    return NULL;


}

bool Dictionary :: put(struct Entry e){
    int slot = findFreeIndex(e.key);
    if (slot == -1) return false;

    A[slot] = e;
    A[slot].isOccupied = 1;
    return true;
}

bool Dictionary :: remove(char key[]){
    Entry * remElt = get(key);

    if (remElt != NULL){
        remElt -> isOccupied = -1;
        return true;
    }
    else {
        return false;
    }

}

