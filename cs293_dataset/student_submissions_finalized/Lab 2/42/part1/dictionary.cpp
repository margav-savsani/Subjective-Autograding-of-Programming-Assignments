#ifndef DICTIONARY_CPP
#define DICTIONARY_CPP

#include "dictionary.h"
#include "cstring"
#include <cmath>

char s[1] = {'\0'}; 
char t[1] = {(char)2};

int len_str(char key[]){
    int len = 0;
    for (int i=0;key[i] != '\0';i++){
        len+=1;
    }
    return len;
}

Dictionary::Dictionary(){
    this->N = DICT_SIZE;
    for (int i=0;i<N;i++){
        strcpy(A[i].key,s);
        A[i].value = 0;
    }
}

int Dictionary::hashValue(char key[]){
    int dummy = 0;
    int polyres = 0;
    int len = len_str(key);
    int m = 1000000009;
    int p = 11111;
    for (int i=len-1;i>=0;i--){
        polyres = (((polyres*p)%m) + key[i])%m;
    }
    double a1 = (std::sqrt(5) - 1)/2;
    int val = std::floor((this->N)*(polyres*a1-std::floor(polyres*a1)));
    return val;

}

int Dictionary::findFreeIndex(char key[]){
    int index = hashValue(key);
    for (int j = index;j<DICT_SIZE+index;j++){
        int i = j%DICT_SIZE;
        if (std::strcmp(A[i].key,s) == 0) return i;
        if (std::strcmp(A[i].key,t) == 0) return i;
    }
    return -1;    
}

Entry* Dictionary::get(char key[]){
    int index = hashValue(key);
    int i = index;
    while (std::strcmp(A[index%DICT_SIZE].key,s) != 0 && (index - i < DICT_SIZE)){
        if(std::strcmp(A[index%DICT_SIZE].key,key) == 0)
            return &(A[index%DICT_SIZE]);
        index++;
    }
    return nullptr;
}

bool Dictionary::put(struct Entry e){
    int index = findFreeIndex(e.key);
    if (index == -1) return false;
    A[index] = e;
    return true;
}

bool Dictionary::remove(char key[]){
    int index = hashValue(key);
    int i = index;
    while ((std::strcmp(A[index%DICT_SIZE].key,s) != 0) && (index - i < DICT_SIZE)){
        if(std::strcmp(A[index%DICT_SIZE].key,key) == 0)
            strcpy(A[index%DICT_SIZE].key,t);
            return true;
        index++;
    }
    return false;
}






#endif