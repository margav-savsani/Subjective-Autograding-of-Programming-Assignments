#ifndef PLANNER_H
#define PLANNER_H
#include <iostream>
#include <vector>
#include <tuple>
using namespace std;
#define MAX_JOURNEY 10
#include "dictionary.cpp"

struct Journey {  // to store the journeys from a particulat station to a destination
  char *desti = new char[50];     // destination
  float s_t;                      // starting time
  float d_t;                      // ending time
  float time;                     // time take for journey
  int index;                      // index of this journey stored in a list
};

struct Station {
  char *name = new char[50];          // station name
  int index;                          // index of station stored in a list
  Dictionary dict_journey;            // dictionary to store indixes of journey stored based on destination
  vector<vector<Journey>> list2;      // a list of journeys from the station to various destinations
                                      // columnarily grouped on the same destination
};

struct Query{                         // to store the input from the user and use it throughtout the program
  char *type = new char[50];          // whether to ADD, QUERY_STATION, QUERY_JOURNEY (following variables are used accordingly)
  char *stat1 = new char[50];         // starting station name
  char *stat2 = new char[50];         // destination station name (if any)
  float time1;                        // starting time of journey
  float time2;                        // ending time of journey (if any)
};

class Planner {
  vector<Station> names;              // a list of all stations from where journey is available
  Dictionary dict_names;              // dictionary to store indixes of stations stored based on their names
  int N;                              // maximum number of journeys per station per destination (used if dynamic array used instead of vectors)
  public:
    Planner();
    bool add(Query* query);           // adds a journey based on query and returns true if added successfully
    bool station(Query* query);       // handles QUERY_STATION and passes a list of all journeys from the station after a time, to print_station()
    void print_station(vector<Journey> &list);    // receives a list from station() and prints the results accordingly
    bool journey(Query* query);       // handles QUERY_JOURNEY which computes prints the earliest journey from start to destination
    bool possible(Query* query, int &index);                                // helper function for journey()
    bool shortest(vector<Journey> &list, float &time, Journey &ans);        // helper function for journey()
};

#endif