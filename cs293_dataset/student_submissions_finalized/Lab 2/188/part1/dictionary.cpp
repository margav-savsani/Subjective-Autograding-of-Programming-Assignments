#include "dictionary.h"
#include<cmath>

double fib = (sqrt(5) - 1)/2;// defining fibbonacci constant

Dictionary::Dictionary(){// default constructor
	N = DICT_SIZE;// assuming N as the size of array used and not the no of elements in dictionary. For now intialized it to DICT_SIZE
	A = new Entry[DICT_SIZE];
	
}
int Dictionary::hashValue(char key[]){
	int poly[32];// this array stores the coefficients of polynomial
	int size=0;// used for calculating size of string
	while(key[size] != '\0'){//
		poly[size] = int(key[size]);// using the ASCII codes of characters in string as coefficients(polynomial accumulation)
		size++;
	}
	int result;// final result
	result = (poly[0])% N;// initializing and using Horner's algorithm for evaluating a polynomial.
	int x = 7;
	for(int i=1; i<size; i++){//implementation of Hornor's algorithm
		result = ((result*x)%N + (poly[i])%N)%N;// this reduces the numbers into smaller ones and ensures that there is no overflow and result is between 0 and N-1
	}
	return result;	
}

int Dictionary::findFreeIndex(char key[]){
	double hash = hashValue(key);
	int hashindex;// this is the index corresponding to hashed
	double a = hash*fib;
	int b = int(a);// calculating integral part of a
	double c = a - b;//calculating fractoinal part of a
	hashindex = int(N*c);
	int freeindex = hashindex;// freeindex is the final index where the entry is stored
	for(int i=hashindex; i<=hashindex+N; i++){
		if((strcmp(A[i].key, "\0") == 0) || (strcmp(A[i].key, "DELETED")) ) return freeindex;
		freeindex = (freeindex+1)%N;//used if collisions happen
	}
	return -1;
}
struct Entry* Dictionary::get(char key[]){
	double hash = hashValue(key);
	int i;// this is the index corresponding to hashed
	double a = hash*fib;
	int b = int(a);// calculating integral part of a
	double c = a - b;//calculating fractoinal part of a
	i = int(N*c);
	while(strcmp(A[i].key,"\0")!=0){
		if(strcmp(A[i].key,key)==0) return &(A[i]);
		i = (i+1)%N;
	}	
		/*for(int i=0; i<N; i++){// searching full array for the key. can be taking less time if we are able to find out hash index
		if(strcmp(A[i].key,key)==0) return &(A[i]);
	}*/
	return NULL;
}

bool Dictionary::put(struct Entry e){
	int index = findFreeIndex(e.key);//
	if(index == -1) return false;
	else{
		A[index] = e;
		return true;
	}
} 

bool Dictionary::remove(char key[]){
	Entry* ptr = get(key);//using get function for fu=inding the address of the required element
	
	if(ptr == NULL) return false;
	else{
		strcpy(ptr->key,"DELETED");// using "DELETED" as a TOMBSTONE marker 
		ptr-> value = -1;// also using -1 as a marker for identifying DELETED elements
		return true;
	}
}
