#include<iostream>
#include "dictionary.h"
#include<cmath>
#include<string>
using namespace std;

Dictionary::Dictionary(){
    N=DICT_SIZE;
    A=new Entry[N];
}

int Dictionary::hashValue(char key[]){
    int x=37;
    double a=0;
    double d[strlen(key)];
    for(int i=0; i<strlen(key); i++){
        d[i]=key[i]*((sqrt(5)-1)/2);
    }
    double b=d[strlen(key)-1]*x;
    b=b-int(b);
    for(int i=strlen(key)-1; i>0; i--){
        b=b+d[i-1];
        b=b*x;
        b=b-int(b);
    }
    return(int(b*N));
}

int Dictionary::findFreeIndex(char key[]){
    int k=hashValue(key);
    int a=k;
    while(true){
        if(A[k].state==0) {
            return k;
        }
        k=(k+1)%N;
        if(k==a) break;
    }
    return (-1);
}

bool Dictionary::remove(char key[]){
    int a=hashValue(key);
    int k=a;
    while(true){
        if(strcmp(key,A[a].key)==0){
            A[a].state=2;
            return true;
        }
        a=(a+1)%N;
        if(a==k) break;
    }
    return false;
}

bool Dictionary::put(struct Entry e){
    int k=findFreeIndex(e.key);
    if(k!=-1){
        A[k]=e;
        A[k].state=1;
        return true;
    }
    else {
        return false;
    }
}

struct Entry * Dictionary::get(char key[]){
    int k=hashValue(key);
    int a=k;
    while(true){
        if(strcmp(key,A[k].key)==0 && A[k].state==1){
            return &A[k];
        }
        k=(k+1)%N;
        if(k==a) break;
    }
    return NULL;
}
