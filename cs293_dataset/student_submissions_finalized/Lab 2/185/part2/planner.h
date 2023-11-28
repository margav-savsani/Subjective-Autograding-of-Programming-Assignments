#include<iostream>
#include<string.h>
#include"dictforplanner.cpp"


#ifndef PLANNER_H
#define PLANNER_H



struct Station {
  // define suitable fields here
};

struct Journey {
  // define suitable fields here
};

struct Query{
  // define suitable fields here
};

int p=0;
int size;
int N =64;

class Planner {
  // define suitable fields here

private:


public:

Planner();
void add(char station_one[], float start_time, char station_two[], float finish_time );
void query_station(char station_one[], float start_time);
void query_journey(char station_one[], float start_time, char station_two[]);
void exit();

};

#endif