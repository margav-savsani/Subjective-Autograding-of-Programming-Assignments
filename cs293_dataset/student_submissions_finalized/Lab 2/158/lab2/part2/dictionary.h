#include<iostream>
#include<string.h>


#ifndef DICTIONARY_H
#define DICTIONARY_H

using namespace std;


// Can change this value for debugging
int DICT_SIZE = 64;

//		DEFINING STATION, JOURNEY AND ENTRY
//***************************************************************//



// station only consists of a name
struct Station {
 	
 	char name[32]; 
 	
 	
 	Station(){
 		
 		strcpy(name,"\0");
 	}
};


//journey will have two stations and start and end times.
struct Journey {
	
  	struct Station s1, s2;
 	int t1;
 	int t2; 	
};


// Entry consists of a journey and a key(which we take to be the name of the first station)
struct Entry {
  
  char key[32];
  struct Journey J;
      
        //Default Constructor provided to allo creation of arrays 
   	Entry(){
  	strcpy(key,"\0");
  	}
  
  	//Entry can be constructed using departure, arrival times and source, destination times.
  	Entry(char st1[],char st2[],int td,int ta){	
  	strcpy(key,st1);
  	strcpy(J.s1.name, st1);
  	strcpy(J.s2.name, st2);
  	J.t1 = td;
  	J.t2 = ta;
  	
  	}
  	
  	// just a print func
  	void printJourney(){
  	cout<<J.s1.name<<" "<<J.t1<<" "<<J.s2.name<<" "<<J.t2<<endl;
  	
  	}
  
};
  
  
//                         DICTIONARY.H ORIGINAL PARTS  
//*********************************************************************//

class Dictionary {
 private:
  int N; // size of array A
  struct Entry *A; // Array of dictionary entries

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]);
  
  // Default constructor
  Dictionary(){
  	N= DICT_SIZE;
  	A = new struct Entry[N];}

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(char key[]);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]);
  
  void list_by_source(char s1[], int t);
  
  void shortest_path(char s1[], int t1, char  s2[]);
};

  


//			QUERY STRUCTURE
//********************************************************************//


// contains nothing but a dictionary. seperate struct only to better think of code.
struct Query{

	Dictionary D;
	
	
	Query(){
		
	
	};
	
	
	void Add(char s1[],char s2[], int t1,int t2){
		
		
		struct Entry E(s1, s2, t1, t2);
		
		
		D.put(E);
		
	
	};
	
	void ListTrains(char s1[], int t1){
		D.list_by_source(s1,t1);
	
	};
	
	
	
	
	
};

//******************************************************************//

#endif
