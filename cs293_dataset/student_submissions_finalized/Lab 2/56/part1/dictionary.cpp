#include "dictionary.h"
#include <cmath>
#define GR (sqrt(5)-1)/2
#include <iostream>

float frac_part(float x){   //calculates the fractional part (num -gif(num))
    return (x - int(x));
}

int hash_code_map(char* key){    //converts the string to int(hash code)
    if(int(*key) == 0){
        return 0;
    }
    return (int(*key) + 37*(hash_code_map(key+1)))%131071;    //mod with a prime to prevent overflow
}

int Dictionary::hashValue(char key[]){   
    return int(64*frac_part(GR*hash_code_map(key)));
}

Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new Entry[N]; 
    for(int i = 0; i < N; i++){
        A[i].id='e';
        strcpy(A[i].key, "");
        A[i].value=0;
    } 
}

int Dictionary::findFreeIndex(char key[]){
    int ind = hashValue(key);
    for(int i = ind; i < N; i = (i+1)%N){
        if(A[i].id != 'f'){
            return i;
        }
    }
    return -1;
}

struct Entry* Dictionary::get(char key[]){
    int ind = hashValue(key);
    for(int i = ind; i < N && A[i].id != 'e'; i = (i+1)%N){
        if(strcmp(A[i].key, key) == 0){  
            return (A+i);
        }
    }
    return NULL;
}

bool Dictionary::put(struct Entry e){
    int ind = hashValue(e.key);
    int free = findFreeIndex(e.key);
    if(free == -1){
        return false;
    }
    A[free] = e;
    A[free].id = 'f';
    return true;
 }

bool Dictionary::remove(char key[]){
    int ind = hashValue(key);
    for(int i = ind; i < N && A[i].id == 'f'; i = (i+1)%N){       
    
        if(strcmp(A[i].key, key) == 0){
            A[i].id = 't';
            strcpy(A[i].key, "");
            A[i].value = 0;
            return true;
        }
        
    }
    return false;
}


