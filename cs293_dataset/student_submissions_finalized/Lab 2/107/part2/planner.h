#ifndef PLANNER_H
#define PLANNER_H

#include "linearQueue.cpp"
#include "dictionary_for_planner.cpp"

struct Station;


struct Journey {
  // define suitable fields here
  Station *start; // pointer to beginning station of journey
  Station *end; // pointer to ending station of journey
  float start_time;  // starting time of journey
  float finish_time;  // ending time of journey
  Journey();  // default constructer
};

struct Station {
  // define suitable fields here
  int mark;  // marker... -1 for empty, 0 for tombstone, 1 for filled
  char key[32]; // name of station
  LinearQueue<Journey> todest;  // linear queue of all journeys originating from this station
  Station();  // default constructer
};

struct Query1 {  // This refers to QUERY_STATION
  char name[32];  // Destination station name
  float start_time;  // starting time of journey
  Query1();  // default constructer
  Query1(const Query1& cpy);  // copy constructer
};


struct Query2{  // This refers to QUERY_JOURNEY
  // define suitable fields here
  Station *start;  // pointer to beginning station
  Station *inter;  // pointer to intermediate station
  Station *end;  // pointer to ending station
  float start_time1;  // starting time of journey 1
  float finish_time1;  // ending time of journey 1
  float start_time2;  // starting time of journey 2
  float finish_time2;  // ending time of journey 2
  Query2();  // default constructer
};

class Planner {
  // define suitable fields here
private:
  Dictionary<Station> stations;  // It has a dictionary of stations
public:
  // Default Constructer
  Planner();

  // Inserts a journey from station_one to station_two beginning at start_time and ending at finish_time in the Linear Queue of journeys originating at station_one
  bool insertJourney(char station_one[], float start_time, char station_two[], float finish_time);

  // Checks if station_one is present in our dictionary of stations
  bool validStation(char station_one[]);

  // Returns a Linear Queue of Query1 which has all travels from station_one after start_time
  LinearQueue<Query1> allTravels(char station_one[], float start_time);

  // Returns Query2 i.e. the earliest train from station_one to station_two after start_time
  Query2 earliestStart(char station_one[], float start_time, char station_two[]);
};

#endif
