#ifndef PLANNER_H
#define PLANNER_H
#include "dictionary.h"
#include "dictionary.cpp"
#include <iostream>
using namespace std;


struct Intermediate             //This is used in QUERY_JOURNEY if t2 is -2 it is a direct journey else it 
{                               //is a via journey with s1 in between
    char s1[32];
    float t1 = 100000000, t2 = -2;          //taking t1 to be some random high value greater than any value of time
};

class Planner
{
    // define suitable fields here
    Dictionary Schedule;                    //this dictionary will contain data of all the journeys

public:
    bool add_journey(Entry data)            //This is used in ADD we take an entry as argument and return true if the entry was
    {                                       //inserted successfull else false if the Dictionary was full

        if (Schedule.put(data))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    
    int findindex(char s1[])                //This just finds the free indes through the findFreeIndex function of dictionary
    {
        return Schedule.findFreeIndex(s1);
    }

    same_start find_stations(char s1[])     //This returns an array of all entries which have s1 as start
    {
        return Schedule.get_all(s1);        //uses getall function implemented in dictionary
    }
    float search(char s2[32], int t, char s3[32])// This is used in QUERY_JOURNEY when we need to check for intermediate steps
    {                               //We return the smallest possible time greater than t such that journey from s2 to s3 is possible
                                    //if such a case is not possible then we return -1;
        same_start S = find_stations(s2);       //finding all stations starting from s2
        float minimum_time = 10000000;          //for finding the minimum time
        for (int i = 0; i < S.n; i++)
        {
            if (strcmp(S.entries[i].second_station, s3) == 0)   //searching for s3
            {
                if (S.entries[i].value1 >= t)
                {
                    minimum_time = min(S.entries[i].value1, minimum_time);  //updating minimum time
                }
            }
        }
        if (minimum_time == 10000000)
            return -1;
        return minimum_time;
    }
    Intermediate min_start_journey(char s1[], char s2[], float start_time)  //used in QUERY_JOURNEY
    {
        same_start s = find_stations(s1);       //finding stations starting from s1
        Intermediate I;                         
        for (int i = 0; i < s.n; i++)
        {
            if (s.entries[i].value1 < I.t1)         //The loop should only run if the start time is less than the already minimum start time
            {
                if (strcmp(s.entries[i].second_station, s2) == 0)   //The case of a direct journey
                {
                    if (s.entries[i].value1 >= start_time)
                    {

                        I.t2 = -1;                  //t2 is -1 for a direct journey
                        I.t1 = s.entries[i].value1; //updating I
                    }
                }
                else
                {
                    if (s.entries[i].value1 >= start_time)      //for a via journey
                    {
                        float l = search(s.entries[i].second_station, s.entries[i].value2, s2);
                        if (l != -1)                //if l=-1 such journey was not possible
                        {
                            strcpy(I.s1, s.entries[i].second_station);      //updating I
                            I.t1 = s.entries[i].value1;
                            I.t2 = l;
                        }
                    }
                }
            }
        }
        return I;
    }
};
#endif