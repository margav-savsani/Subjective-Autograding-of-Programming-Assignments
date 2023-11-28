#include "dictionary.h"
#include<cmath>
int Dictionary::hashValue(char B[]){
	int size = strlen(B);                          // gives size of string
	unsigned int value = 0;
	for(int i=size-1;i>=0;i--){
		value = int(B[i]) + value*33;                //polynomial accumulation
	}
	double fibo=0.618;
	double p,x=value*fibo;
	double frac=modf(x, &p);            // fibonachi-hashing
	int hash_value=int(N*frac);
	return hash_value;
}

int Dictionary::findFreeIndex(char B[]){
	int probe = hashValue(B);
	while(A[probe].occupied && !A[probe].tomb){             // if at a location tomb is found it breaks out of loop, if no tomb is found and a unoccupied space 
		probe=(probe+1)%(DICT_SIZE);                         // it breaks out of loop
		if(probe==hashValue(B)){
			return -1;
		}
	}
	return probe;
}

Dictionary::Dictionary(){
	N=DICT_SIZE;
	A=new Entry[DICT_SIZE];
}

Entry* Dictionary::get(char B[]){
	for(int i=hashValue(B);A[i].occupied;i=(i+1)%N){              // checks from hashvalue to unsuccesfull search
		if(strcmp(A[i].key,B)==0){                                   
			return &A[i];
		}
	}
	return NULL;	
}

bool Dictionary::put(Entry e){
	int index=findFreeIndex(e.key);                                    // finds free index 
	if(index==-1){
		return false;
	}
	A[index]=e;
	A[index].occupied=true;
	A[index].tomb=false;
	return true;
}
bool Dictionary::remove(char B[]){
	Entry*X=get(B);
	if(X==NULL){
		return false;
	}
	X->tomb=true;
	return true;
}
