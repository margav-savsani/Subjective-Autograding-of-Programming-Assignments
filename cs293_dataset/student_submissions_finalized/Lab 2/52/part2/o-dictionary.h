#include <iostream>
#include <string.h>

#ifndef DICTIONARY_H
#define DICTIONARY_H

const int DICT_SIZE = 64;

// Journey entry struct
struct Entry
{
    char station_one[32];
    float start_time;
    char station_two[32];
    float finish_time;
};

class Dictionary
{
private:
    int N;           // current size of array A
    struct Entry *A; // Array of dictionary entries

public:
    // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
    int hashValue(char key[]);

    // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
    int findFreeIndex(char key[]);

    // Default constructor
    Dictionary();

    // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
    struct Entry *get(char key[]);

    // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
    bool put(struct Entry e);

    // Remove the given key; return true if success, false if failure (given key not present)
    bool remove(char key[]);

    // Put all entries starting from station_one after start_time into array pointed by Entry* journies
    // and return number of such entries
    int query_station(char *station_one, float start_time, Entry *journies);

    // Put the journey with soonest start_time going from station_one to station_two in atmost 2 steps
    // If it is direct journey in 1 step then put it in path[0]
    // else If it is journey with intermediate station then put first train in path[0] and second in path[1]
    // and return number of steps required
    int query_journey(char *station_one, float start_time, char *station_two, Entry *path);

    // Default destructor
    ~Dictionary();
};

#endif
