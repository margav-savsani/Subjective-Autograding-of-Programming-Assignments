#include<iostream>
#include<string.h>
#include "dictionary.h"
#include <cmath>
using namespace std;

Dictionary::Dictionary(){
	N = DICT_SIZE;
	A = new Entry[N];
}

int Dictionary::hashValue( char key[] ){
	//cout<<"inside hash"<<endl;
	int x=41;
	int n=strlen(key);
	int sum = 0;
	for(int i=n-1; i>=0; i--){
		sum = key[i] + x*sum;
	}
	
	double a = (sqrt(5)-1)/2;
	int hashed_val = floor((sum*a-int(sum*a))*N); //will return int range from 0 to N-1
	//cout<<"hash value "<<hashed_val<<endl;
	return hashed_val;
}

int Dictionary::findFreeIndex(char key[]){
	int probe = Dictionary::hashValue(key); 
	int iprobe = probe-1;
	
	if(probe==0) iprobe = N-1;
	
	while( A[probe].status == 1 ){
		if(probe==iprobe){
			//cout<<"full from findfreeindex  "<<probe<<endl;
			return -1; //array is full
		}
		if(strcmp(A[probe].key, key)==0){ 			
			return -2; //key not unique
		}
		probe = (probe+1)%N;
		//cout<<"probe "<<probe<<endl;
	}
	return probe;
}

struct Entry * Dictionary::get(char key[]){
	int probe = Dictionary::hashValue(key);
	if(probe>=N || probe<0)
		return NULL;
		
	int iprobe = probe-1;	
	if(probe==0) iprobe = N-1;
	
	while(A[probe].status==1 || A[probe].status==2){
		if(probe==iprobe){
			return NULL;
		}
		if(A[probe].status==2){ // ignore the tombstone
			probe = (probe+1)%N;
			continue;
		}
		if(strcmp(A[probe].key, key)==0){			
			struct Entry *b = &A[probe];
			return b;	
		}
		probe = (probe+1)%N;
	}
	return NULL;//condition not true means status 0 means empty space
}

bool Dictionary::put(struct Entry e){
	int index = Dictionary::findFreeIndex(e.key);
	if(index==-1 || index==-2)
		return false;
	for(int i=0; i<strlen(e.key); i++){
		A[index].key[i] = e.key[i];
	}
	A[index].value = e.value;
	A[index].status = 1;
	return true;
}

bool Dictionary::remove(char key[]){
 //get is checking everything whether the index is even valid or not or if there is any such element or not
	if( Dictionary::get(key)==NULL )
		return false;

	int probe = Dictionary::hashValue(key);
	while(A[probe].status==1 || A[probe].status==2){
		
		if(A[probe].status==2){ // ignore the tombstone
			probe = (probe+1)%N;
			continue;
		}
		if(strcmp(A[probe].key, key)==0){ //returns zero if similar			
			A[probe].status = 2; //tombstone
				return true;	
		}
		probe = (probe+1)%N;
	}
	return false;//condition not true means status 0 means empty space	
}















