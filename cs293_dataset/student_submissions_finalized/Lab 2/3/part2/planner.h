#include<iostream>
#include<string.h>
#ifndef PLANNER_H
#define PLANNER_H

#include "dictionary.cpp"

#include "circularQueue.cpp"

using namespace std;

struct station {
  char name[32];
  float id;
};

struct Journey {
  // define suitable fields here
  struct station start;
  struct station end;
  float st;
  float ft;
};

class Planner {
  public:
  // define suitable fields here
    Dictionary railways;
    DynamicQueue <char*> stations;
    struct Journey* paths;


  char* makekey(Journey path);
  int com1(char *key,Journey path);
};

#endif