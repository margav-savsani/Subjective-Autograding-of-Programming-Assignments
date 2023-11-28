#include <iostream>
#include <cmath>
#include "station.cpp"

using namespace std;

//Initially putting stns names as "EMPTY"
Planner::Planner(){
	stns = new Station[NUM_STATIONS];
	for(int i=0; i<NUM_STATIONS; i++){
		strcpy(stns[i].name,"EMPTY");
	}	
}
	
// Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
int Planner::hashValue(char name[]){
	//Hashcode map -Polynomial Accumulation
	int k = 0, x=33;//changeable
	int keysize;
	for(keysize=0; keysize<32; keysize++){
		if(name[keysize]=='\0') break;
	}
	for(int i=keysize; i>=0; i--){
		k = k*x + (int)name[i];
	}

	//Compression map -Fibonacci Hashing
	double k1 = k*((sqrt(5)-1)/2);
	k1 = k1 - (int)k1;
	k1 = k1*NUM_STATIONS;
	return abs((int)k1); //to deal with overflow
}

// Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
int Planner::findFreeIndex(char name[]){
	if(N==NUM_STATIONS) return -1;
	int probe = hashValue(name);
	while(strcmp(stns[probe].name,"EMPTY")!=0){
		probe = (probe+1)%NUM_STATIONS;
	}
	return probe;
}	

// Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
struct Station* Planner::get(char name[]){
	int exp_pos = hashValue(name);
	if(strcmp(stns[exp_pos].name,name)==0) return &stns[exp_pos];
	int index = exp_pos+1;
	while(index!=exp_pos && (strcmp(stns[index].name,"EMPTY")!=0)){
		if(strcmp(stns[index].name,name)==0) return &stns[index];
		index = (index+1)%NUM_STATIONS;	
	}
	return NULL;		
}

// Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
bool Planner::put(struct Station stn){
	int probe = findFreeIndex(stn.name);
	if(probe==-1) return false;
	else{
		stns[probe] = stn;
		N++;
	}
	return true;			
}


