#include <iostream>
#include "dictionary.h"
#include <cmath>

// made random tombstone 
char TOMBSTONE[2] = "-";

using namespace std;

Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new Entry[N];
}

//calculates hashValue as per given in question
int Dictionary::hashValue(char key[]){
    int i = 0;
    float a = (sqrt(5) - 1)/2, val = 0;
    while(key[i] != '\0'){
        val = fmod((fmod(a*key[i]*round(pow(33, i)), 1) + fmod(val, 1)),1);
        i++;
    }
    val = floor(val*DICT_SIZE);
    return int(val);
}

// finds free index, where new Entry can be entered
int Dictionary::findFreeIndex(char key[]){
    int idx = hashValue(key), i = 0;
    while(A[idx].isFilled && i < N){
        if(A[idx].key == TOMBSTONE)
            return idx;
        idx = (idx+1) % N;
        i++;
    }
    if(i == N)
        return -1;
    else
        return idx;
}

// searches for an entry, and returns a pointer to it
struct Entry* Dictionary::get(char key[]){
    int idx = hashValue(key), i = 0;
    while(A[idx].isFilled && i < N){
        if(strcmp(A[idx].key, key) == 0){
            return &A[idx];
        }
        i++;
        idx = (idx+1) % N;
    }
    return NULL;
}

// puts an entry into the dictionary
bool Dictionary::put(struct Entry e){
    int idx = findFreeIndex(e.key);
    if(idx == -1)
        return false;
    else{
        A[idx] = e;
        A[idx].isFilled = true;
        return true;
    }
}

//removes an entry from the dictionary
bool Dictionary::remove(char key[]){
    struct Entry* ptr = get(key);
    if(ptr == NULL)
        return false;
    else{
        for(int i = 0; i < sizeof(ptr->key);  i++ ) {
            ptr->key[i] = (char)0;
        }
        ptr->key[0] = '-';
        ptr->key[1] = '\0';
        ptr->isFilled = true;
        ptr->value = -1;
        return true;
    }
}

