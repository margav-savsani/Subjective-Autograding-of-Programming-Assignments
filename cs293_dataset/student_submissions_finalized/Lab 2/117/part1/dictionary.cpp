#include <iostream>
#include<bits/stdc++.h>
#include "dictionary.h"
#include <string>
#include<string.h>
using namespace std;

// # indicates tmbstone
// ! indicates Null pointer
// use 37 for the hash code mapping, 

bool mystrcmp(char key1[], char key2[]){// Function to check whether 2 char arrays are same or not
    for(int i =0;true;i++){
        if(key1[i] != key2[i]) return false;
        if(key1[i] == key2[i] && key1[i] == '\0') return true;
    }
}


Dictionary::Dictionary(){
    N = DICT_SIZE;// stores the size of dictionary
    A = new struct Entry[N];// creates a dictionary
    for(int i = 0; i < N; i++){
        A[i].key[0] = '!';
        A[i].key[1] = '\0';// Stores !\0 in all elements to signify that all places are empty
    }
}

int Dictionary::hashValue(char key[]){
    unsigned int hashCode=0;//Hash code map, using polynomial, convert string to int
    int i = 0;
    while(key[i]!= '\0'){
        hashCode = (37*hashCode + int(key[i])-96)%203429;// used 203429(big prime) to counter overflow
        i++;
    }// int formed
    double fractional = 0.61803398875*hashCode; // fibonacci compression map
    hashCode = fractional;
    fractional-= hashCode;
    hashCode = fractional * DICT_SIZE;
    return hashCode;// done
}

int Dictionary::findFreeIndex(char key[]){// finds the index of a key, returns -1 if not present
    int index = hashValue(key);// find hash
    for(int i = 0; i < DICT_SIZE; i++){// checks for elements starting from hash until we get a tombstone or an empty place, runs 
                                        // DICT_SIZE times to check for all the array
        if(mystrcmp(A[(index+i)%DICT_SIZE].key ,"#")|| mystrcmp(A[(index+i)%DICT_SIZE].key, "!")) return (index+i)%DICT_SIZE;
    }
    return -1;// if no tombstone/empty place found in array, array is full so returns -1
}

struct Entry* Dictionary::get(char key []){// returns the pointer of an element given its key, returns NULL if element not present
    int index = hashValue(key);// find hash value
    struct Entry* ans = NULL;
    
    for(int i = 0; i<DICT_SIZE; i++){
        if(mystrcmp(A[(index+i)%DICT_SIZE].key, "!")) return ans;// if we get an empty space, then it should return NULL as that signifies the key is not present
        if(mystrcmp(A[(index+i)%DICT_SIZE].key,key)){// checks if we get the correct key
            ans = &A[(index+i)%DICT_SIZE];// stores the pointer of out entry in the ans
            break;
        }    
    }
    return ans;
}

bool Dictionary::put(struct Entry e){// inserts a given entry
    int index = findFreeIndex(e.key);// finds free index for the entry
    if(index == -1) return false;// returns false if array full
    A[index] = e;// otherwise stores the element if not full in the found index
    return true;// ans returns true
}

bool Dictionary::remove(char key[]){// remove a given key
    struct Entry* storedIn = get(key);// finds key for the element
    if(storedIn == NULL) return false;// returns false if element not present
    storedIn->key[0] = '#';// changes the key to a tombstone otherwise
    storedIn->key[1] = '\0';
    return true; // returns true as element was deleted
}