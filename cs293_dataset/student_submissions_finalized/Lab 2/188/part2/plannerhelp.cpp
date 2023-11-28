#include "plannerhelp.h"
#include<iostream>
#include<cmath>

double fib = (sqrt(5) - 1)/2;// defining fibbonacci constant
//int DICT_SIZE = 64;
Dictionary::Dictionary(){// default constructor
	N = DICT_SIZE;// assuming N as the size of array used and not the no of elements in dictionary. For now intialized it to DICT_SIZE
	A = new struct Station[N];
	for(int i=0; i<N; i++){
		strcpy(A[i].name,"\0");
		}
	
}

int Dictionary::hashValue(char name[]){
	int poly[32];// this array stores the coefficients of polynomial
	int size=0;// used for calculating size of string
	while(name[size] != '\0'){//
		poly[size] = int(name[size]);// using the ASCII codes of characters in string as coefficients(polynomial accumulation)
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

int Dictionary::findFreeIndex(char name[]){
	double hash = hashValue(name);
	int hashindex;// this is the index corresponding to hash
	double a = hash*fib;
	int b = int(a);// calculating integral part of a
	double c = a - b;//calculating fractoinal part of a
	hashindex = int(N*c);
	int freeindex = hashindex;// freeindex is the final index where the Station is stored
	for(int i=hashindex; i<=hashindex+N; i++){
		if((strcmp(A[i].name, "\0") == 0) || (strcmp(A[i].name, "DELETED")) ) return freeindex;
		freeindex = (freeindex+1)%N;//used if collisions happen
	}
	return -1;
}
struct Station* Dictionary::getStart(char name[]){
	double hash = hashValue(name);
	int i;// this is the index corresponding to hash
	double a = hash*fib;
	int b = int(a);// calculating integral part of a
	double c = a - b;//calculating fractoinal part of a
	i = int(N*c);//calculating hash index
	while(strcmp(A[i].name,"\0")!=0){// here DELETED is ignored, 
		if(strcmp(A[i].name,name)==0) return &(A[i]);
		i = (i+1)%N;
	}	
	return NULL;
}


bool Dictionary::put(struct Station e){
	int index = findFreeIndex(e.name);//
	if(index == -1) return false;
	else{
		A[index] = e;
		return true;
	}
} 
void Dictionary::giveEnd(char name[], Station* end){
	Station *ptr = getStart(name);
	ptr->end = end;
}
void Dictionary::giveStart(char name[], Station* start){
	Station *ptr = getStart(name);
	ptr->start = start;
}
struct Station* Dictionary::getEnd(char name[]){
	double hash = hashValue(name);
	int i;// this is the index corresponding to hash
	double a = hash*fib;
	int b = int(a);// calculating integral part of a
	double c = a - b;//calculating fractoinal part of a
	i = int(N*c);//calculating hash index
	while(strcmp(A[i].name,"\0")!=0){// here DELETED is ignored, 
		//std::cout<<"Entered while loop"<<std::endl;
		if(strcmp(A[i].name,name)==0) {return (A[i].end);}
		i = (i+1)%N;
	}	
	return NULL;
}


bool Dictionary::remove(char name[]){
	Station* ptr = getStart(name);//using get function for fu=inding the address of the required element
	
	if(ptr == NULL) return false;
	else{
		strcpy(ptr->name,"DELETED");// using "DELETED" as a TOMBSTONE marker 
		ptr-> time = -1;// also using -1 as a marker for identifying DELETED elements
		return true;
	}
}
