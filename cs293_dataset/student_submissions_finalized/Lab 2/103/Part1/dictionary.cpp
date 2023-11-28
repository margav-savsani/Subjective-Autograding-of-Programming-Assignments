#include <iostream>
#include <string.h>
#include <cmath>

#include "dictionary.h"

// Default constructor
Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new Entry[N];
}

// Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
int Dictionary::hashValue(char key[]){
	// Hash Code - Compute hash code using polynomial accumulation scheme with x=37
    unsigned int code = 0;
    unsigned int x = 37;
    for(int i = 0; key[i] != '\0'; i++){
        code = x*code + (int)key[i]; //Polynomial accumulation using Horner's rule
    }

    // Hash Compression - Fibonacci hashing scheme
    double A = (sqrt(5) - 1) / 2;
    int hash = floor(N * ((code * A) - floor(code * A)));
    return hash;
}

// Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
int Dictionary::findFreeIndex(char key[]){
	int probe = hashValue(key); // Linear probing
    int init_probe = probe; // Remembers initial probe value to detect cycle
    while(A[probe].identifier == 'O'){ // Keeps moving probe as long as probed slot is occupied
        probe = (probe + 1) % N; // Increment probe
        if(probe == init_probe) // If cycled through all slots, then table is filled
            return -1;
    }
    return probe;
}

// Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
struct Entry* Dictionary::get(char key[]){
    int probe = hashValue(key); //Linear probing
    int init_probe = probe; //Remembers initial probe value to detect cycle
    while(A[probe].identifier != 'U'){ //Keeps moving probe until probe slot is unoccupied
        if(strcmp(A[probe].key, key) == 0 && A[probe].identifier == 'O'){ //Checks if the key of the probed slot matches and the probed slot is occupied (and not tombstone instead)
            return &A[probe];
        }
        probe = (probe + 1) % N; //Increment probe
        if(probe == init_probe) //If cycled through all slots, then key does not exist in dictionary
            return NULL;
    }
    return NULL; //If unoccupied slot is encountered, then key does not exist in dictionary
}

// Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
bool Dictionary::put(struct Entry e){
	int freeIndex = findFreeIndex(e.key); //Get the next free index
    if(freeIndex == -1) //If freeIndex is -1, table is full
        return false;
    
    A[freeIndex].identifier = 'O'; //Marks slot at freeIndex as occupied
    strcpy(A[freeIndex].key, e.key); //Sets key of slot at freeIndex
    A[freeIndex].value = e.value; //Sets value of slot at freeIndex
    return true;
}

// Remove the given key; return true if success, false if failure (given key not present)
bool Dictionary::remove(char key[]){
	int probe = hashValue(key); //Linear Probing
    int init_probe = probe; //Remembers initial probe value to detect cycle
    while(A[probe].identifier != 'U'){ //Keeps moving probe until probe slot is unoccupied
        if(strcmp(A[probe].key, key) == 0 && A[probe].identifier == 'O'){ //Checks if the key of the probed slot matches and the probed slot is occupied (and not tombstone instead)
            A[probe].identifier = 'X'; //Marks probed slot as tombstone
            return true;
        }
        probe = (probe + 1) % N; //Increment probe
        if(probe == init_probe){ //If cycled through all slots, then key does not exist in dictionary
            return false;
        }
    }
    return false; //If unoccupied slot is encountered, then key does not exist in dictionary
}
