#include "dictionary.h"

Dictionary::Dictionary() {
	N=64;
	A = new struct Entry[N];
}

bool Dictionary::put(struct Entry e){
	int index = findFreeIndex(e.key);
	if(index != -1){
		A[index] = e; 
		return true;
	}
	else return false;
}

int Dictionary::hashValue(char key[]){
	const int p = 31, m=64;
	int i=0;
	double A = 0.61;
	long int pow = 1;
	int hash=0;
	while(key[i] != '\0' && key[i] != '\n'){
	hash = (hash+ (key[i]-'a'+97)*pow)%m;
	 pow = (p*pow)%m;
	 i++;
	}
	double h = hash*A - int(hash*A);

	int r = m*h; 
	return r;
}


int Dictionary::findFreeIndex(char key[]){
	int i=hashValue(key);
	int j=i;

	while(A[i].key[0]!='\0' && A[i].key[0]!='\n'){
		i = (i+1)%N;
		if(i==j)
			return -1;
	}

	return i;
}

bool Dictionary::remove(char key[]){
	int a = hashValue(key);
	int b=a;
	while(strcmp(A[a].key, key) != 0){
		a = (a+1)%N;
		if(a==b)
			return false;
	}
	b = a+1;
	if(A[(a+1)%N].key[0]=='\0'){
		A[a].key[0]='\0';
		while((a)!=b){
			if(A[a].key[0]=='\n')
				A[a].key[0]='\0';
			else break;
			a = (a-1+N)%N;
		}
	}
	else {
		A[a].key[0]='\n';
	}
	return true;
}

Entry* Dictionary::get(char key[]){
	int a = hashValue(key);
	int b=a;
	while(strcmp(A[a].key, key) !=0){
		a = (a+1)%N;
		if(a==b)
			return NULL;
	}

	return &A[a];
}