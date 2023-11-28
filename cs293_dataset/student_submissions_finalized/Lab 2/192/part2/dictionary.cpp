#include"dictionary.h"
#include<cmath>

using namespace std;

template<class T>int Dictionary<T>::hashValue(char key[]){

    int slot = 0;
    int polyVar = 33;
    double polySum = 0;
    double phi = (sqrt(5) - 1.0) / 2.0 ;



    // implementing polynomial accumulation
    for (int i = 0; key[i] != '\0'; i++){
        
        polySum = (polyVar * polySum + int(key[i]) * phi) - floor(polyVar * polySum + int(key[i]) * phi);
        //cout << i << endl;
    }


   // take only the fractional part of the final sum
    slot = floorf128(N * (polySum - floorf128(polySum)));
   
    return slot;
}

template <class T>Dictionary<T>::Dictionary(){
    N = DICT_SIZE;
    A = new T[64];
}

template<class T> int Dictionary<T>:: findFreeIndex(char key[]){
    int slot = hashValue(key);
    
    int numProbed = 0;
    bool found  = false;

    //search for a free index in the array 
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

template<class T> T* Dictionary<T>::get(char key[]){
    int slot = hashValue(key);
    

    int numProbed = 0;
    bool found = false;
    
    //search for an occupied slot in the array
    while (numProbed < N && A[slot].isOccupied != 0){
        numProbed++;
        
        //if the element is actually occupied
        if (!strcmp(key, A[slot].key) && A[slot].isOccupied != -1){
            
            return (A + slot);
        } else {
        //if the slot was a tombstone then move ahead

        
        
        slot = (slot + 1) % N;
        }
    }
    //
    return NULL;


}

template<class T>bool Dictionary<T>:: put(T e){
    int slot = findFreeIndex(e.key);
    if (slot == -1) return false;


    //create a new element at the slot
    strcpy(A[slot].from.stName, e.from.stName);
    strcpy(A[slot].to.stName, e.to.stName);
    A[slot].startTime = e.startTime;
    A[slot].finishTime = e.finishTime;
    A[slot].isOccupied = 1;
    return true;
}

template <class T> bool Dictionary<T> :: remove(char key[]){
    T * remElt = get(key);
    //if element was not found
    if (remElt != NULL){
        remElt -> isOccupied = -1;
        return true;
    }
    else {
        return false;
    }

}



