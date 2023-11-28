#ifndef PLANNER_HPP
#define PLANNER_HPP

#include <cmath>
#include <cassert>
#include <cfloat>
#include <cstring>

#define CHAR_ARRAY_SIZE 32
#include "dictionary.tpp.hpp"

struct Journey {
    char s1[CHAR_ARRAY_SIZE];
    float st;
    char s2[CHAR_ARRAY_SIZE];
    float et;

    Journey();
    Journey(char const _s1[], float _st, char const _s2[], float _et);
    Journey& operator=(Journey j2);
    bool operator==(Journey j2);
};

struct FullJourney {
    char s1[CHAR_ARRAY_SIZE];
    float st;
    char s_mid[CHAR_ARRAY_SIZE];
    float st_mid;
    char s2[CHAR_ARRAY_SIZE];
    float et;
    
    FullJourney(char const _s1[], float _st, char const _s_mid[], float _st_mid, char const _s2[], float _et);
    FullJourney();
    FullJourney(Journey* j1, Journey* j2);
    FullJourney& operator=(FullJourney J2);
    bool operator==(FullJourney J2);
};

struct Station {
    char name[CHAR_ARRAY_SIZE];
    Journey journeys[64];
    unsigned int n;

    Station();
    Station(char const _name[]);
    void add_journey(Journey j);
    Journey* find_next_direct_journey(float now, char const dest[]);
};

class Planner {
    Dictionary<Station> stations;
    bool add(char const s1[], float st, char const s2[], float et);
    FullJourney find_next_journey(char const s1_name[], float now, char const s2_name[]);
  public:
    void Query();
};

#endif
