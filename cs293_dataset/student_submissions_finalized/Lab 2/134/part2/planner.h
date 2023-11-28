#ifndef PLANNER_H
#define PLANNER_H
#include <iostream>
#include "dictionary.cpp"
using namespace std;


class Planner {
  // define suitable fields here
  Dictionary* plannerDict;

public:

  Planner(){
    plannerDict = new Dictionary;
  }

  bool queryJourney(char[] , float, char [], int , float);
  void planningHandler();
  void add();
  void queryStation();

  
};

#endif