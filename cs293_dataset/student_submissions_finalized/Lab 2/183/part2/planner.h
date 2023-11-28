#ifndef PLANNER_H
#define PLANNER_H

struct Station {
  // define suitable fields here
};

struct Journey {
  // define suitable fields here
  char sn1[32];
  char sn2[32];
  float  st;
  float ft;
  int pre=0;  //if nothing is present then 0 if we add the it updates to 1
};

struct Query{
  // define suitable fields here
};

class Planner {
  // define suitable fields here
  public:
      int N=64; // size of array J
      struct Journey *J; // Array of dictionary entries
  
  public:
  // Default constructor
  Planner();
  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]);
    // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]);
  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Journey e);
  //display all trains starting from st1 and after starting time.If station doesn't exist displays ERROR
  void display_station(char key[],float st);
  //display journey with least starting time after start time from station1 to station 2 with atmost 1 stop in between 
  void display_journey(char key[],float st,char dest[]);
};

#endif
