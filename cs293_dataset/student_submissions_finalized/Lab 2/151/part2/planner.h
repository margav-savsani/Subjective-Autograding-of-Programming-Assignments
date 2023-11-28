#ifndef PLANNER_H
#define PLANNER_H

#include <iostream>
#include <string>
#include <vector>
#define gold_conj 0.618033989
using namespace std;


// stores each train journey

struct Journey {
    string stat_start;
    int ts;
    string stat_end;
    int te;
};


// stores query made by user

struct Query{
    vector<string> q_vec;
};


// planner class, which is a dictionary that uses chaining feature
// the journeys are stored in a dictionary, and is chained with the help of vectors

class Planner {
private:
    int N;                      // size of dictionary
    vector<Journey> *a;         // our array, which is the dictionary

public:

    // constructor
    Planner();


    // hash function, returns dictionary position
    int hashValue(string s1);


    // create new journey
    void newJourney(string s1, int t1, string s2, int t2);


    // QUERY_STATION command
    vector<Journey> queryStation(string s1, int t);


    // QUERY_JOURNEY command
    vector<Journey> queryJourney(string s1, int t, string s2);


};

#endif