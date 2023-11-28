#include "dictionary.h"
#include<cmath>

double fib = (sqrt(5) - 1)/2;

Dictionary::Dictionary(){
	N = DICT_SIZE;
	A = new Entry[DICT_SIZE];
	
}
int Dictionary::hashValue(char key[]){
	int poly[32];
	int size=0;
	while(key[size] != '\0'){
		poly[size] = int(key[size]);
		size++;
	}
	int result;
	result = (poly[0])% N;
	int x = 7;
	for(int i=1; i<size; i++){
		result = ((result*x)%N + (poly[i])%N)%N;
	}
	return result;	
}

int Dictionary::findFreeIndex(char key[]){
	double hash = hashValue(key);
	int hashindex;
	double f = hash*fib;
	int g = int(f);
	double h = f - g;
	hashindex = int(N*h);
	int freeindex = hashindex;
	for(int i=hashindex; i<=hashindex+N; i++){
		if(strcmp(A[i].key, "\0") == 0) return freeindex;
		freeindex = (freeindex+1)%N;
	}
	return -1;
}
struct Entry* Dictionary::get(char key[]){
	for(int i=0; i<N; i++){
		if(strcmp(A[i].key,key)==0) return &(A[i]);
	}
	return NULL;
}

bool Dictionary::put(struct Entry e){
	int index = findFreeIndex(e.key);
	if(index == -1) return false;
	else{
		A[index] = e;
		return true;
	}
} 

bool Dictionary::remove(char key[]){
	Entry* ptr = get(key);
	
	if(ptr == NULL) return false;
	else{
		strcpy(ptr->key,"DELETED");
		ptr-> value = -1;
		return true;
	}
}
