#include "dictionary.h"
#include <cmath>
#define INT32_MAX 2147483647

int polynomial_hashmap(char key[], int base=37){
    long long ans = 0; // we store it in a long long so that even if it overflows over int during an operation, it will not overflow past long, and will be below int again when we take % INT32_MAX.
    for (int i = 0; key[i] != '\0'; i++)
        ans = ((ans * base) + key[i]) % INT32_MAX;
    return int(ans);
}

// Default constructor
Dictionary::Dictionary(): N(DICT_SIZE), A(new Entry[DICT_SIZE]){}

// Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
int Dictionary::hashValue(char key[]){
    double kA = polynomial_hashmap(key, 37) * (std::sqrt(5)-1)/2; // A = 1/phi. Fibonacci Hashing.
    return int(N * (kA - int(kA))); 
}

// Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
int Dictionary::findFreeIndex(char key[]){
    int original = hashValue(key);

    // go around the hashtable and look for an unoccupied spot.
    int i = original;
    do {
        if (A[i].isEmpty || A[i].isTomb)
            return i;
        i = (i + 1) % N;
    } while(i != original);
    return -1; // if the table is full.
}

// Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
struct Entry *Dictionary::get(char key[]){
    int original = hashValue(key);

    // go around the hashtable and look for the key. To speed up the search, we note that if at any point we find an empty entry, then the key is not in the table.
    int i = original;
    do {
        if (A[i].isEmpty)    
            return NULL; // not found.

        // else the entry is a tomb or is occupied.
        if (A[i].isTomb || strcmp(A[i].key, key) != 0){
            i = (i + 1) % N;
            continue;
        }
        return &A[i];
    } 
    while(i != original);
    return NULL; // the key is not in the table. We reach here only when the key is not present and the table is full(else we already have returned).
}

// Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
bool Dictionary::put(struct Entry &e){
    // we assume that e.key is a valid char array, possibly the empty string(but NOT NULL)
    int index = findFreeIndex(e.key);
    if (index == -1) return false; // array is full, cannot add another Entry.
    A[index] = e;
    A[index].isEmpty = false;
    A[index].isTomb = false;
    return true;
}

// Remove the given key; return true if success, false if failure (given key not present)
bool Dictionary::remove(char key[]){
    Entry *pos = get(key);
    if (!pos) return false; // given key is not present in the dictionary.
    pos->isTomb = true; // place a tomb there.
    return true;
}
