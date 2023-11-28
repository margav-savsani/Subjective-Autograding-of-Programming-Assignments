#include<cmath>
#include<string.h>
#include<iostream>
#include"dictionary.h"
using namespace std;

Dictionary:: Dictionary(){
    N = DICT_SIZE;
    A = new Entry[N];
    for (int i = 0; i<N; i++){
        A[i].status = NULL_SPACE;
    }
}

int Dictionary:: hashValue(char key[]){

    int x = 32; // setting x value for polynomial accumulation
    float hashvalue = 0; 
    int size = 0;// to store the size of the word in the key
    for(int i=0 ; key[i] != '\0' ; i++){
        size ++;
    }
    float A = 0.61803398874989; // the value of A 

    if (key[0]=='\0'){ // to return hash value for empty string
        hashvalue = 0;
    }
    else {
        // cout<<"Size "<<size;
        for(int i = size -1; i>=0 ; i--){
            // cout<<key[i];
            hashvalue = (((x*hashvalue*A) - floor(x*hashvalue*A)) + ((key[i]*A) - floor(key[i]*A))) -
            floor(((x*hashvalue*A) - floor(x*hashvalue*A)) + ((key[i]*A) - floor(key[i]*A))); // to compute kA(mod1) recursively            
            // cout<<"First half: "<<((x*hashvalue*A) - floor(x*hashvalue*A))<<endl;
            // cout<<"Second half: "<<(((key[i]*A) - floor(key[i]*A)))<<endl;
            // cout<<"Hash value: "<<hashvalue<<endl;
            // cout<<"Entire function: "<<((x*hashvalue*A) - floor(x*hashvalue*A)) + ((key[i]*A) - floor(key[i]*A))<<endl;
            // cout<<"Floor of entire function"<<floor(((x*hashvalue*A) - floor(x*hashvalue*A)) + ((key[i]*A) - floor(key[i]*A)))<<endl;
            // cout<<endl;
        }
        hashvalue = (int)floor(N*hashvalue); 
    }
    // cout<< "Hash value of the key is: "<<hashvalue;
    return (int)hashvalue;
}

int Dictionary:: findFreeIndex(char key[]){
    int hashvalue = hashValue(key);
        for(int i = 0; i<N; i++){
            if(A[(hashvalue+i)%N].status==NULL_SPACE||A[(hashvalue+i)%N].status==TOMBSTONE){ 
                // cout<<"Empty space found at: "<<(hashvalue+i)<<endl;
                return (hashvalue+i);
            }
            // cout<<"Array is full: "<<endl;
        }
    return -1;
}

 struct Entry * Dictionary:: get(char key[]){
    int hashvalue = hashValue(key);
    for(int i = 0; i<N; i++){
        if(A[(hashvalue+i)%N].status==NULL_SPACE){ // ignoring the Entry if status is a tombstone
            return nullptr; 
        }
        if(strcmp(key, A[(hashvalue+i)%N].key)==0){
            return &A[(hashvalue+i)%N];
        }
    }
    return nullptr;
 }

bool Dictionary:: put(struct Entry e){
    int freeindex = findFreeIndex(e.key);
    
    if (freeindex == -1){
        return false;
    }
    else{
        A[freeindex].value = hashValue(e.key);
        A[freeindex].status = FULL; // to update the status of that index as full
        for(int i=0 ; e.key[i]!='\0' ; i++){ // to copy the word in the key
                A[freeindex].key[i] = e.key[i];
        }
        return true;
    }
}

 bool Dictionary:: remove(char key[]){
    int hashvalue = hashValue(key);
    // int test = 0;
    
    for (int i = 0; i<N; i++){
        if(A[(hashvalue+i)%N].status == NULL_SPACE){
            return false; // to return the non-existance of the key in the chain once it is broken
        }
        else if(strcmp(key, A[(hashvalue + i)%N].key) == 0){
            A[(hashvalue + i)%N].status = TOMBSTONE; // to give the value tombstone to the index once element is removed
            // test = i;
            return true;
        }
    }
    return false;
    // cout<<"Hash Value removed at index: "<< (hashvalue + test)%N; // for debugging
 }



