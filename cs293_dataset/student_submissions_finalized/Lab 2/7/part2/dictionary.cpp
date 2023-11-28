#include<iostream>
#include"dictionary.h"
#include<string.h>
#include<cmath>

using namespace std;


Dictionary:: Dictionary(){
    N = DICT_SIZE;
    A = new struct Entry[64];
    
}

int Dictionary:: hashValue(char key[]){
    
    // polynomial accumulation
    double n=0;
    
    int l=0;  // length of key
    while(key[l]!='\0'){
        l++;
    }
    
    
    for(int i=0; i<l; i++){
        n = (key[l-i-1] + n)*37;
    }
    
    double x = n*0.618;
    
    return floor((x-(long)x)*64);
}

int Dictionary:: findFreeIndex(char key[]){
    
    int x = this->hashValue(key);
    
    

    if (A[x].value != -1){
        strcpy(A[x].key , key);
        return x;
    }
    
    else {
        for(int i = x+1; i < 64+x; i++){
            if(A[i%64].value == -1){
                strcpy(A[i%64].key , key);
                return i;
            }
        }
    }
    
    return -1;
}

struct Entry Dictionary:: *get(char key[]){
    int x = this->hashValue(key);
    
    
    if( strcmp(A[x].key , key )){
        return A[x];
    }
    
    else {
        for(int i = x; i < 64+x; i++){
            if(strcmp(A[i%64].key , key)){
                return A[i%64];
            }
        }
    }
    
    return NULL;
    
}

bool Dictionary:: put(struct Entry e){
   
    
    int x = this->hashValue(e.key);
    
    if (A[x].value != -1){
        strcpy(A[x].key , e.key);
        return true;
    }
    
    else {
        for(int i = x; i < 64+x; i++){
            if(A[i].value == -1){
                strcpy(A[i].key , e.key);
                return true;
            }
        }
    }
    
    
}

bool Dictionary:: remove(char key[]){
    
    int x = this->hashValue(key);
    
    if( strcmp(A[x].key , key )){
        A[x].value = -2;    // using -2 as tomb stone.
        return true;
    }
    
    else {
        for(int i = x; i < 64+x; i++){
            if( strcmp(A[i%64].key , key)){
                A[i%64].value = -2;
                return true;
            }
        }
    }
    
    return false;
    
}
