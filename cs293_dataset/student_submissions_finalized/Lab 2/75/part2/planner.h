#include<string>
#include"circularQueue.cpp"
#include"dictionary.cpp"
using namespace std;

#ifndef PLANNER_H
#define PLANNER_H



class Planner {
  // define suitable fields here
  public:
    Dictionary stations;
  public:
    bool isPresent(char station[]);
    void addEntry(Journey newjourney);
    void queryStation(char startStation[], float startTime);
    void queryJourney(char startStation[], float startTime, char endStation[]);

};

#endif