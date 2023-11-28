//dictionary.cpp
#include<iostream>
#include<string.h>
#include<cmath>
#include"dictionary.h"

using namespace std;

// Can change this value for debugging

 

//                       BASIC DICTIONARY FUNCTIONS
//***********************************************************************//

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
  	do{	//if matching then spit out the value of the address
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
  	else {A[loc]=e; 
  	return true;}
  	 
  	
  
  };

  // Remove the given key; return true if success, false if failure (given key not present)
  bool Dictionary::remove(char key[]){
  	struct Entry* address = get(key);
  	//Leaves a Tombstone when removing happens
  	if(address != NULL){
  		strcpy((*address).key,"Tomb1");
  		return true;
  		
  	}
  	else return false;
  
  
  };
  
//                SPECIAL FUNCTION FOR QUERY_STATION 
//*********************************************************************//  

 
//Given a station, this function lists out all those journeys which 
//can occur after the time given by user 
  void Dictionary::list_by_source(char key[], int ref){
    int loc = hashValue(key);
    int initloc = loc, count=0;
    
    // This do-while loop looks complicated
    // It starts looping from the hash value of the given source.
    // From there, it will print every journey with starting station as given.
    
  	
    do{	
  	if(strcmp(A[loc].key, key)==0) {
  		
  	if(count==0 && A[loc].J.t1>=ref ){count++;}
  		
  		if(A[loc].J.t1>=ref ){
  			cout<<A[loc].J.t1<<" "<<A[loc].J.s2.name<<endl; }
  		
  		
  		}
  		
  		loc = (loc+1)%N; 
  	} while(loc!=initloc && A[loc].key[0]!='\0');
  	
  	// NO available trains if count of total valid journeys is 0
  	if (count==0) cout<<"ERROR"<<endl; 
  	}
  
  
  
//               SPECIAL FUNCTION FOR QUERY_JOURNEY  	
//**********************************************************************//
  	
  void Dictionary::shortest_path(char s1[], int t1, char  s2[]){
  	
  	//Initializes the first location to look for, and also two pointers to entries.
  	//tcurr is a reference time in comparison with which we will choose an earlier departure.
  	
  	int loc = hashValue(s1);
  	struct Entry* note=NULL, *note_via=NULL;
  	int initloc = loc,  tcurr=999999;
  	
  	//This loop follows a strategy of looking for direct trains or one-stop trains at each location in the dictionary.
  	//Each valid journey will reduce "tcurr" so that we have earliest departure time.
  	//If at any location in the dictionary, the entry has a destination different from the required,
  	//A second loop initiates which will look for a via-one-stop train from the said destination
  	
  	do{	
  		if(strcmp(A[loc].key, s1)==0) {
  			
  			if(strcmp(s2,A[loc].J.s2.name)==0 && A[loc].J.t1<tcurr && A[loc].J.t1>=t1){
  				tcurr=A[loc].J.t1;
  				note = A+loc;		
   				note_via=NULL;	
  			}
  		
  			if(strcmp(s2,A[loc].J.s2.name)!=0 && A[loc].J.t1<tcurr && A[loc].J.t1>t1){
  	char stop[64];
  	note_via = A+loc;
  	strcpy(stop,A[loc].J.s2.name);
  	int loc_ = hashValue(stop);
  	
  	int initloc_ = loc_, count=0;
  	
  	do{	
  		if(strcmp(A[loc_].key, stop)==0 && A[loc_].J.t1>=A[loc].J.t2) {
  			if(strcmp(s2,A[loc_].J.s2.name)==0 ){
  				tcurr = A[loc].J.t1;
    				note = A+loc_;		
  				count++;	
 			} 			
  			};
  		loc_ = (loc_ + 1)%N; 
  	} while(loc_!=initloc_ && A[loc_].key[0]!='\0');
  	
  	
  	if (count==0) note_via=NULL;}
  	
  	}
  	
  	;
  	loc = (loc+1)%N;
  	}while(loc!=initloc );
  	// do while ends here.
  	
  	//note-via is a pointer to the entry which contains info of journey from first station to middle, if any.
  	//note is a pointer to the entry which contains info of journey from source to dest or mid to dest as the case is.
  	
  	
  	//Three cases are possible:
  	
  	if (note==NULL) {cout<<"ERROR"<<endl;}
  	
  	else if(note_via!=NULL){
  	
  		cout<<note_via->J.t1<<" "<<note_via->J.s2.name<<" ";
  		cout<<note->J.t1; cout<<endl;
  		
  		 }
  	else {
  	
  	cout<<note->J.t1;
  	cout<<endl;
  	}
  	
  
  }	
  
 //********************************************************************//
  
  
  
  
  
  
 


