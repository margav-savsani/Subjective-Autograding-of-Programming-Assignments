#include <iostream>
#include "dictionary.h"
#include <string.h>
#include <cmath>


int Dictionary::hashValue(char key[]){
    int h=0,j=33;
    for(int i=0; i < 32 ; i++){
        if(key[i]=='\0'){
            break;
        }
        h = (h * j) + int(key[i]);
    }
    double x=h*((sqrt(5)-1)/2);
    double frac,inte;
    frac = modf(x,&inte);
    frac = frac*DICT_SIZE;
    return abs((int)frac);
}

Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new Entry[DICT_SIZE];
	for(int i=0; i<DICT_SIZE; i++){
		strcpy(A[i].key,"EMPTY");
	}
}

int Dictionary::findFreeIndex(char key[]){
    int probing=hashValue(key);
    while(strcmp(A[probing].key,"EMPTY")!=0){
        if(strcmp(A[probing].key,"TOMBSTONE")==0){
            return probing;
        }
        probing=(probing+1)%DICT_SIZE;
        if(probing == hashValue(key)){
            return -1;
        }
    }
    return probing;
}

struct Entry* Dictionary::get(char key[]){
	int i = hashValue(key);

	if(strcmp(A[i].key,key)==0){
        return &A[i];
    }
	int j = i + 1;
    while(j != i && (strcmp(A[j].key,"EMPTY")!=0)){
		if(strcmp(A[j].key,key)==0){
            return &A[j];
        }
		j = (j+1)%DICT_SIZE;	
	}
	return NULL;	
}

bool Dictionary:: put(struct Entry e){
	int prob = findFreeIndex(e.key);
	if(prob == -1){
        return false;
    }
	else{
		A[prob] = e;
	    return true;
    }	
}

bool Dictionary::remove(char key[]){
	if(N==0){
        return false;
    }
	Entry* B = get(key);
	if(B==NULL){
        return false;
    }
	strcpy(B->key,"TOMBSTONE");
	return true;
}

