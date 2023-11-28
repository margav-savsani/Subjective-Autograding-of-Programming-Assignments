#include <iostream>
#include "dictionary.cpp"
#include <arijit.h>
using namespace std;

#ifndef PLANNER_H
#define PLANNER_H


struct Journey // Journey is a struct which store start_time and end_station ,time
{
    char end_station[34];
    float start_time;
    float end_time;
};


class Planner // planner is the main class and all functions are implemented here
{
    Dictionary<DynamicQueue<Journey>> Stations; // this is a dictionary of stations which store 
                                                // journey started from this station( key = name of station)
public:
    Planner(){}; // default constructor

    bool check_intermediate_station(Journey j, char end[]) // check if there any intermediate station
    { 
        struct Entry<DynamicQueue<Journey>> *s = Stations.get(j.end_station);
        if (s != NULL)
        {
            Journey *arr = s->value.getAll();
            int size = s->value.size();
            for (size_t i = 0; i < size; i++)
            {
                if ((arr[i].start_time >= j.end_time) && (strcmp(arr[i].end_station, end) == 0))
                {
                    return true;
                }
            }
        }
        return false; // return false if there is not intermediate station between two stations
    }

    void add(struct Journey a, char *start_station) // this will add a new journay to 
    {                                               // corresponding  the station queue
        struct Entry<DynamicQueue<Journey>> *s = Stations.get(start_station); // check if there is 
        if (s != NULL)                                          // station in the dictionary
        {
            s->value.QInsert(a);        // if yes then just store to that station queue
        }
        else
        {
            Entry<DynamicQueue<Journey>> S; // otherwise create a new queue and store there
            strcpy(S.key, start_station);
            DynamicQueue<Journey> j;
            j.QInsert(a);
            S.value = j;
            if(!Stations.put(S)){     // if there is an error print a error message
                cout << "Errors in Adding \n";
            }
        }
    }

    void query_station(char *name, float time)  // list all journey 
    {                                           // started from this station and after the given time
        struct Entry<DynamicQueue<Journey>> *s = Stations.get(name);
        if (s != NULL)
        {
            Journey *arr = s->value.getAll();
            int size = s->value.size();
            bool found = false;
            for (size_t i = 0; i < size; i++)
            {
                
                if (arr[i].start_time >= time)
                {
                    cout << arr[i].start_time << " " << arr[i].end_station << endl;
                    found = true;
                }
            }
            if (!found)
            {
                cout << "ERROR\n";
            }
            
        }
        else
        {
            cout << "ERROR \n"; // print error if there is no such station
        }
    }
    // query journey
    void query_journey(char *station_one, float time, char *station_two)
    {
        struct Entry<DynamicQueue<Journey>> *s = Stations.get(station_one);
        if (s != NULL)
        {
            Journey *arr = s->value.getAll();
            int size = s->value.size();
            float min_time = 10e+23;
            int id = -1;
            for (int i = 0; i < size; i++)
            {
                if (time < arr[i].start_time && ((strcmp(arr[i].end_station, station_two) == 0) || check_intermediate_station(arr[i], station_two)))
                {
                    if (arr[i].start_time - time < min_time)
                    {
                        min_time = arr[i].start_time - time;
                        id = i;
                    }
                }
            }
            if (id != -1)
            {
                if (strcmp(arr[id].end_station, station_two) == 0)
                {
                    cout << arr[id].start_time << endl;
                }
                else
                {
                    struct Entry<DynamicQueue<Journey>> *s = Stations.get(arr[id].end_station);
                    float min_time = 10e+23;
                    int new_id = -1;
                    if (s != NULL)
                    {
                        Journey *j = s->value.getAll();
                        int size = s->value.size();
                        for (size_t i = 0; i < size; i++)
                        {
                            if (j[i].start_time < min_time)
                            {
                                new_id = i;
                                min_time = j[i].start_time;
                            }
                        }
                        cout << arr[id].start_time << " "<< arr[id].end_station << " " << j[new_id].start_time << endl;
                    }
                    else
                    {
                        cout << "error occurs \n";
                    }
                }
            }
            else
            {
                cout << "ERROR \n";
            }
        }
        else
        {
            cout << "ERROR \n";
        }
    }
};

#endif