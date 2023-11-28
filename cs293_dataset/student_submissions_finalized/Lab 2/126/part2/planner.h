#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;

#ifndef DICTIONARY_H
#define DICTIONARY_H

// Can change this value for debugging
int DICT_SIZE = 64;
int CONST_GROWTH = 64;
struct journeys{
    float start_time;
    string key1;
    float end_time;
};

struct Entry
{
public: // define suitable fields here
    string key;
    bool isNull = true;
    int numJ=0;
    struct journeys jour[64];
};

class Dictionary
{
private:
    int N;           // size of array A
    struct Entry *A; // Array of dictionary entriesI
public:
    // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
    int hashValue(string key);

    // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
    int findFreeIndex(string key);

    // Default constructor
    Dictionary();

    void grow();

    // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
    struct Entry *get(string key);

    bool getAfterTime(string key, float start_time);

    bool getJourney(string key, float start_time, string key1, float start_2, int depth);

    // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
    bool put(struct Entry e, float start_time, string key1, float end_time);
};

#endif
