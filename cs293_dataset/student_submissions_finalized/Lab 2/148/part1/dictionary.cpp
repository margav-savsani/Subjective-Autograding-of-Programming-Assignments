#include "dictionary.h"
#include <cmath>
#include <limits>

// The constants, as described in the lecture. I have taken the null placeholder to be the largest value inside the 
const int NULLINT= std::numeric_limits<int>::max();
const int TOMBSTONE= std::numeric_limits<int>::min();
const int X = 33;
const float PHI = (sqrt(5)-1)/2;
const int M = 64;


double frac(double d){
        // Helper for the hashValue function
    return d - floor(d);
}

int Dictionary::hashValue(char key[]){
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
  int Dictionary::findFreeIndex(char key[]){
    int index = hashValue(key);
    // Check if the index is empty or tombstone
    if(A[index].value == NULLINT || A[index].value == TOMBSTONE){
        return index;
    }
    for (int i = 0; i < DICT_SIZE; i++) {
        // Agin check for empty or tombstone. We use %DICT_SIZE so that it loops around
        if(A[(index+i)%DICT_SIZE].value == NULLINT || A[(index+i)%DICT_SIZE].value == TOMBSTONE){
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
  struct Entry * Dictionary::get(char key[]){
    int index = hashValue(key);
    int original = index;
        while(A[index].value != NULLINT || A[index].value == TOMBSTONE){

            if(strcmp(A[index].key, key) == 0 && A[index].value!=TOMBSTONE) return &A[index];
            index += 1;
            index %= DICT_SIZE;
            
            if(index == original) break;
        }
    return NULL;
  }

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool Dictionary::put(struct Entry e){
    // If the key exists, update it
    Entry *a = get(e.key);
    if(a!=NULL){
            a->value = e.value;
            return true;
    }

    // Find the next free index
    int index = findFreeIndex(e.key);
    // If couldn't find an index, return false;
    if(index == -1) return false;
    A[index] = e;
    N+=1;
    return true;
  }

  // Remove the given key; return true if success, false if failure (given key not present)
  bool Dictionary::remove(char key[]){
    Entry *a = get(key);
    if(a!=NULL){
        a->value=TOMBSTONE;
        return true;
    }
    return false;
  }
