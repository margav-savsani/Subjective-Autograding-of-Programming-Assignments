#include <vector>
#include "queue.cpp"
using namespace std;

#ifndef PLANNER_H
#define PLANNER_H

struct Journey {     //stores start station, start time, end time, end station
  // define suitable fields here
    char start_station[32];
    float start_time;
    float end_time;
    char end_station[32];
    Journey(char _start_station[32], float _start_time, char _end_station[32], float _end_time){
      strcpy(start_station, _start_station);
      start_time = _start_time;
      end_time = _end_time;
      strcpy(end_station, _end_station);
    }
    Journey(){

    }
};

struct Station {   //stores name(key), id and an array of journeys
  // define suitable fields here  
  char key[32];
  DynamicQueue<Journey> journeys;
  char id;
  Station(char _key[32]){
    strcpy(key, _key);
  }
  Station(){}
};


class Planner;   //defined in planner.cpp

#endif