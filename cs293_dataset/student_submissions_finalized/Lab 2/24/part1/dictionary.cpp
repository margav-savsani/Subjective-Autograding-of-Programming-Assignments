#include "string.h"
#include <bits/stdc++.h>
#include <iostream>
#include <cmath>
#include "dictionary.h"
using namespace std;
int Dictionary::hashValue(char key[]){
    long long unsigned int sum_ascii=0; //turning the string to int
    int x=33;//chosen
  double k=(sqrt(5)-1)/2;//fibonacci
    double ksum_asciimod1;
    
    double hashfunc;   // h(k)integral part of m*ksum_asciimod1 wanted
    int hashvalue;
    for(int i=0;key[i]!='\0';i++){
        sum_ascii=sum_ascii*x+int(key[i]);
    }
    ksum_asciimod1=fmod(k*sum_ascii,1);
    hashfunc=DICT_SIZE* ksum_asciimod1;
    hashvalue=hashfunc;   //taking integer part alone
    return hashvalue;
}
int Dictionary:: findFreeIndex(char key[]){
	int h=hashValue(key);
	int t=0;
	while(true){
        //cout<<h<<endl;
		if(A[h].value==0 || A[h].tombstone==true)return h;
		h=(h+1)%DICT_SIZE;
		t++;
		if(t==DICT_SIZE){return -1;}
	}
}
Dictionary:: Dictionary(){
        N=64;
        A=new Entry[64];
    for(int i=0;i<DICT_SIZE;i++){
        A[i].value=0;
    }
}
struct Entry * Dictionary :: get(char key[]){
    int i=hashValue(key);
    for(int i=hashValue(key);i<DICT_SIZE;i++){
        if(A[i].value!=0 && A[i].tombstone==false){
            if(strcmp(A[i].key,key)==0) return &A[i];;
        }
    }
    return NULL;
    
}
bool Dictionary::put(Entry e){
    if(findFreeIndex(e.key)==-1 )return false;
    else {
        A[findFreeIndex(e.key)]=e;
        return true;
    }
}
bool Dictionary::remove(char key[]){
    int hv=hashValue(key);
    for(int i=hv;i<DICT_SIZE;i++){
        if(A[i].value!=0){
            if(strcmp(A[i].key,key)==0 && A[i].tombstone==false){A[i].tombstone=true;return true;}
        }
    }
    return false;
}

