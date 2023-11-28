#ifndef PLANNER_H
#define PLANNER_H
#include <iostream>
#include <string>
#include "dictionary.h"
#include "dictionary.cpp"

using namespace std;

struct Station
{
	// define suitable fields here
	char city[32]; // station contains city name 
	Station()
	{
		city[0] = 0;
	}
};

struct Journey
{
	// define suitable fields here 
	Entry a; // It contains the edited entry part
};

struct Query
{

	// define suitable fields here
	char A[32];
	float t2; 	// it contains three variables for us to address the query , depending upon if it's 
	char B[32];
	Query()
	{
		t2 = -1.0;
		A[0] = 0;
		B[0] = 0;
	}
};

class Planner
{
	// define suitable fields here
private:
	Dictionary d;

public:
	bool addjourney(Entry a); // to add a journey
	
	void querystation(Query b);//
	
	bool journey_exists(Query &b);  // function to find if journey between 2 cities exists or not
	
	

	void queryjourney(Query c);
	
	
};

#endif
