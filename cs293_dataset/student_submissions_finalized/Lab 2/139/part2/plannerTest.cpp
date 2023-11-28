#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
using namespace std;
#include "planner.cpp"
#include "planner.h"

void plannerHandler(Planner &planner)
{
    for (int i = 0; true; i++)
    {
        char input[32];
        cout << ">>> ";
        cin >> input;
        if (strcmp(input, "EXIT") == 0)
        {
            break;
        }
        else if (strcmp(input, "ADD") == 0)
        {
            Journey J;
            char station_one[32], station_two[32];
            float start_time, finish_time;
            cin >> station_one >> start_time >> station_two >> finish_time;
            strcpy(J.station_one.name, station_one);
            strcpy(J.station_two.name, station_two);
            J.finish_time = finish_time;
            J.start_time = start_time;
            planner.insert(J);
        }
        else if (strcmp(input, "QUERY_STATION") == 0)
        {
            char station_one[32];
            float start_time;
            cin >> station_one >> start_time;
            Station s;
            strcpy(s.name, station_one);
            planner.Query_Station(s, start_time);
        }
        else if (strcmp(input, "QUERY_JOURNEY") == 0)
        {
            char station_one[32], station_two[32];
            float start_time;
            cin >> station_one >> start_time >> station_two;
            Station s1, s2;
            strcpy(s1.name, station_one);
            strcpy(s2.name, station_two);
            planner.Query_Journey(s1, start_time, s2);
        }
    }
}

int main()
{
    Planner planner;
    plannerHandler(planner);
}