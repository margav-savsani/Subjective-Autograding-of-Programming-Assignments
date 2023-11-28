#ifndef PLANNER_H
#define PLANNER_H
#include<string>
#include "dictionary.h"

struct Journey { //struct Journey defined here 
  // define suitable fields here
  float t1;
  float t2;
  char stop[32];
};

class SortedArray{ //Declaration of classs Sorted Array 
	private:
	int growth_constant;
	
	Journey *ptr;
	int N;//size of the array (total number of positions available
	public:
	int size;//size of the array (number of elemetns contained
	SortedArray();
	int find(float element); //finds and returns index where an element can be added or its index where it is located 
	void add(Journey element);
	Journey& operator[](int a);		//operator overloading of []
	void grow();	//grows the array as and when required 
	
};

struct Station{ //Station struct . It is data type for which dictionary is created  
  // define suitable fields here
  char key[32];			//starting station
  SortedArray j;	//coontains the sorted array 
};



struct Query{	//struct Query, saves the user input for processing 
  // define suitable fields here
  std::string query[5];
};

class Planner {	//our main class which collaborates between all the used data structures like SortedArray and Dictionary 
	Dictionary<Station> station; //Dictionary as the only member object 
	
public:
	Planner();
	
	void take_query(std::string query);	//takes the user input and processes it 
	void add_start_station(Station s);//if needed to add a station to the dictionary it is used 
	void query_station(char k[], float time);	//shows all journeys from station in k after time *time*
	void query_journey(char start[], float time, char stop[]);//responsible for finding the earliest start time journey possible from station start to station stop after time *time*. It uses the via_0_stop and via_1_stop member method 
	int via_0_stop(char start[], float time, char stop[]);
	int via_1_stop(char start[], float time, char stop[]);
};


#endif
