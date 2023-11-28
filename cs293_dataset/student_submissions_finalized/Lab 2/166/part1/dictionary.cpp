#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"dictionary.h"
#include<cmath>

using namespace std;

int Dictionary::hashValue(char key[]){
    int s=strlen(key)-1;
    int a[s];
    long long int k=33;
    for(int i=0;i<s;i++){
        a[i]=key[i];
    }
    for(int i=0;i<s;i++){
        k=a[s-i-1]+a[s-i]*k;
    }
    return k%N;
}

int Dictionary::findFreeIndex(char key[]){
    int f=-1;
    for(int i=hashValue(key);i<N;i++){
        if(A[i].key==nullptr){
            f=i;
            break;
        }
    }
    return f;
}

struct Entry *Dictionary::get(char key[]){
    Entry*o;
    o=NULL;
    for(int i=hashValue(key);i<N;i++){
        if(A[i].key==key){
            o=&A[i];
            break;
        }
    }
    return o;

}

bool Dictionary::put(struct Entry e){
    int y=findFreeIndex(e.key);
    if(y==-1) return false;
    else{
        A[y].key=e.key;
        return true;
    }
}

bool Dictionary::remove(char key[]){
    bool x=false;
    for(int i=hashValue(key);i<N;i++){
        if(A[i].key==key){
            A=nullptr;
            x=true;
            break;
        }
    }
    return x;
}



    



