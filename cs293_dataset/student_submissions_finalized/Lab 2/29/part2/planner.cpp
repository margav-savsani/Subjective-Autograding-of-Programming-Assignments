#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "planner.h"
using namespace std;


void queryHandler(Planner &P)
{
    for (int i = 0; i >= 0; i++)
    {
        char input[32];
        cin >> input;
        if (strcmp(input, "EXIT") == 0)
        {
            break;
        }

        // ADD <key> <value>
        if (strcmp(input, "ADD") == 0)
        {

            char station_one[32];
            char station_two[32];
            float start_time;
            float finish_time;
            cin >> station_one;
            cin >> start_time;
            cin >> station_two;
            cin >> finish_time;
            Journey j;
            strcpy(j.end_station, station_two);
            j.end_time = finish_time;
            j.start_time = start_time;
            P.add(j,station_one);
        }

        // QUERY_STATION <key>
        else if (strcmp(input, "QUERY_STATION") == 0)
        {
            char station_one[32];
            float start_time;
            cin >> station_one;
            cin >> start_time;
            P.query_station(station_one,start_time);
            
        }

        // QUERY_JOURNEY <key>
        else if (strcmp(input, "QUERY_JOURNEY") == 0)
        {
            char station_one[32];
            char station_two[32];
            float start_time;
            cin >> station_one;
            cin >> start_time;
            cin >> station_two;
            P.query_journey(station_one,start_time,station_two);

        }
    }
}

int main()
{
    Planner P;
    queryHandler(P);
    return 0;
}
