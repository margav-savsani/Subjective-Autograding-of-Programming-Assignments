#include <cmath>
#include "dictionary.h"

using namespace std;

int Dictionary::hashValue(char key[]){
// Hash code map : Polynomial Accumulation, Compression map : Fibonacci hashing scheme

    // Finding Number of characters in the string    
    int l = 0;
    for( int i = 0; key[i] != '\0'; i++ ){
        l++;
    }

    double const x = 37.0;
    double A = (sqrt(5.0) - 1.0)/2.0;

    double temp = key[l-1] * A;
    for( int i=0; i < 2*l - 2; i++ ){
        if(i%2 == 0){
            temp *= x;
        }
        else{
            temp += key[l-1 - i] * A;
        }

        temp = temp - double(floor(temp)); //Same as fractional part of newKey

    }

    // temp = frac( kA mod 1 ) 
    // newKey = floor ( m * temp )
    // m = size of hash table = N

    temp = temp - double(floor(temp));

    int newKey = floor( N * temp );

    // cout << "hash value: " << newKey << endl;

    return newKey;
}


int Dictionary::findFreeIndex(char key[]){
    /*
        When space is empty, value = 0.
        When space is occupied, value = 1.
        When space is a Tombstone, value = -1. 
    */

    int startPos = hashValue(key);
    int i = startPos;
    while(A[i].value >= 1 || A[i].value == -1){
        i = (i + 1) % N;

        if(i == startPos) return -1;
    }

    // cout << "Free index: " << i << endl;

    return i;
}

Dictionary::Dictionary(){
    N = DICT_SIZE;

    A = new Entry[N];

    for(int i=0; i<N; i++){     // Initializing array of entries, A
        Entry e = {"\0", 0};
        
        A[i] = e;
    }

}

//Compares two keys, if equal, returns true else false
bool compareKeys(char key1[], char key2[]){
    
    bool bothSame = true;
    for(int i=0; i<32; i++){

        if(key1[i] == '\0' || key2[i] == '0') break;
        
        if(key1[i] != key2[i]){
            bothSame = false;
            break;
        }
    }

    return bothSame;
}


struct Entry *Dictionary::get(char key[]){

    Entry *e = NULL;

    int i = hashValue(key);

    while( A[i].value >= 1 || A[i].value == -1){    //Looping while I either encounter an ENTRY or a TOMBSTONE
        
        if(A[i].value == -1) continue;  // Tombstone are to be ignored while finding Entry.
        
        if(compareKeys(key, A[i].key)){ 
            e = A + i;
            

            break;
        }

        i = (i+1) % N;

        if(i == hashValue(key)) return e;
    }

    return e;
}

bool Dictionary::put(struct Entry e){
    int i = findFreeIndex(e.key);

    if(i == -1){
        // cout << "Insertion failed" << endl;
        return false;
    };

    A[i] = e;
    // cout << "Insertion successful" << endl;
    return true;
}

bool Dictionary::remove(char key[]){
    Entry *e = get(key);

    if(e == NULL) return false;

    e->value = 0;   // Converting the entry into a tombstone.

    return true;
}




