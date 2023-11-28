#include "dictionary.h"

int Dictionary::hashValue(char key[]){
	int size = sizeof(key)-1;                          // gives size of string
	long long int value = 0;
	for(int i=size-1;i>=0;i--){
		value = int(key[i]) + value*33;                //polynomial accumulation
	}
	double fibo=0.618;
	double frac=(value*fibo-int(value*fibo));            // fibonachi-hashing
	int hash_value=int(N*frac);
	return hash_value;
}

int Dictionary::findFreeIndex(char key[]){
	int probe = hashValue(key);
	while(A[probe].occupied && !A[probe].tomb){             // if at a location tomb is found it breaks out of loop, if no tomb is found and a unoccupied space 
		probe=(probe+1)%(DICT_SIZE);                         // it breaks out of loop
		if(probe=hashValue(key)){
			return -1;
		}
	}
	return probe;
}

Dictionary::Dictionary(){
	N=DICT_SIZE;
	A=new Entry[DICT_SIZE];
}

Entry* Dictionary::get(char key[]){
	for(int i=hashValue(key);A[i].occupied;i=(i+1)%N){              // checks from hashvalue to unsuccesfull search
		if(A[i].key==key){                                   
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
bool Dictionary::remove(char key[]){
	Entry*X=get(key);
	if(X==NULL){
		return false;
	}
	X->tomb=true;
	return true;
}