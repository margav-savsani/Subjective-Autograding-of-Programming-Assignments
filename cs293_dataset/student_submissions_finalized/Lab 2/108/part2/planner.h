#ifndef PLANNER_H
#define PLANNER_H

#include "dictionary.cpp"

// Planner has a dictionary schedule which maps strings(keys) to an array of 
// Journeys(value). Value corresponding to any key(station names) is an array 
// of all the journeys that start at that station.
class Planner {
private:
    Dictionary schedule {};  // Contains info on all journeys

public:
    // This function processes queries
    void query(); 

    // Adds a new journey to dictionary of existing journeys
    void add(std::string start_stn, double start_t, std::string end_stn, double end_t);

    // Prints all the journeys starting from start_stn and after time
    void query_station(std::string start_stn, double time);

    // Returns the journey that starts the earliest after time from start_stn and 
    // ends at end_stn and only one intermediate stop at max
    void query_journey(std::string start_stn, double time, std::string end_stn);
};

#endif