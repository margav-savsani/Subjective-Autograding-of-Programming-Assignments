#include <iostream>
#include <string.h>
#include <cmath>
#include "QUEUE.h"
#ifndef DICTIONARY_H
#define DICTIONARY_H
using namespace std;
float epsilon = 10e-7;

// Can change this value for debugging
int DICT_SIZE = 64;

struct JOURNEY
{ // NOTE we will store the trains in dictionary by
  // utilising the start station as the key for Storing the journey
    // This would store a station-name start time and station-end and end time in that station.
    char start[32]; // key to store the start station.
    char end[32];   // key to store the end station.
    float start_t;  // store the start time
    float end_t;    // store the end time.
};

class Dictionary
{
private:
    int N;             // size of array A
    struct JOURNEY *A; // Array of journies.

public:
    // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
    int hashValue(char key[]);

    // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
    int findFreeIndex(char key[]);

    // Default constructor
    Dictionary();

    // Return the JOURNEY corresponding to given key, or NULL if the given key does not exist in the dictionary
    DynamicQueue<JOURNEY> getall(char key[], float time); // This will store the queue of the journeys.

    // Put the given JOURNEY in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
    bool put(struct JOURNEY e);

    JOURNEY *searchdirect(char start[], char end[], float time)
    { // search whether there is a direct journey from station one to two with the least time.
        // It returns the particular journey.
        int origindex = hashValue(start);
        int index = origindex;
        if (strcmp(start, end) == 0)
            return NULL; // For same start and end.
        JOURNEY *direct = new JOURNEY; //Latest time direct journey.
        DynamicQueue<JOURNEY> listofdirect; // List that stores the direct journeys
        for (int i = 0; i < N; i++)
        {                                               // maximum no of times it searches the array is N.
            if (hashValue(A[index].start) != origindex) // computing hash value in each iteration.
            {
                break; //break for the case when start station becomes different.
            }
            else if ((strcmp(A[index].start, start) == 0) && (strcmp(A[index].end, end) == 0) && (((A[index].start_t-time)>epsilon) || (abs(A[index].start_t-time)<=epsilon)))
            {
                listofdirect.QInsert(A[index]); //Insert the given direct journey
            }
            index = (index + 1) % N; // index updated.
        }
        if (listofdirect.size() == 0)
        {
            return NULL; // if there is no such journey.
        }
        else
        {
            direct->start_t = listofdirect.getindex(0).start_t;    // storing the start of this journey as start time from A
            direct->end_t = listofdirect.getindex(0).end_t;      // Storing the end of this journey as end time
            strcpy(direct->end, listofdirect.getindex(0).end);   // End station
            strcpy(direct->start, listofdirect.getindex(0).start); // start as the start station.

            for (int i = 1; i < listofdirect.size(); i++) // Finding the minimum time journey
            {
                if (direct->start_t > listofdirect.getindex(i).start_t)
                {
                    direct->start_t = listofdirect.getindex(i).start_t;    // storing the start time
                    direct->end_t = listofdirect.getindex(i).end_t;        // Storing the end time
                    strcpy(direct->end, listofdirect.getindex(i).end);     // end station
                    strcpy(direct->start, listofdirect.getindex(i).start); // start station.
                }
            }
        }
        return direct;
    }
    JOURNEY searchjourney(char start[], char end[], float time)
    { // function searches whether there is a journey from start to end
        // After the given time.
        // Returns a journey (A,t1,B,t2) for direct from A to B
        //Else returns (A,t1,C,t3) -- "t3 is start time of journey C to B"
        DynamicQueue<JOURNEY> intermediateorend = getall(start, time); // It gets a list of stations having station 1 as start time.
        DynamicQueue<JOURNEY> listnew;                                 // contains the possible via journeys.
        JOURNEY *direct = searchdirect(start, end, time);              // Stores the latest time direct journey if any
        JOURNEY mintime;                                               // final journey to be returned.
        bool exists = false;                                           // variable to check if there is a direct journey.

        if (direct != NULL)
        { // IF Direct exists
            exists = true;
        }

        for (int i = 0; i < intermediateorend.size(); i++) // searches for all the intermediate stations present in the Queue
        {
            JOURNEY *intermediate_j = searchdirect(intermediateorend.getindex(i).end, end, intermediateorend.getindex(i).end_t);
            if (intermediate_j != NULL) // which means there is a journey.
            {
                listnew.QInsert(intermediateorend.getindex(i)); // insert the A-B
                listnew.QInsert(*intermediate_j); // insert the B-C
            }
        }
        if (listnew.size() != 0) // if new list created has non zero values (i.e journeys are possible)
        {
            mintime.start_t = listnew.getindex(0).start_t;    // storing the start of this journey as start time from A
            mintime.end_t = listnew.getindex(1).start_t;      // Storing the end of this journey as start time from next station.
            strcpy(mintime.end, listnew.getindex(1).start);   // end as intermediate station.
            strcpy(mintime.start, listnew.getindex(0).start); // start as the start station.

            for (int i = 2; i < listnew.size(); i = i + 2) // Since only the even places store the journey from A-intermediate.
            {
                if (mintime.start_t > listnew.getindex(i).start_t)
                {
                    mintime.start_t = listnew.getindex(i).start_t;      // storing the start of this journey as start time from A
                    mintime.end_t = listnew.getindex(i + 1).start_t;    // Storing the end of this journey as start time from next station.
                    strcpy(mintime.end, listnew.getindex(i + 1).start); // end as intermediate station.
                    strcpy(mintime.start, listnew.getindex(i).start);   // start as the start station.
                }
            }
            if (exists) // If the direct journey exists then
            {
                if ((mintime.start_t) > (direct->start_t))
                {
                    mintime.start_t = direct->start_t;
                    mintime.end_t = direct->end_t;
                    strcpy(mintime.end, direct->end);     // end as intermediate station.
                    strcpy(mintime.start, direct->start); // start as the start station.
                }
            }
            return mintime;
        }
        else
        {
            if (exists) // If minimum exists then return the direct journey.
            {
                return *direct;
            }
        }
        strcpy(mintime.end, "NULL");
        return mintime;
        // If no such journey exists then we return a DUMMY JOURNEY
        // and check accordingly in the handler file.
    }
};

