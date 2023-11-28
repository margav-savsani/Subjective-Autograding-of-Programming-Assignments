#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
#define DICT_SIZE 64

#ifndef DICTIONARY_H
#define DICTIONARY_H

struct threeTuple
{
    float departureTime; // departure time from station1
    char S2[32];         // station 2 string
    float arrivalTime;   // arrival time at station 2
};

struct Entry
{
    char S1[32];                      // station 1 string
    struct threeTuple fsf[DICT_SIZE]; // array of direct journeys from S1 to other stations
    int length;                       // number of such direct journeys
    bool is_filled;                   // whether this entry is filled
    Entry()
    {
        is_filled = false;
        length = 0;
    }
    void put(threeTuple &addMe, int start, int end) // puts addMe into the sorted threeTuple array
    {
        int index = find(addMe.departureTime, start, end); // find index where it is to be added
        for (int i = length - 1; i >= index; i--)
        {
            fsf[i + 1] = fsf[i];
        }
        fsf[index] = addMe;
        return;
    }
    int find(int dT, int start, int end) // returns index of smallest number >=dT in range[start, end - 1]. returns end if all numbers are smaller
    {
        /*int index = -1;                       //O(n) implementation for reference
        for (int i = 0; i < length; i++)
        {
            if (fsf[i].departureTime >= dT)
            {
                index = i;
                break;
            }
        }
        if (index == -1)
        {
            index = length;
        }
        return index;*/

        if (start == end) // O(log n) recursive binary search implementation
        {
            return start;
        }

        int middle = (start + end) / 2;
        if (dT > fsf[middle].departureTime)
        {
            return find(dT, middle + 1, end);
        }
        else
        {
            return find(dT, start, middle);
        }
    }
};

class Planner
{
private:
    int N;           // size of array A
    struct Entry *A; // Array of dictionary entries

public:
    // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
    int hashValue(char key[]);

    // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
    int findIndex(char key[]);

    // -1 if given key is absent, otherwise return index of key in dictionary
    int getIndex(char key[]);

    // Default constructor
    Planner();

    // ADD_JOURNEY dT stands for departure time and aT for arrival time
    void add(string, float dT, string, float aT);

    // QUERY_STATION dT stands for departure time and aT for arrival time
    void qs(string, float dT, ofstream &outFile);

    // QUERY_JOURNEY dT stands for departure time and aT for arrival time
    void qj(string, float dT, string, ofstream &outFile);
};

#endif