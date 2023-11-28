#include"dictionary.h"
#include<iostream>
using namespace std;

int Dictionary::hashValue(char key[]){
	int x;
	double A,p;
	//defining constants

	A=(sqrt(5)-1.0)/2.0;
	x=33;

	long double t=0;
	int i=1;
	if(key[0]!='\0'){
	t+=(int(key[0])*A);
	while(key[i]!=0){
	//hashing the function
	t=(modf(((modf(t,&p))*x),&p))+modf(modf((int(key[i])*A),&p),&p);
	i+=1;
	}
	t=modf((modf(t,&p)*x),&p);
	}
	return int(floor(t*DICT_SIZE));
}

int Dictionary::findFreeIndex(char key[]){
	int hash;
	hash=hashValue(key);

	int i=hash;
	while(i<DICT_SIZE){
	//element is inserted till a dummy element or tombstone is found
	if((A[i].key)[0]=='0'||(A[i].key)[0]=='1'){
	return i;
	}
	i=i+1;
	}
	return 2*DICT_SIZE;

}


Dictionary::Dictionary(){
N=DICT_SIZE;//initialising the whole array with dummy entries which serve as NULL
	A=new Entry[N];
	Entry dummy=Entry('0',0,'0',0);
	for(int i=0;i<N;i++){
		A[i]=dummy;
	}
}


Entry* Dictionary::get(char key[], float start,int &count,Entry*& ptr){
	int hash;
	hash=hashValue(key);
	int i=hash;
	ptr=new Entry[10];
	bool found=false;
	while((A[i].key)[0]!='0'){
	//searching till an empty space is found
	if(strcmp(A[i].key,key)==0 && A[i].start_time>=start){
	ptr[count]=A[i];
	found=true;
	count+=1;
	}
	i=i+1;	
	}

	if (found){
		return ptr;
	}
	return NULL;
}


bool Dictionary::check_this(char intermediate[32],char destination[32],float &st,float end){
	int hash;
	hash=hashValue(intermediate);
	int i=hash;
	
	while((A[i].key)[0]!='0'){

	if(strcmp(A[i].key,intermediate)==0 && strcmp(A[i].station_two,destination)==0 && A[i].start_time>= end){
	st=A[i].start_time;
	return true;
	
	}
	i=i+1;	
	}

	return false;

}


float Dictionary::soonest(char key[32], float start,char (&inter)[32],float &st,char station_two[32]){
	int hash;
	hash=hashValue(key);
	int i=hash;

	// ptr=new Entry[10];
	// bool found=false;

	float sooner=2401;

	while((A[i].key)[0]!='0'){
	//searching till an empty space is found
	if(strcmp(A[i].key,key)==0 && A[i].start_time>start && A[i].start_time < sooner){
// cout<<i<<"before";
	// ptr[count]=A[i];
	// found=true;
	// count+=1;
	if(strcmp(A[i].station_two,station_two)==0){
		sooner=A[i].start_time;
	}
	

	else if(check_this(A[i].station_two,station_two,st, A[i].finish_time)){
		strcpy(inter,A[i].station_two);
		
		
		sooner=A[i].start_time;
	}


	}
	i=i+1;	
	}

	// if (found){
	// 	return ptr;
	// }
	// return NULL;
	return sooner;
}


bool Dictionary:: put(Entry e){
//inserting entries
	int index;
	index=findFreeIndex(e.key);
	if(index==2*DICT_SIZE){
	return false;
	}
	A[index]=e;
	return true;

}

bool Dictionary::remove(char key[]){
	int hash;
	hash=hashValue(key);
	int i=hash;
	bool found=false;
	// till an empty spot is reached
	while((A[i].key)[0]!='0'){
	if(strcmp(A[i].key,key)==0){
	found=true;
	break;
	}
	i=i+1;
	}
//setting up the tombstones
	Entry tombstone=Entry('1',0,'1',0);
	if(found==true){
	A[i]=tombstone;
	
	}
	return found;

}



