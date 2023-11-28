//dictionary.cpp
#include<iostream>
#include<string.h>
#include<cmath>
#include"dictionary.h"

using namespace std;

// Can change this value for debugging

 




 //polynomial rolling of char string with x=37 and modded over ArraySize.
  int Dictionary::hashValue(char key[]){
  	//HASH FUNC --> Polynomial Hashing
  	int hashValue=0;
  	int x=37;
  	
  	// %N at every step to prevent overflow
  	for(int index=0;key[index]!='\0';index++){
  		hashValue += (hashValue * x + key[index])%N; 
  	}
  	
  	//COMPRESSION FUNCTION --> Fibonacci 
  	// f(k) = |_ N * frac{A*k} _| with A as the inverse of Golden Ratio 
  	//and k as the key obtained in previous step.
  	float goldinv = 0.6180339 ;
  	float frac = goldinv * hashValue - floor(goldinv * hashValue);
  	
  	hashValue = floor( N * frac) ;
  	
  	return hashValue;
  
  
  }

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int Dictionary::findFreeIndex(char key[]){
  	int hash = hashValue(key);
  	
  	for(int loc = hash; ; ){
  		if (strcmp(A[loc].key,"\0")==0 ||strcmp(A[loc].key,"Tomb1")==0){
  			return loc;
  		}
  		
  		//Circular increment of location of search
  		loc= (loc+1)%N;
  		
  		//Stops searching if full
  		if (loc==hash)break;
  		
  	}
  	
  	//returns -1 if loop exited without result
  	return -1;
  
  
  
  
  };
  
 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *Dictionary::get(char key[]){
  	
  	struct Entry* address;
  	
  	int loc = hashValue(key);
  	
  	int initloc = loc;
  	address = NULL;
  	do{	//if matching then spit out the value
  		if(strcmp(A[loc].key, key)==0) {
  		address = A+loc; break;
  		}
  		
  		loc = (loc+1)%N; 
  	} while(loc!=initloc);
  	
  	
  	return address;
  
  };

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool Dictionary::put(struct Entry e){
  	int loc= findFreeIndex(e.key);
  	if(loc==-1){return false;}
  	else {A[loc]=e; return true;}
  	 
  	
  
  };

  // Remove the given key; return true if success, false if failure (given key not present)
  bool Dictionary::remove(char key[]){
  	struct Entry* address = get(key);
  	if(address != NULL){
  		strcpy((*address).key,"Tomb1");
  		return true;
  		
  	}
  	else return false;
  
  
  };
  
  
  
 


