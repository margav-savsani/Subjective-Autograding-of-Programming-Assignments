#include <string>
#include <iostream>
#ifndef PLANNER_H
#define PLANNER_H
using namespace std;
// All float comparisons are done using epsilon
const float epsilon = 0.001;
struct Journey {
  // define suitable fields here
  string start, end;
  float start_time, finish_time;
  Journey *next = nullptr;

  Journey(string s1, string s2, float t1, float t2){
    start=s1;
    end = s2;
    start_time = t1;
    finish_time = t2;
  }

};

struct Station {
  // define suitable fields here
  string name;
  // I'll be storing a linked list of all the journeys originating at a station
  Journey *first = nullptr;

  Station(string s){
    name = s;
  }
  void addJourney(Journey *j);

  ~Station(){
    while(first != nullptr){
        Journey *temp = first;
        first = first->next;
        delete temp;
    }
  }
};


#endif
