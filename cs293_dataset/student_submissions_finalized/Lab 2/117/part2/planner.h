#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"dictionary.cpp"
#include <cmath>
#include<string>
using namespace std;

#ifndef PLANNER_H
#define PLANNER_H

class Planner {
  private:
    Dictionary planner;//key is the startstation as all functions search based on that, value is the start time
  public:

    Planner();
    // Adding a journey
    void add(char startStation[], float startTime, char Endstation[], float endTime);
    // For query station function
    void station(char startStation[], float startTime);
    // Checks if direct journey between stations exists after a given start time
    float journeyDirect(char startStation[], float startTime, char endstation[]);
    // Complete function for QUERY_JOURNEY
    void journeyComplete(char StartStation[], float startTime, char EndStation[]);
};

#endif
