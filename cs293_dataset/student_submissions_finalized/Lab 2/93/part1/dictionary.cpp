#include "dictionary.h"
#include <iostream>
// #include <string.h>
#include <math.h>
// using namespace std;

// int DICT_SIZE = 64;

// struct Entry {
//   // define suitable fields here
//     char* key;  
//     int value;
//     Entry(){
//         key = new char[32]{'\0'};
//         value = 0;
//     }
//     Entry& operator = (Entry& a){     //assignment operator definition
//         strcpy(key, a.key);
//         value = a.value;
//         return *this;
//     }
// };

// class Dictionary {
//  private:
//   int N; // size of array A
//   struct Entry *A; // Array of dictionary entries

//  public:

//   // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
//   int hashValue(char key[]);

//   // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
//   int findFreeIndex(char key[]);
  
//   // Default constructor
//   Dictionary(); 

//   // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
//   struct Entry *get(char key[]);

//   // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
//   bool put(struct Entry e);

//   // Remove the given key; return true if success, false if failure (given key not present)
//   bool remove(char key[]);
// };

int Dictionary::hashValue(char key[]){
    //using polynomial hashing and fibonacci compression
    unsigned int hash_value{0};
    int c = key[0];
    int x = 41;
    int i = 0;
    while(c!=0){
        hash_value = hash_value*x+c-'0';
        i+=1;
        c = key[i];
    }
    double golden = (sqrt(5)-1)/2;
    double y = hash_value*golden;
    // hash_value = y*DICT_SIZE;
    // hash_value = hash_value%DICT_SIZE;
    hash_value = DICT_SIZE*(y-(int)y);
    hash_value%=DICT_SIZE;
    return hash_value;    
}

int Dictionary::findFreeIndex(char key[]){
    //if the first charectar of a string is \0, then it the element is assumed to be empty
    //if the first charectar is 1(ASCII), then it is assumed to be a tombstone
    int hash_value = hashValue(key);
    for(int i{0}; i<N; i++){
        int index = (hash_value+i)%N;
        if((A[index].key[0]=='\0')||(A[index].key[0]==1))
            return index;
    }
    return -1;
}

Dictionary::Dictionary(){
    //initializing the attributes
    N = DICT_SIZE;
    A = new Entry[N];
}

Entry* Dictionary::get(char key[]){
    int hash_val = hashValue(key);
    for(int i{0}; i<N; i++){  //searching until we find the element or an empty (non tombstone)
        int index = (i+hash_val)%N;
        char* word = A[index].key;
        if(strcmp(word, key)==0) //if key matches, return the location
            return A+index;
        if(word[0]=='\0') //if the word is empty, return NULL 
            return NULL;
    }
    return NULL; //return NULL, if array is full and element is not found
}

bool Dictionary::put(Entry e){
    int index = findFreeIndex(e.key); //find the location where the element is to be inserted 
    if(index==-1)  //return false if the array is full
        return false;
    A[index] = e; //assign e to the empty location
    return true;
}

bool Dictionary::remove(char c[]){
    Entry* e = get(c);
    if(e==NULL)
        return false;
    char d[1];
    d[0] = 1;
    strcpy(e->key, d);
    return true;
}

