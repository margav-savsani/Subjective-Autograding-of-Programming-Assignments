#include<cmath>
#include<string.h>
#include<iostream>
#include"dictionary.h"
#include <cstdlib>
using namespace std;

// Constructor for the Dictionary class
Dictionary:: Dictionary(){
    N = DICT_SIZE; // Initializing the array size as given constant
    A = new Entry[N]; // Creating a new array dynamically
    for (int i = 0; i<N; i++){ // Initializing the value of all entries as NULL_SPACE before hashing any value inside it
        A[i].status = NULL_SPACE;
        A[i].value = rand()%101; // Initializing random values to value in some range
    }
}

// Returns the hash value given the key
int Dictionary:: hashValue(char key[]){

    int x = 32; // setting x value for polynomial accumulation
    float hashvalue = 0; // for storing the hash value of the key
    int size = 0;// to store the size of the word in the key
    for(int i=0 ; key[i] != '\0' ; i++){
        size ++;
    }
    float A = 0.61803398874989; // the value of A suggested by knuth

    if (key[0]=='\0'){ // to set the hash value for empty string
        hashvalue = 0;
    }
    else{
        for(int i = size -1; i>=0 ; i--){
            hashvalue = (((x*hashvalue*A) - floor(x*hashvalue*A)) + ((key[i]*A) - floor(key[i]*A))) -
            floor(((x*hashvalue*A) - floor(x*hashvalue*A)) + ((key[i]*A) - floor(key[i]*A))); // to compute kA(mod1) recursively
        }
        hashvalue = (int)floor(N*hashvalue); 
    }
    return (int)hashvalue;
}

// Finds the free index of at which key can be inserted
int Dictionary:: findFreeIndex(char key[]){
    int hashvalue = hashValue(key); // returns a hash value between 0, N-1
    for(int i = 0; i<N;i++){
        if(A[(hashvalue+i)%N].status==NULL_SPACE||A[(hashvalue+i)%N].status==TOMBSTONE){
            return ((hashvalue+i)%N); // to return the NULL space and TOMBSTONE index to put the value there
        } 
    }
    return -1;
}

// To get the Entry corresponding for the given key
struct Entry * Dictionary:: get(char key[]){
    int hashvalue = hashValue(key);
    for(int i = 0; i<N; i++){
        if(A[(hashvalue+i)%N].status==NULL_SPACE){ // ignoring the Entry if status is a tombstone
            return nullptr; 
        }
        if(strcmp(key, A[(hashvalue+i)%N].key)==0){ // to return the Entry address if found
            return &A[(hashvalue+i)%N];
        }
    }
    return nullptr;
}

// To get the Entry corresponding for the given key
bool Dictionary:: find(char key[]){
    int hashvalue = hashValue(key);
    for(int i = 0; i<N; i++){
        if(A[(hashvalue+i)%N].status==NULL_SPACE){ // ignoring the Entry if status is a tombstone
            return false; 
        }
        if(strcmp(key, A[(hashvalue+i)%N].key)==0){ // to return the Entry address if found
            return true;
        }
    }
    return false;
}

// Function to put the Entry into the array by linear hashing
bool Dictionary:: put(struct Entry e){
    int freeindex = findFreeIndex(e.key);
    
    if (freeindex == -1){
        return false;
    }
    else{
        A[freeindex].value = e.value;
        A[freeindex].status = FULL; // to update the status of that index as full
        int i=0;
        for(;e.key[i]!='\0' ; i++){ // to copy the word in the key
            A[freeindex].key[i] = e.key[i];
        }
        A[freeindex].key[i] = '\0';
        return true;
    }
}

// To remove the Element with key given
bool Dictionary:: remove(char key[]){
    int hashvalue = hashValue(key);
    
    Entry* removeEntry = get(key);
    if(removeEntry!=nullptr){
        removeEntry->status = TOMBSTONE; // to give the value tombstone to the index once element is removed
        removeEntry->value = 0;
        for(int j = 0;j<32;j++){
             (removeEntry->key)[j] = '\0';
        }
        return true;
    }
    else{
        return false;
    }
}