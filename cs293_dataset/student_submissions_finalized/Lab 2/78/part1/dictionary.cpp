#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include<cmath>
#include"dictionary.h"
using namespace std;

class Dictionary {
 private:
  int N; // size of array A
  struct Entry *A; // Array of dictionary entries

 public:

Dictionary::Dictionary(){
	N=64;
	A= new Entry[64];
	for(int i=0;i<64;i++){
		A.key[i]=NULL;
	}	
}

int Dictionary::hashValue(char key[]){
	double a=0.618;
	int sz=sizeof(key);
	int sum=0,prod=1;
	for(int i=0;i<sz;i++){
		int m=int(key[i]);
		prod=prod*2;
		sum=sum+(m*(prod%183));	
	}
	double sa=sum*a;
	double in=(sa%1)*64;
	double hash = floor(in);
	int final = hash;
	return final;
}

int Dictionary::findFreeIndex(char key[]){
	int hash=hashValue(key[]);
	int num=0;
	for(int i=0;i<64;i++){
		if(A.key[i]!=NULL) num++;
	}
	if(num==64) return -1;
	
	while(A.key[hash]!=NULL || A.key[hash]!=X){
		hash=(hash+1)%64;
	}
	return hash;
}


string Dictionary::convertToString(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}


struct Dictionary::Entry *get(char key[]){
	s1=convertToString(key,sizeof(key));
    	string str[64];
    	for(int i=0;i<64;i++){
    		str[i]=convertToString(A.key[i],sizeof(A.key[i]));
    	}
	for(int j=0;j<64;j++){
		int yn=s1.strcmp(str[j]);
		if(yn==0) return A[j];
	}
	return NULL;
}

 bool Dictionary::put(struct Entry e){
 	int num=0;
	for(int i=0;i<64;i++){
		if(A.key[i]!=NULL) num++;
		else break;
	}
	if(num==64) return false;
 	int place=findFreeIndex(e.key);
 	A.value[place]=e.value;
 	A.key[place]=e.key;
 	return true;
 }

bool Dictionary::remove(char key[]){
	if(struct Entry *get(char key[]) == NULL) return false;
	else {
		for(int i=0;i<64;i++){
			if(A.key[i]==key[]) {
				A.key[i]=X;
				return true;
			}
		}
	}


}

};
