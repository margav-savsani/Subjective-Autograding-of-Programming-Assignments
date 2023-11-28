#include<iostream>
#include<cmath>
#include "dictionary.h"
#include <string.h>
using namespace std;

Dictionary::Dictionary(){
	A = new Entry[DICT_SIZE];
	for(int i=0; i<DICT_SIZE; i++){
		strcpy(A[i].key,"EMPTY");
	}
}

int Dictionary::hashValue(char key[]){

	//Hashcode map -Polynomial Accumulation
	int k = 0, x=33;//changeable
	int keysize;
	for(keysize=0; keysize<32; keysize++){
		if(key[keysize]=='\0') break;
	}
	for(int i=keysize; i>=0; i--){
		k = k*x + (int)key[i];
	}
		
	//Compression map -Fibonacci Hashing
	double k1 = k*((sqrt(5)-1)/2);
	k1 = k1 - (int)k1;
	k1 = k1*DICT_SIZE;
	return abs((int)k1); //to deal with overflow

}

int Dictionary::findFreeIndex(char key[]){
	//Linear Probing
	if(N==DICT_SIZE) return -1;
	int probe = hashValue(key);
	while(strcmp(A[probe].key,"EMPTY")!=0){
		if(strcmp(A[probe].key,"TOMBSTONE")==0) return probe;
		probe = (probe+1)%DICT_SIZE;
	}
	return probe;
}

// Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
struct Entry* Dictionary::get(char key[]){
	int exp_pos = hashValue(key);
	if(strcmp(A[exp_pos].key,key)==0) return &A[exp_pos];
	int index = exp_pos+1;
	while(index!=exp_pos && (strcmp(A[index].key,"EMPTY")!=0)){
		if(strcmp(A[index].key,key)==0) return &A[index];
		index = (index+1)%DICT_SIZE;	
	}
	return NULL;	
}

bool Dictionary::put(struct Entry e){
	int probe = findFreeIndex(e.key);
	if(probe==-1) return false;
	else{
		A[probe] = e;
		N++;
	}
	return true;	
}

bool Dictionary::remove(char key[]){
	if(N==0) return false;
	Entry* pos = get(key);
	if(pos==NULL) return false;
	strcpy(pos->key,"TOMBSTONE");
	N--;
	return true;
}



