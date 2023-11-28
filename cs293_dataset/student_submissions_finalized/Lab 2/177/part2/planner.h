#ifndef PLANNER_H
#define PLANNER_H

#include <string>
#include "dictionary_modified.cpp"

struct Journey {
  std::string start_station;
  std::string end_station;
  float start_time;
  float end_time;
};

class Planner {
  Dictionary<Journey> jour_list; // Here, entries are hashed by the name of the starting station

  public:

  void add_journey(std::string s1, float t1, std::string s2, float t2);

  void query_station(std::string st, float tm);

  void query_journey(std::string s1, float tm, std::string s2);
};

#endif

