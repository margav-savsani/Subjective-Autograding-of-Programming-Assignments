#include <iostream>
using namespace std;
#include "dictionary.h"
#include <math.h>
#include <string.h>

int Dictionary::hashValue(char key[]){
  	//hash table
  	int i=0;
	const int p = 31;
    int hash = 0;
    long p_pow = 1;
    while(key[i]!='\0'){
        hash = (hash + (key[i] - 'a'+1) * p_pow) % N;
        p_pow = (p_pow * p) % N;
		i++;
    }
  	return hash;
  	}		

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
int Dictionary::findFreeIndex(char key[]){
  	int index;
  	for(index=hashValue(key);(!(A[index].null))&&(!(A[index].key[0]=='\0'));index++){
  		if(index==N){return -1;}
		cout<<(A[index].key[0]);
  	}
  	return index;
	} 
  // Default constructor
  Dictionary::Dictionary(){
  	N=DICT_SIZE;
  	A=new Entry[N];
  }

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
 struct Entry* Dictionary::get(char key[]){
  	int index=hashValue(key);
	// cout<<index;
	// cout<<A[index].key;
  	while(index<N){
		if(A[index].null){
			return NULL;
		}
 		if(strcmp(A[index].key,key) == 0){
 			return &(A[index]);
 		}
 		index++;
  	}
  	return NULL;
  }

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool Dictionary::put(struct Entry e){
	int index=findFreeIndex(e.key);
	if(index==-1){return false;}
	A[index].key=e.key;
	A[index].value=e.value;
	A[index].null=false;
	return true;
  }
  // Remove the given key; return true if success, false if failure (given key not present)
  bool Dictionary::remove(char key[]){
  	Entry* element;
	element=get(key);
	if(element==NULL){
		return false;
	}
	char n='\0';
	element->key=&n;
	//strcpy(element->key, .c_str());
  	return true;	
  }


