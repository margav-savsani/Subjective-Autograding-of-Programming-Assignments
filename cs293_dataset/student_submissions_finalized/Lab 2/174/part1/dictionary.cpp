#include<iostream>
#include "dictionary.h"
#include<math.h>
#include<array>
using namespace std;
Dictionary::Dictionary(){
    N=DICT_SIZE;
    A=new Entry[N];
    for(int i=0; i<N; i++){
        A[i].key=NULL;
    }
}
int Dictionary::hashValue(char* key){
    int x=7;
    int size=sizeof(key)/sizeof(key[0])-1;
    int coeff[size];
    for(int i=0; i<size; i++){
        coeff[i]=key[i];    
    }
    int sum=coeff[0];
    for(int i=1; i<size; i++){
        sum=sum+coeff[i]*pow(x,i);
    }
    float k=(sum*0.61);
    k=k-floor(k);
    return(floor(N*k));
}
int Dictionary::findFreeIndex(char key[]){
    int check1=hashValue(key);
    while(A[check1].key != NULL){
        if(strcmp(A[check1].key,"removed")==0) {return check1;}
        check1++;
        if(check1==N) return(-1);
    }   
}
struct Entry* Dictionary::get(char key[]){
    int k=findFreeIndex(key);
    if(k==-1) {return NULL;}
    for(int i=k; i<N; i++){
        if(strcmp(A[i].key,key)==0){
            return &A[i];
        }
    }
    return NULL;
}
bool Dictionary::put(struct Entry e){
    int k=findFreeIndex(e.key);
    if(k==-1) {return false;}
    A[k]=e;
    return true;
}
bool Dictionary::remove(char key[]){
    for(int i=hashValue(key); i<N; i++){
        if(strcmp(A[i].key,key)==0){
            string s="removed";
            for(int j=0; j<7; j++){
                A[i].key[j]=s[j];}
            return true;
        }
        if(A[i].key==NULL){
            return false;
        }
    }
    return false;
}