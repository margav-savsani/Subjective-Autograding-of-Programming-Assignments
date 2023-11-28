#ifndef PLANNER_H
#define PLANNER_H
#include<string.h>
#include<vector>
using namespace std;

int DICT_SIZE = 64;

struct Station {
  // define suitable fields here
};

struct Journey {
  // define suitable fields here
  char station_one[32];
  float start_time=-1;
  char station_two[32];
  float finish_time;
  bool operator < (const Journey &iData) const
  {
    return start_time < iData.start_time;
  }
};

struct Query{
  // define suitable fields here
};

class Planner {
 private:
  int N; // size of array A
  struct Journey *A; // Array of journey entries

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]);
  
  // Default constructor
  Planner(); 

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool addJourney(struct Journey j);
  
  //returns array of trains for QUERY_STATION
  vector<Journey> returnTrains(char station_one[],float start_time);

  void printJourney(char station_one[], float start_time, char station_two[]);

  //
  bool eq(float a, float b);
};

#endif