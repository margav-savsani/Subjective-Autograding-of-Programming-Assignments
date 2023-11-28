#include<iostream>
#include<string.h>
#include<cmath>
using namespace std;
#include "dictionary.h"

Dictionary:: Dictionary(){
	A= new Entry[DICT_SIZE];
	for(int i=0; i<DICT_SIZE; i++){
		A[i].value=0;
	}
}

float C=(sqrt(5)-1)/2.0;

int Dictionary:: hashValue(char key[]){
	int asc;
	string s=key;
	int l=s.length();
	float f;
	long long unsigned int h=0;
	for(int i=l-1; i>=0; i--){
		asc=key[i];
		h=asc+h*33;
	}
	float k=h*C;
	long long int m=k;
	f=k-m;
	int z=DICT_SIZE*f;
	return z;
}

int Dictionary:: findFreeIndex(char key[]){
	int h=hashValue(key);
	int iteration=0;
	while(true){
		if(A[h].value==0 || A[h].value==-1)return h;
		h=(h+1)%DICT_SIZE;
		iteration++;
		if(iteration==DICT_SIZE){return -1;}
	}
}

struct Entry* Dictionary:: get(char key[]){
	int h=hashValue(key);
	while(A[h].value!=0){
		if(A[h].value==-1) {h=(h+1)%DICT_SIZE; continue;}
		if(strcmp(A[h].key,key)==0) return &A[h];
		else h=(h+1)%DICT_SIZE;
	}
	return NULL;
}

bool Dictionary:: put(struct Entry e){
	int i=findFreeIndex(e.key);
	if(i==-1)return false;
	 else {
	 	A[i]=e;
	 	return true;
	 }
}

bool Dictionary:: remove(char key[]){
	int h=hashValue(key);
	while(A[h].value!=0){
		if(A[h].value==-1) return false;
		if(strcmp(A[h].key,key)==0){
			A[h].value=-1;
			return true;
		}
		else h=(h+1)%DICT_SIZE;
	}
	return false;
}
