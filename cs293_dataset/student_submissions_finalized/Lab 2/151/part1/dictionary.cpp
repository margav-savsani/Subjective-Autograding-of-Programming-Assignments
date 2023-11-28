#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "dictionary.h"

using namespace std;

double gold_conj = 0.618033989;


Dictionary::Dictionary(){
	N = 64;
	A = new Entry[N];

	for(int i = 0; i < 64; i++){
		A[i].value = -1;
	}
}


int Dictionary::hashValue(char key[]){
	//hash code map
	int x = 31;
	unsigned long long pol = 1;

	for(int i = 0; i < strlen(key); i++){
		pol = pol * x +  key[i];
	}

	//compression mapping
	double p = pol * gold_conj;
	int k = DICT_SIZE * (p - (long)p);
	return k;
}



int Dictionary::findFreeIndex(char key[]){
	int h = hashValue(key);
	int h_o = h;
	while(A[h].value != -1 && A[h].value != -2){
		h++;
		h %= DICT_SIZE;
		if(h_o == h) return -1;
	}
	return h;

}


struct Entry* Dictionary::get(char key[]){
	int h = hashValue(key);
	int h_o = h;

	while(A[h].key != key || (A[h].key == key && A[h].value == -2)){
		h++;
		h %= DICT_SIZE;
		if(h_o == h) return NULL;
	}
	if(A[h].value == -1) return NULL;
	return A + h;
}


bool Dictionary::put(struct Entry e){
	int h = hashValue(e.key);
	int h_o = h;
	while(A[h].value != -1 || A[h].value != -2){
		h++;
		h %= DICT_SIZE;
		if(h_o == h)return false;
	}

	A[h] = e;
	return true;
}


bool Dictionary::remove(char key[]){
	int h = hashValue(key);
	int h_o = h;
	while(A[h].key != key || (A[h].key == key && A[h].value == -2) ){
		h++;
		h %= DICT_SIZE;
		if(h_o == h) return false;
	}

	A[h].value = -2;
	return true;
}

