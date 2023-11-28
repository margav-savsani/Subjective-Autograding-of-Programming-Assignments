#ifndef PLANNER_H
#define PLANNER_H

int NUM_STATIONS = 50;

struct Journey {

	float stime;
	char stn2[32];
	float ftime;

	//Default constructor
	Journey();	
	
	//sets journey details	
	void set_jrny_details(float stime, char stn2[], float ftime);
};

struct Station {
  	// Assumption: max 24 journies from 1 stn, lifting time restrictions
  	
  	char name[32];
  	Journey* jrnies;
  	
  	//Default constructor
	Station();
	
	//Adds a dourney to the jrnies array
	void add_jrny(Journey jrny);
	
	//Returns fastest stime2 for travel to stn2
	int check_train_availability(float stime, char stn2[]);
};

class Planner { 
private:
	int N; // size of array stns
	Station* stns; // Array of dictionary stns

public:
	// Default constructor
	Planner();
	
	// Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
	int hashValue(char name[]);

	// Find the position where given name can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
	int findFreeIndex(char name[]);	

	// Return the entry corresponding to given name, or NULL if the given name does not exist in the dictionary
	struct Station *get(char name[]);

	// Put the given stn in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
	bool put(struct Station stn);
};

#endif
