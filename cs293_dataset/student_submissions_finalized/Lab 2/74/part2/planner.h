#ifndef PLANNER_H
#define PLANNER_H

using namespace std;

int DICT_SIZE = 64;

struct Journey {
  // define suitable fields here
  int value;
  char station1[32]; // this is like key to dictionary
  float start_time;
  char station2[32];
  float finish_time;
  
};


class Planner {
  // define suitable fields here

  private:
    int N;
    
  public:
    Journey *A; //Array of journey entries
    
    Planner(); //Default Constructor
  void put( Journey r ); //appends the given route into dictionary array

    // Return the hash value (between 0 and N-1) of the given string
    int hashValue(char station1[]);

    // Find the position where given station1 can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
    int findFreeIndex(char station1[]);

    // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
    Journey *get(char station1[]);
  

};

#endif