#include "dictionary.h"
#include <cmath>

int Dictionary::hashValue(char key[]){
    int x = 33;
    int i = 0; 
    long int sum = 0;
    while(key[i]!='\0'){
        sum = (( sum + int(key[i]) ) * x )%879190747;                       //A very large prime number not near power of 2, to prevent overflow
        i++;
    }
    double n = 3;
    int fib = floor(DICT_SIZE * ( modf( sum * 0.615 , &n)) );               //Fib thing
    return fib;
}

int Dictionary::findFreeIndex(char key[]){
    int hash = hashValue(key);
    int count = 0;
    while(A[hash].get()!=0 ){
        hash = ( hash + 1 ) % DICT_SIZE;
        count++;
        if( count == DICT_SIZE+1 ){
            return -1;
        }
    }
    return hash;
}

struct Entry *Dictionary::get(char key[]){
    int hash = hashValue(key);
    int count = 0;
    while(1){
        bool b = 0;
        
        if(strcmp(A[hash].get_key(),key)==0){
            return &A[hash];
        }
        if(A[hash].get()==-1){
            return NULL;
        }
        hash=(hash+1)%DICT_SIZE;
        count++;
        if(count==DICT_SIZE+1){
            return NULL;
        }
    }    
}

Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new Entry[N];
};

bool Dictionary::put(struct Entry e){
    char *key = e.get_key();
    int hash = hashValue(key);
    int count = 0;
    while(A[hash].get()!=0 ){
        count++;
        hash=(hash+1)%DICT_SIZE;
        if(count==DICT_SIZE+1){
            return 0;
        }
    }
    A[hash]=e;
    return 1;
}

bool Dictionary::remove(char key[]){
    int hash = hashValue(key);
    int count = 0;
    while(1){
        if(strcmp(A[hash].get_key(),key)==0){
            A[hash].removed();
            return 1;
        }
        hash = (hash+1)%DICT_SIZE;
        if (count==DICT_SIZE+1){
            return 0;
        }
        count++;
    }
}
