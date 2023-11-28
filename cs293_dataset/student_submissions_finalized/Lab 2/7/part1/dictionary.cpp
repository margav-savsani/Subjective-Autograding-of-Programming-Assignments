#include<iostream>
#include"dictionary.h"


Dictionary:: Dictionary(){
    N = DICT_SIZE;
    A = new Entry[N];
    
}

int Dictionary:: hashValue(char key[]){
    
    // polynomial accumulation
    int n=0;
    for(int i=0; i<key.length(); i++){
        n = (key[(key.length())-i-1] + n)*37;
    }
    
    return (n%64);
}

int Dictionary:: findFreeIndex(char key[]){
    
    int x = this->hashValue(key);
    
    if (A[x].value != -1){
        A[x].key = key;
        return x;
    }
    
    else {
        for(int i = x; i < key[].length(); i++){
            if(A[i].value == -1){
                A[i].key = key;
                return i;
            }
        }
    }
    
    return -1;
}

struct Entry Dictionary:: *get(char key[]){
    int n = this->hashValue(key);
    
    if( A[n].key == key ){
        return A[n].value;
    }
    
    else {
        for(int i = x; i < key.length(); i++){
            if(A[i].key == key){
                return A[i].value ;
            }
        }
    }
    
    return NULL;
    
}

bool Dictionary:: put(struct Entry e){
   
    
    int x = this->hashValue(e.key);
    
    if (A[x].value != -1){
        A[x].key = e.key;
        return true;
    }
    
    else {
        for(int i = x; i < e.key.length(); i++){
            if(A[i].value == -1){
                A[i].key == e.key;
                return true;
            }
        }
    }
    
    
}

bool Dictionary:: remove(char key[]){
    
    int n = this->hashValue(key);
    
    if( A[n].key == key ){
        A[n].value = -2;    // using -2 as tomb stone.
        return true;
    }
    
    else {
        for(int i = x; i < key.length(); i++){
            if(A[i].key == key){
                A[i].value = -2;
                return true;
            }
        }
    }
    
    return false;
    
}