double F = (sqrt(5) - 1) / 2.0;

int x = 37; // Value we are using for calculating the value of polynomial.
int Dictionary::hashValue(char key[])
{
    //#Hash MAP.
    int size = 0; // finding the size of the string.
    for (int i = 0; i < 32; i++)
    {
        if (key[i] == '\0')
        {
            break;
        }
        size++;
    }
    float value = 0; // this is directly storing the final computed value.
    for (int i = size - 1; i >= 0; i--)
    {
        float a = ((value * x) - int((value * x)));                 // it is a fractional part.
        float b = (F * (key[i] - '\0') - int(F * (key[i] - '\0'))); // it is a fractional part of new thing to be added.
        value = (a + b) - int(a + b);
    }
    //#Compression MAP.
    int hashval;
    hashval = int(((value) - int(value)) * N);
    return hashval;
}

int Dictionary::findFreeIndex(char key[])
{
    int index = hashValue(key);

    for (int i = 0; i < N; i++)
    { // we look maximum for the total size of the array.
        char empty[32];
        strcpy(empty, "");

        char tomb[32];
        strcpy(tomb, "-1");

        if (strcmp(A[index % N].start, empty) == 0 || strcmp(A[index % N].start, tomb) == 0)
        { // index is free only when the key it stores is equal "" or "-1".

            return index;
        }
        index = (index + 1) % N;
    }
    return -1;
}
Dictionary::Dictionary()
{ // constructor for the dictionary
    N = DICT_SIZE;
    A = new JOURNEY[N];
    for (int i = 0; i < N; i++)
    {
        strcpy(A[i].start, ""); // initialising the array.
        strcpy(A[i].start, "");
        A[i].start_t = -1; // Initialising the start_t and end_t by -1
        A[i].end_t = -1;
    }
}
struct DynamicQueue<JOURNEY> Dictionary::getall(char key[], float time) // get all stations with journey after given time
{
    int origindex = hashValue(key); // This is the index returned from hash value.
    int index = origindex;
    bool stationexist = false;
    DynamicQueue<JOURNEY> list;
    for (int i = 0; i < N; i++)
    { // maximum no of times it searches the array is N.
        if (hashValue(A[index].start) != origindex)
        {
            break;
        }
        else if (strcmp(A[index].start, key) == 0 && (((A[index].start_t > time) || (abs((A[index].start_t - time)) <= epsilon))))
        {
            stationexist = true;
            list.QInsert(A[index]);
        }
        index = (index + 1) % N; // index updated.
    }
    if (stationexist)
    {
        return list;
    }
    return list;
}

bool
Dictionary::put(JOURNEY e)
{
    // declaring character array
    int a = findFreeIndex(e.start); // finding a free index if available.
    if (a == -1)
    {
        return false;
    } // returns false for no value.
    else
    { // Adding
        strcpy(A[a].start, e.start);
        strcpy(A[a].end, e.end);
        A[a].start_t = e.start_t;
        A[a].end_t = e.end_t;
        return true;
    }
}
#endif
