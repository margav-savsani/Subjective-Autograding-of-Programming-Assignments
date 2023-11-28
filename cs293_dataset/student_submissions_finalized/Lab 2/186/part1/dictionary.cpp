#include <iostream>
#include "dictionary.h"

Dictionary::Dictionary(){               //Constructor
    N = DICT_SIZE;          
    A = new struct Entry[N];
    for(int i = 0; i < N; i++){         //I am using -10 as an initializing value
        A[i].value = -10;
        A[i].key = new char[32];
        strcpy(A[i].key,"\0");          //I am using NUll character as an initializing key
        A[i].isTombStone = false;       //isTombstone is set to false initially
    }
}

int Dictionary::hashValue(char key[]){
    const int x = 37, M = 1e7 + 7;      // I evaluated the polynomial at x = 37
    const double fibb = 0.6180339887;   // fibb is (sqrt(5)-1)/2
    int i = 0, term = 1, hashvalue = 0; 
    char character = key[0];

    while(character!='\0'){             // Polynomial Accumulation
        character = key[i];
        hashvalue = (hashvalue + (character - '\0')*term) % M;
        term = (term*x) % M;            // Used % M inorder to prevent overflow
        i++;
    }

    double hashv = hashvalue*fibb;      // Compression using Fibonacci Hashing scheme
    hashvalue = hashvalue*fibb;
    hashvalue = int((hashv - hashvalue)*64);

    return hashvalue;
}

int Dictionary::findFreeIndex(char key[]){    
    int probe = hashValue(key);
    int initprob = probe;
    do {
        if(strcmp(A[probe].key,"\0") == 0) return probe;    //return the index of empty location
        probe = (probe + 1) % N;
    }
    while(probe != initprob);   // exit the loop if you have checked the whole array
    return -1;                  // return -1 if any empty index not found
}

struct Entry *Dictionary::get(char key[]){
    int probe = hashValue(key);
    int initprob = probe;
    do {                    //search until you get an empty location or you searched the whole array
        if(A[probe].isTombStone == true){       //if tombstone is found, then ignore it and continue
            probe = (probe + 1) % N;
            continue;
        }
        if(strcmp(A[probe].key,key) == 0){      //if key found, then return that entry
            return &A[probe];
        }
        probe = (probe + 1) % N;
    }
    while((strcmp(A[probe].key,"\0") != 0) || (initprob != probe));
    return NULL;                                //return NULL, if key not found
}

bool Dictionary::put(struct Entry e){
    int index = hashValue(e.key);
    int initindex = index;
    do {
        if(strcmp(A[index].key,"\0") == 0 || A[index].isTombStone){     //insert if the location is empty
            A[index] = e;                                               //or it is a tombstone
            return true;
        }
        index = (index + 1) % N;
    }
    while(index != initindex);              //loop through until you have searched the whole array
    return false;                           //return false if failure (array is full)
}

bool Dictionary::remove(char key[]){
    int index = hashValue(key);
    int initindex = index;
    do {
        if(strcmp(A[index].key,key)==0){    //delete the key if it is found
            A[index].isTombStone = true;    //set tombstone to true and other values to thier initials
            A[index].value = -10;
            strcpy(A[index].key,"\0");
            return true;
        }
        index = (index + 1) % N;
    }
    while(index != initindex);              //loop through until you have searched the whole array
    return false;                           //return false if key to be deleted not found
}