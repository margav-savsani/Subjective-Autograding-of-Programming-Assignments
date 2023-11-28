#include<iostream>
#include<string.h>


#ifndef DICTPLAN_H
#define DICTPLAN_H


// Can change this value for debugging
#define DICT_SIZE 64

struct Info{
    char dest[32];
    double stime;
    double etime;
};

struct returnDetails{
    int len;
    Info details[64];
};

class mySet{
    int N;
    int len;
    Info B[64];

  public:
    mySet();

    bool put(Info inf);

    int find_next_index(double start, int sindex, int lindex);

    returnDetails query_station(char st1[], double start);
};

struct Entry {
  // define suitable fields here
  char key[32];
  mySet Details; // Set of details about trains starting from dest = key, sorted in increasing order of start time
};

class Dictionary {
 public:
  int N; // size of array A
  struct Entry A[64]; // Array of dictionary entries

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]);
  
  // Default constructor
  Dictionary(); 

  // Default destructor

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(char key[]);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(char key[], Info inf);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]);

  returnDetails query_station(char st1[],double start);

  Info query_journey(char st1[], double start, char st2[]);
};

#endif
