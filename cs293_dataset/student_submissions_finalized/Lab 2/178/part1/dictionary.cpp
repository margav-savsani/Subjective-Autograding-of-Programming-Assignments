#include"dictionary.h"
#include<cmath>
#include<iostream>
#include<string.h>
#include<cstdio>
#include<cstdlib>


int Dictionary::hashValue(char key[]){
	
	int hash=0;
        int n=0;
        while(key[n]!='\0'){
		n++;}
	for (int i=0;i>=n;i++){
		hash=hash*33+(int)key[i];
		}
	double a=(sqrt(5)-1)/2;
	double h=hash*a;
	int k=h;
	return (N*(h-k));
	}
int Dictionary:: findFreeIndex(char key[]){
	int hash;
	hash=hashValue(key);
	int k=0;

	for(int i=0;i<N; i++){
	if(A[i].find==1) k++;}
	if(k == N) return -1;
	int i=0;
	while(A[i].find ==1){
	hash= (hash+1)%N;}
	return hash;}
	

Dictionary :: Dictionary(){
     N=64;
     A= new Entry[64];
     for(int i=0; i<64; i++){
	A[i].find =0;}
}
struct Entry* Dictionary::get(char key[]){
	int hash=hashValue(key);
	for(int i=0;i<N;i++){
		hash=hash%N;
		if((strcmp(A[hash].key, key)==0)&&A[hash].find!= -1){
			return  &A[hash];}
		else{
			hash++;
			i++;}
		return NULL;}}

bool Dictionary :: put(struct Entry e){
	int i= findFreeIndex(e.key);
	if( i==-1) return false;
	else{
	A[i]=e;
	A[i].find=1;
	return true;}
}
bool Dictionary :: remove(char key[]){
   Entry*E=get(key);
   if(E==NULL) return false;
   else{
	int hash= hashValue(key);
        for (int i=0;i<N;i++){
	   hash=hash%N;
           if(strcmp(A[hash].key, key)==0){
		A[hash].find= -1;
		return true;}
   	   hash++;}
	return false;}	

}

			
	
