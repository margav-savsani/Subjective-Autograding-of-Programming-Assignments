#include<iostream>
#include<string.h>
#include "dictionary.h"

using namespace std;

Dictionary::Dictionary(){
    N=64;
    A = new Entry[64];
}

unsigned long int hashcodemap(char key[]){
    int p=33;
    int i=0;
    for(i ; i< 32 ; i++){
        if(key[i] == '\0' ) break;
    }
    unsigned long int ans=key[0];
    for(int k=1 ; k <i ; k++){
        ans = ans*p + key[i]; 
    }
    return ans;
}

int comp_hash(unsigned long int key){
    double a=0.618;
    a*=key;
    int b=64;
    b= b*(a-(int)a);
    return b;
}

int Dictionary::hashValue(char key[]){
    unsigned long int a=hashcodemap(key);
    int b=comp_hash(a);
    return b;
}
int Dictionary::findFreeIndex(char key[]){
    int pos=hashValue(key);
    int size=0;
    while(true){
        if(A[pos].key=="NULL"){
            return pos;
        }

        pos++;
        pos = pos%64;
        size++;
        if(size==64)return 0;
    }

}

bool Dictionary::put(struct Entry e){
    int pos=findFreeIndex(e.key);
    if(pos== -1)return 0;
    A[pos]=e;
    return 1;
    
}

struct Entry * Dictionary::get(char key[]){
    int pos=hashValue(key);
    int size=0;
    while(true){
        if(A[pos].key=="NULL"){
            return NULL;
        }
        
        if(strcmp(A[pos].key,key)==0){
            return &A[pos];
        }

        pos++;
        pos = pos%64;
        size++;
        if(size==64)return NULL;
    }
}
bool Dictionary::remove(char key[]){
    if(get(key)==NULL) return 0;
    int pos=hashValue(key);
    int size=0;
    while(true){        
        if(strcmp(A[pos].key,key)==0){
            A[pos].key[0]='T';
            return 1; 
        }

        pos++;
        pos = pos%64;
        size++;
        if(size==64)return 0;
    }
        

    }

