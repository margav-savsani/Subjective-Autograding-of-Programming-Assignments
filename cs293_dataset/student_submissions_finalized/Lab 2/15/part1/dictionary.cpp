#include<iostream>
using namespace std;
#include "dictionary.h"
#include<cmath>
Entry::Entry(){
    key=new char[32];
}
Dictionary::Dictionary(){
    N=64;
    A=new Entry[DICT_SIZE];
    for(int i=0;i<N;i++){
        A[i].key="";
    }
}

int Dictionary::hashValue(char key[]){
    int x=37;
    double pseudo_key=0;
    int size;
    for(size=0;size<32;size++){
        if(key[size]=='\0'){
            break;
        }
    }
    double A=(sqrt(5)-1)/2;
    size--;
    for(;size>=0;size--){
        pseudo_key=(key[size]-'\0')*A+pseudo_key*x;
        pseudo_key=pseudo_key-int(pseudo_key);
    }
    int hash_value=DICT_SIZE*pseudo_key;
    return hash_value;
}

int Dictionary::findFreeIndex(char key[]){
    int lin=hashValue(key),l=lin;
    while((A[l].key!="")&&(A[l].key!="TOMB\0")){
        l=(l+1)%DICT_SIZE;
        if(l==lin){
            return -1;
        }
    }
    return l;
}
struct Entry* Dictionary::get(char key[]){
    int lin=hashValue(key),l=lin;
    while(A[l].key!=key&&A[l].key!=""){
        l=(l+1)%64;
        if(l==lin){
            return NULL;
        }
    }
    if(A[l].key==""){
        return NULL;
    }
    return &A[l];
}
bool Dictionary::put(struct Entry e){
    int l=findFreeIndex(e.key);
    if(l==-1){
        return false;
    }
    A[l]=e;
    return true;
}

bool Dictionary::remove(char key[]){
    struct Entry * k=get(key);
    if(k){
        k->key="TOMB\0";
        k->value=0;
        return true;
    }
    return false;
}
