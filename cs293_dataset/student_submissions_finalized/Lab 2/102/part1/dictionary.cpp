#include<iostream>
#include <cmath>
#include "assert.h"

using namespace std;

#include"dictionary.h"

int Dictionary::hashValue(char key[]){
    int x=33;
    int sum_key=0;
    for(int i=0 ; i<31 && key[i]!='\0' ; i++){
        
        sum_key+=((int)key[i]-65)*pow(x,i);
        // cout<<"value "<<(int)key[i]-65<<" "<<pow(x,i)<<endl;
    }
    N=64;
    double keyA;
    double A= (sqrt(5)-1)/2;
    //cout<<sum_key<<" "<<A<<" "<<endl;
    keyA=(sum_key*A);
    keyA=keyA-(int)keyA;
    // cout<<"keyA is "<<keyA<<endl;
    double keyR=floor(keyA*DICT_SIZE);
    assert(keyR<DICT_SIZE);
    //cout<<"This is keyR "<<keyR<<endl;
    return keyR;
}

int Dictionary::findFreeIndex(char key[]){
    int keyC=hashValue(key);
    int i=0;
    while(i<DICT_SIZE){
        if(A[keyC%DICT_SIZE].value==-1){
            return keyC%DICT_SIZE;
        }
        keyC++;
        i++;
    }

    return -1;
}

Entry* Dictionary::get(char key[]){
    int keyC=hashValue(key);
    cout<<"keyC "<<keyC<<endl;
    int i=0;
    bool tracer=true;
    for(int i=0 ; i<32 && key[i]!='\0';i++){
        if(A[keyC%DICT_SIZE].key[i]!=key[i]){
            tracer=false;
            break;
        }
    }
    while(i<DICT_SIZE){
        if(tracer){
            return &A[keyC%DICT_SIZE];
        }
        keyC++;
        i++;
    }
    return NULL;
}


bool Dictionary::put(struct Entry e){
    int keyE=findFreeIndex(e.key);
    if(keyE==-1){
        return false;
    }
    else {
        A[keyE]=e;
        // A[keyE]=e.value;
        return true;
    }
}

bool Dictionary::remove(char key[]){
    int keyC=hashValue(key);
    Entry* D=get(key);
    if(D!=NULL && D->value!=-2){
        D->key[0]='N';
        D->key[1]='U';
        D->key[2]='L';
        D->key[3]='L';
        D->value=-2;
        return true;
    }

    return false;

}

