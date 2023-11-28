#ifndef PLANNER_H
#define PLANNER_H
#include <string>
#include <vector>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

int i=0;

// struct Station {
//   // define suitable fields here
//   string final_station;
// };

// struct Journey {
//   int q_final_time, q_final_station;
//   // define suitable fields here

// };

// struct Query{
//   // define suitable fields here
// };

class Planner {
  //struct Station S[64];
  string station_one[32], station_two[32];
  float time_one[32], time_two[32];
  int index=0;
public:
  void Store_Station(string station_start,string station_end){
    station_one[index]=station_start;
    station_two[index]=station_end;
    }

  void Store_Journey(float time_start,float time_end){
    time_one[index]=time_start;
    time_two[index]=time_end;
    index++;
    }

  void Query_list_request(string q_station_start,float q_time_presence);

  void Query_Journey(string j_station_start, float j_time, string j_station_end);

  Planner(){};
  // float getValue(char key[]){

  // }
};

#endif