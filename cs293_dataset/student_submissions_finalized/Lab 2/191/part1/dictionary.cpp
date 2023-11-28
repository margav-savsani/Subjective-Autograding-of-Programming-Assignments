#include<iostream>
using namespace std;
#include<cmath>
#include<string>
#include "dictionary.h"

int TOMBSTONE = 2147483647;		//TOMBSTONE variable
int NULLSTONE = -2147483647;	//NULLSTONE variable

Dictionary::Dictionary(){	// Constructor implementation
	
	N=64;					//size of array 
	A = new Entry[N];		//creating an array and storing it in A
	for (int i=0;i<N;i++){
		A[i].key[0] = '\0';			// for all the elements in the array, I have put the key[0] as null char so that default random values are not taken and put the value as NULLSTONE signifying empty slot.
		A[i].value = NULLSTONE;
	}
}	


int Dictionary::hashValue(char key[]){	//computing the hashvalue of keys given as argument 
	int x=41;		// the constant x for polynomial accumulation
	int i=0;
	while(i<31 && key[i]!='\0'){ //calculating the length of the string 
		i++;
	}
	int m =911; //modulo number 
	
	int ascii = key[i-1];		//converting char into int
	int hash_number=ascii % m;
	for(int j=i-2;j>=0;j--){	//finding the answer to polynomial accumulation (hash code map ) 
//Note: I have changed a step in hash code mapping through polynomial accumulation as I have used modulus in each step so that overflow is not done . The number chosen for modulo is such that it is prime and not too close to N so that collisions are not increased because of taking modulus.
		ascii = key[j]; 
		hash_number = ascii+x*hash_number;
		hash_number = hash_number % m;
	}
	
	float fib_number = 0.618;		//this is (sqrt(5) -1)/2 used in fibonacci hashing 
	float hash = hash_number* fib_number;	//using fibonnacii hashing 
	hash = hash - floor(hash);
	int hash_value = floor(N * hash);
	return hash_value;
}	


int Dictionary::findFreeIndex(char key[]){	//find the index free for insertion (linear probing )
	int index = hashValue(key);	//got the hash value from above function 
	for (int i=0;i<N;i++){		//finding the free index using looping which stops when either the array is not empty or we find required position
		if(A[index].key[0] == '\0'){
			return index;
		}
		index = (index + 1)%N;		//incrementation for loop
	}
	
	return -1;	//found no empty index
}

struct Entry* Dictionary::get(char key[]){	//finding through keys
	int index = hashValue(key);	//find the hash_value
	int i=0;	
	while(i!=N){
		if(strcmp(A[index].key,key) == 0){
			return &A[index];
		}
		if(A[index].key[0]=='\0' && A[index].value == NULLSTONE)
			break;
		index = (index+1)%N;
		i++;
	}
	
	return NULL;
}	


bool Dictionary::put(struct Entry e){	//inserting the key value pair 
	int index = findFreeIndex(e.key);	//find index for insertion 
	if(index == -1)//no empty space
		return false;
	else{
		strcpy(A[index].key, e.key);
		A[index].value = e.value;
		return true;
	}
}


bool Dictionary::remove(char key[]){	//removing the key:value pair 
	struct Entry *find = get(key);		//finding the ptr to the required position
	if(find != NULL){
		find->key[0] = '\0';		//changing required attributes of the data element 
		find->value = TOMBSTONE;
		return true;
	}
	else	//returns false if couldn't find the key
		return false;
}


