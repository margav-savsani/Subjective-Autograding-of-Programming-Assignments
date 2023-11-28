#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "planner.h"

using namespace std;

void plannerHandler(Planner &planner)
{
    for (int i = 0; i >= 0; i++)
    {
        char input[32];
        cin >> input;
        if (strcmp(input, "EXIT") == 0)
        {
            break;
        }

        if (strcmp(input, "ADD") == 0)
        {

            char inputKey[32],second_station[32];
            float value1, value2;
            cin >> inputKey>>value1>>second_station>>value2;
            Entry data;
            strcpy(data.key, inputKey);
            data.value1 = value1;
            data.value2 = value2;
            strcpy(data.second_station, second_station);
            float freeIndexData = planner.findindex(data.key);
            if(freeIndexData<0)
            {
                cout << "No Available space " << endl;
            }
            else{
                planner.add_journey(data);
            }
        }
        if (strcmp(input, "QUERY_STATION") == 0)
        {   
            char s1[32];
            float t1;
            cin >> s1 >> t1;
            bool found = false;
            same_start z = planner.find_stations(s1);
            if (z.n == 0)
            {
                cout << "Sorry no such starting station" << endl;
            }

            else
            {
                for (int i = 0; i < z.n; i++)
                {
                    if (z.entries[i].value1 >= t1)
                    {
                        found = true;
                        cout << z.entries[i].value1 << " " << z.entries[i].second_station  << endl;
                    }
                }
                if (!found)
                {
                    cout << "No such trains found" << endl;
                }
            }
        }
        else if (strcmp(input, "QUERY_JOURNEY")==0)
        {
            char s1[32], s2[32];
            float start_time;
            cin >> s1 >> start_time >> s2;
            Intermediate I = planner.min_start_journey(s1, s2, start_time);
            if (I.t2 == -2)
            {
                cout << "No possible path" << endl;
            }
            else if (I.t2 == -1)
            {
                cout << I.t1 << endl;
            }
            else
            {
                cout<< I.t1 << " " << I.s1 << " " << I.t2<<endl;
            }
        }
    }
}

int main()
{
    Planner planner;
    plannerHandler(planner);
}
