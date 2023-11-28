#ifndef PLANNER_H
#define PLANNER_H
#include<iostream>
#include<string.h>
#include"dictionary.cpp"

class Planner {
  // define suitable fields here
  private:
    Dictionary dictionary;

  public:
    void add(struct Entry query);
    void station(char station_one[],float start_time);
    void journey(char station_one[],float start_time,char station_two[]);//first called in QUERY_JOURNEY
    Entry* base(char station_one[],float start_time,char station_two[]);//next called in QUERY_JOURNEY , and then journey is called from inside with base, reachtime and destination

    };

#endif