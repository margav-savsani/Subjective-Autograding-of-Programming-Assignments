#include "dictionary.h"
#include <cmath>
#include <limits>

// Placeholders: value = nullptr and key != tombstone -> null
// value = nullptr and key == tombstone -> tombstone

const int X = 33;
const float PHI = (sqrt(5)-1)/2;
const int M = 64;


double frac(double d){
        // Helper for the hashValue function
    return d - floor(d);
}

int Dictionary::hashValue(string key){
        // Note that this has the rightmost character with the highest power of x.

    double ans = key[0]*PHI;
    ans = frac(ans);
    for (int i = 1; i < 64; i++) {
            if(key[i] == '\0'){
                    break;
            }
            ans = ans*X+key[i]*PHI;
            // Doing this prevents any kind of overflow
            ans = frac(ans);
    }
    ans = floor(ans*M);
    return ans;

}
int Dictionary::findFreeIndex(string key){
        int index = hashValue(key);
        // Check if the index is empty or tombstone
        if(A[index].value == nullptr){
                return index;
        }
        for (int i = 0; i < DICT_SIZE; i++) {
                // Agin check for empty or tombstone. We use %DICT_SIZE so that it loops around
                if(A[(index+i)%DICT_SIZE].value == nullptr){
                        return (index+i)%DICT_SIZE;
                }
        }
        return -1;
}

// Default constructor
Dictionary::Dictionary(){
        N = 0;
        A = new Entry[DICT_SIZE];
}



// Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
struct Entry * Dictionary::get(string key){
        int index = hashValue(key);
        int original = index;
        // While we don't get a pure null (null that is not tombstone)
        while(A[index].value != nullptr ||A[index].key == "tombstone"){
        /* cout << "Hello"  << endl; */
                if(A[index].key == key) return &A[index];
                index += 1;
                index %= DICT_SIZE;

                if(index == original) break;
        }
        return NULL;
}

// Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
bool Dictionary::put(struct Station * s){
        Entry *e = new Entry(s);
        // If the key exists, update it
        Entry *a = get(s->name);
        if(a!=NULL){
                a->value = s;
                return true;
        }

        // Find the next free index
        int index = findFreeIndex(s->name);
        // If couldn't find an index, return false;
        if(index == -1) return false;
        A[index] = *e;
        N+=1;
        return true;
}

// Remove the given key; return true if success, false if failure (given key not present)
bool Dictionary::remove(string key){
        Entry *a = get(key);
        if(a!=NULL){
                a->value = nullptr;
                a->key="tombstone";
                return true;
        }
        return false;
}
