#include<iostream>
#include<string.h>
using namespace std;
#include "dictionary.h"

int hashValue(char key[]){
	int asc;
	int h=0;
	for(int i=0; i<32; i++){
		asc=key[i];
		h=asc+h*37;
	}
	return h % 64;
}

int findFreeIndex(char key[]){
	int p=hashValue(key[]);
	for(int i=p; i<DICT_SIZE; i++){
		if (A[i].value==NULL){
			return i;
		}
	}
	return -1;
}

Entry *get(char key[]){
	int p=hashValue(key[]);
	for(int i=p; i<DICT_SIZE; i++){
		if(strcmp(A[i].key,key)==0) return &A[i];
	}
}

bool put(struct Entry e){
	int p=findFreeIndex(e.key);
	if(p==-1)return false;
	 else return true;
}

bool remove(char key[]){
	int p=hashValue(key[]);
	for(int i=p; i<DICT_SIZE; i++){
		if(strcmp(A[i].key,key)==0) A[i].value=NULL;
		return true;
	}
	return false;
}
