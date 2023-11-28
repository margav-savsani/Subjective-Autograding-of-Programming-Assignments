#include <iostream>
#include <string.h>
#include <cmath>
#include "dictionary.h"
using namespace std;

const double fibA=(sqrt(5)-1)/2;
const int x=33;


Dictionary::Dictionary(){
	N=DICT_SIZE;
	A=new Entry[N];
	for (int i=0;i<N;i++){
		Entry a;
		A[i]=a;
	}
}

bool Dictionary::getDict(int i){
	if(A[i].marker==full){
		cout<<A[i].key<<" "<<A[i].value<<" ";
		return true;
	}
	else{
		return false;
	}
}

int Dictionary::hashValue(char* key){
	//find the polynomial
	//use the mod 
	int poly=0,i=0;
	while (key[i]!=NULL){
		poly=poly*x;
		poly+=key[i];
		poly=poly%N;
		i++;
	}	
	double intpart;
	double k=(N)*modf(poly*fibA,&intpart);
	return k;
}	

int Dictionary::findFreeIndex(char* key){
	int hvalue=hashValue(key);
	for (int i=0;i<N;i++){
		if(A[(hvalue+i)%N].marker!=full){
			return (hvalue+i)%N;
		}
	}
	return -1;
}

struct Entry* Dictionary::get(char* key){
	int hval=hashValue(key);
	std::string ckey=string(key);
	for(int i=0;i<N;i++){
		if(A[(hval+i)%N].marker==full){
			if(std::string(A[(hval+i)%N].key)==ckey){
				return &A[(hval+i)%N];
			}
		}
		else if (A[(hval+i)%N].marker==empty){
			break;
		}
	}	
	return NULL;
}

bool Dictionary::put(struct Entry e){
	int place=findFreeIndex(e.key);
	if(place==-1){
		return false;
	}
	else{
		strcpy(A[place].key,e.key);
		A[place].value=e.value;
		A[place].marker=full;
		return true;
	}
}

bool Dictionary::remove(char*key){
	int hval=hashValue(key);
	int place;
	bool found=false;
	for(int i=0;i<N;i++){
		if(A[(hval+i)%N].marker==full){
			if(std::string(A[(hval+i)%N].key)==std::string(key)){
				place=(hval+i)%N;
				found=true;
				break;
			}
		}
		else if(A[(hval+i)%N].marker==empty){
			break;
		}
	}	
	if(found){
		A[place].marker=tombstone;
		strcpy(A[place].key,"");
		return true;
	}
	else{
		return false;
	}
}

int* Dictionary::getIndices(char* key,int* indices){
	int hval=hashValue(key);
	indices=new int[N];
	indices[0]=0;
	int count=1;
	std::string ckey=string(key);
	for(int i=0;i<N;i++){
		if(A[(hval+i)%N].marker==full){
			if(std::string(A[(hval+i)%N].key)==ckey){
				indices[count]=(hval+i)%N;
				count++;
			}
		}
		else if (A[(hval+i)%N].marker==empty){
			break;
		}
	}	
	indices[0]=count;
	return indices;
}

char* Dictionary::getKey(int i){
	return A[i].key;
}

float Dictionary::getValue(int i){
	return A[i].value;
}
