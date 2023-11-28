#ifndef PLANNER_H
#define PLANNER_H
#include<iostream>
#include"dictionary.h"
#include<string.h>

int DICT_SIZE = 64;

struct Journey {
  char* from; 
  char* to;
  float arri;
  float dept;
Journey(){from=new char[32];to=new char[32];arri=0;dept=0;}
};

class Planner {
private:
  Journey *journey;
  int N;
public:
Planner(){N=64;journey=new Journey[64];}
int hashValue(char key[]);
int findFreeIndex(char key[]);
bool Query_Station(char key[],float time);
bool Query_Journey(char key1[],float time,char key2[]);
bool insert(Journey j);
};

#endif