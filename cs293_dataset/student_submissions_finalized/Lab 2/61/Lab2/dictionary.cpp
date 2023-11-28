#include<iostream>
using namespace std;
#include<cmath>
#include"dictionary.h"

float frac(float a){
    return a-floor(a);
}
Dictionary::Dictionary(){
    A=new Entry[DICT_SIZE];
    N=DICT_SIZE;
}
 int Dictionary::hashValue(char key[]){
    int a,i=0,x=33;
    float value=int(key[i]),f=(pow(5,0.5)-1)/2;
    i++;
    while(key[i]!='\0'){
        a=int(key[i]);
        value=frac(frac(((value*x)*f))+frac(a));
        i++;

    }
    value=floor(value*f*DICT_SIZE);
    return value;
 }
int Dictionary::findFreeIndex(char key[]){
    int i=0, x=hashValue(key);
    while(i!=N){
        if(A[x].Null || A[x].tombstone){
            break;
        } 
        x=(x+1)%N;
        i++;
    }
    if(i==N){
        return N;
    }
    else{
        return x;
    }
}
Entry *Dictionary::get(char key[]){
    int i=0,x=hashValue(key);
    while(strcmp(A[x].key,key)!=0 || A[x].tombstone){
        if(A[x].Null||i==N){
            return NULL;
        }
        x=(x+1)%N;
        i++;
    }

     return &A[x];
}
 bool Dictionary::put(Entry &e){
    int x=findFreeIndex(e.key);
    if(x==N){
        return false;
    }
    else{
        e.Null=false;
        A[x]=e;
        return true;
    }
 }
   bool Dictionary::remove(char key[]){
    struct Entry* e=get(key);
    if(e==NULL){
        return false;
    }
    else{
        e->tombstone=true;
        return true;
    }

   }