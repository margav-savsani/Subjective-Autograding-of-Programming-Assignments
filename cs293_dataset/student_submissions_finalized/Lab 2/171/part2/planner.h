#include<iostream>
#include<string.h>

#ifndef PLANNER_H
#define PLANNER_H

struct Journey {
  char s1[32],s2[32];
  float t1,t2;
  int value;
  Journey();
  // define suitable fields here
};

class Planner {
  private:
  int N;
  struct Journey *A;
  
  public:
  
  float duration(struct Journey J);
  Planner();

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char s1[]);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char s1[]);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Journey J);
  
  struct Journey *station(char s1[],float f);
  void soonest(char s1[],float k,char s2[]);
  

  // define suitable fields here
};

#endif