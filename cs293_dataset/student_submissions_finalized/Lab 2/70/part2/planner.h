#ifndef PLANNER_H
#define PLANNER_H

#define CONST_GROWTH 1000
#define INIT_SIZE 1000

// Can change this value for debugging
int DICT_SIZE = 64;

struct Station {
  // define suitable fields here
  char name[32];  //Station name
};

struct Journey {
  // define suitable fields here
  Station s1;
  Station s2;
  int start; //start time
  int finish;//finish time
};

class DynamicQueue {
public:
  Journey *A; // the array used for implementing the dynamic dequeue
  unsigned int N; // the current size of array A
  unsigned int head; // index where next element of queue will be deleted from
  unsigned int tail; // index where next element will be inserted
  unsigned int nextSize() { return N+CONST_GROWTH; }
public:
  DynamicQueue() // default constructor
  {
    A = new Journey[INIT_SIZE];
    if (A != '\0') N = INIT_SIZE;
    else N = 0;
    head = tail = 0;
  } 
  ~DynamicQueue(){delete[] A;}; // default destructor
  
  bool isEmpty(); // is the queue empty?
  bool isFull(); // is the queue full?
  void grow(); // grow the queue to its next size 
  unsigned int size(); // return the current number of elements in the queue
  void QInsert(Journey x); // insert given element at tail of the queue; grow array size as necessary
  bool QDelete(Journey *x); // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
};


struct Entry {
  // define suitable fields here
  DynamicQueue j;   //every 'Entry' consists of a Dynamicqueue, all the train journeys starting from a given station are stored in the queue at its respective Entry location in the dictionary
  char key[32];

  Entry(){
    
  }

};

class Dictionary {
 public:
  int N; // size of array A
  struct Entry *A; // Array of dictionary entries

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]);
  
  // Default constructor
  Dictionary(); 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(char key[]);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]);
};

struct station_query{
  // define suitable fields here
  Station s;
  int start_time;
};

struct journey_query{

  Station s1;
  Station s2;
  int start_time;

};

class Planner {
public:
// define suitable fields here
  Dictionary d;
  //DynamicQueue<Journey> j;
public:

  void Add(Journey p);  //add a journey to planner

  int bin_srch(DynamicQueue& b, int time, int low, int high); //search for index with start_time>=time and index-1(if any) with start_time<time

  void query_station(station_query q1); //query all the trains starting from a given station after given time

  void query_journey(journey_query q2); //query the Journey with least possible start time from station1 to station2 after given start_time

  int findFreeIndex1(char key[]); //used to find free location to store info about trains starting from 'key'(given string)

};

#endif