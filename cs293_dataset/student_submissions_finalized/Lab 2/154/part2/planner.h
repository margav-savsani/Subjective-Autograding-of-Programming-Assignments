#ifndef PLANNER_H
#define PLANNER_H

# define NULL_KEY 0  // this will be stored in key[0]
# define DICT_SIZE 64

struct Journey{
    // Node based storage of a journey
    char end_station[32];
    float start_time;
    float end_time;
    Journey* next; // next ptr
    Journey(float start, char* station, float end);
};

struct Station{
    // Entry of the dictionary
    char name[32]; // station name
    Journey *journey; // journeys starting from this station
    Station();
};

struct Query_result{
    // struct to store result of QUERY_JOURNEY
    float start_time;
    float next_time;
    char stop[32];
    Query_result(float start); // for direct journey
    Query_result(float start, float next, char *station); // for indirect journey
};

// manually defined function to check if two char strings are equal or not
bool isequal(const char* a, const char* b);

class Planner{
    int N;
    Station* Stations;
    int hashValue(char *key); // hashing function
    int find_station(char* station); // returns the index of station in the hashed array

public:
    Planner();
    bool add(char *start_station, float start_time, char *end_station, float end_time);
    Journey* query_station(char* station, float time);
    Query_result* query_journey(char* start_station, float start_time, char* end_station);
};

#endif