#ifndef PLANNER_H
#define PLANNER_H

int CONST_GROWTH = 64;

struct Station
{
  char name[32];
};

struct Journey
{
  Station station_one, station_two;
  float start_time, finish_time;
  int status = 0;
  // 0-unoccupied
  // 1-occupied
};

class Planner
{
  Journey *A; // stores the array of journeys
  int N;      // Hash table size
public:
  Planner();                                                    // default constructor
  int hashvalue(Station S);                                     // hashing
  int freeIndex(Journey journey);                               // Finding free index of the journey
  void insert(Journey journey);                                 // Inserting journey into the Array
  void Query_Station(Station s, float time);                    // Lists all the stations after start_time
  void Query_Journey(Station s1, float start_time, Station s2); // Lists soonest possible journey after start_time
};

#endif