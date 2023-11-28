#include<iostream>
#include<cmath>
#include<string.h>
#include"dictionary.h"

Dictionary:: Dictionary() {
	//declaring array to store the keys
	N=DICT_SIZE;
	A = new Entry[N];
	for(int i=0;i<N;i++){
		A[i].key[0]='\0';
	}
}
	
	// Return the hash value (between 0 and N-1) of the given string;
	// assume string is null terminated and of max length 32
	int Dictionary::hashValue(char key[]){
    		const int p=31;
    		int hash_temp=0;
    		
    		long int x=1;
    		for(int i=0;key[i]!='\0' && key[i]!='\n';i++){
        		hash_temp = (hash_temp + (key[i]-'a'+97)*x)%N; //using polynomial accumulation
        		x=(x*p)%N;
    		}
    		//till here it is hash code map
    		double a=(sqrt(5)-1)/2;
			double h = hash_temp*a - int(hash_temp*a) ;
    		int hash_value = N*h;     //using fibonacci(Knuth)
    		// here it is compression map
    		return hash_value;
    		
	}
	
	// Find the position where given key can be inserted (after resolving hash collision if any);
	// return value between 0 and N-1 if free location present; return -1 if no free location
	int Dictionary::findFreeIndex(char key[]){
		int h = hashValue(key);
		bool found=false;
		int position_found=0;
		if(A[h].key[0]=='\0' || A[h].key[0]=='\n'){
			found=true;
			position_found=h;
		}
		for(int i=h+1;i!=h && found==false;i=(i+1)%N){                        //using linear probing to find a position in array
			if(A[i].key[0]=='\0' || A[i].key[0]=='\n'){
				found=true;
				position_found = i;            
				break;
			}
		}
		if(found) return position_found;
		else return -1;
	
	}
	
	// Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
	Entry* Dictionary::get(char key[]){
		int i = findFreeIndex(key);
		if(i>=0) return &A[i];
	}
	
	// Put the given entry in the appropriate location (using hashing) in the dictionary; 
	// return true if success, false if failure (array is full)
	bool Dictionary::put(struct Entry e){
		int i = findFreeIndex(e.key);
		if(i>=0){
			A[i]=e;
			return true;
		}
		else {
			return false;
		}
	}
	
	// Remove the given key; return true if success, false if failure (given key not present)
	bool Dictionary::remove(char key[]){
		int h = hashValue(key);
		bool removed=false;
		for(int i=h; i<N; i++){
			if(A[i].key[0]=='\0'){
				removed=false;
				break;
			}
			else if(strcmp(A[i].key,key)){
				A[i].key[0]='\n';        //assigning -1 implies that it is a tombstone
				removed=true;
				break;
			}
		}
		return removed;
	}

