#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "o-dictionary.cpp"
using namespace std;

/*
    I am storing all entries in dictionary itself using linear probing
    The hash value of an entry is calculated with station_one as key
*/

/*
  You can give the following commands '
  ADD <station_one> <start_time> <station_two> <finish_time>
  QUERY_STATION <station_one> <start_time>
  QUERY_JOURNEY <station_one> <start_time> <station_two>
  EXIT
*/

void dictionaryHandler(Dictionary &dictionary)
{
    for (int i = 0; i >= 0; i++)
    {
        char input[32];
        cout << ">>> ";
        cin >> input;
        if (strcmp(input, "EXIT") == 0)
        {
            break;
        }

        // ADD <station_one> <start_time> <station_two> <finish_time>
        if (strcmp(input, "ADD") == 0)
        {
            char station_one[32];
            cin >> station_one;
            float start_time;
            cin >> start_time;
            char station_two[32];
            cin >> station_two;
            float finish_time;
            cin >> finish_time;

            Entry data;
            strcpy(data.station_one, station_one);
            data.start_time = start_time;
            strcpy(data.station_two, station_two);
            data.finish_time = finish_time;


            if (dictionary.put(data))
            {
                cout << "Successfully Added!" << endl;
            }
            else
            {
                cout << "NO Available space" << endl;
            }
        }

        // QUERY_STATION <station_one> <start_time>
        else if (strcmp(input, "QUERY_STATION") == 0)
        {
            char station_one[32];
            cin >> station_one;
            float start_time;
            cin >> start_time;

            Entry journies[DICT_SIZE];
            int count = dictionary.query_station(station_one, start_time, journies);

            if(count == 0){
                cout << "No possible journey available" << endl;
            }
            else{
                for (int i = 0; i < count; i++)
                {
                    cout << journies[i].start_time << " " << journies[i].station_two << endl;
                }
            }
        }

        // QUERY_JOURNEY <station_one> <start_time> <station_two>
        else if (strcmp(input, "QUERY_JOURNEY") == 0)
        {
            char station_one[32];
            cin >> station_one;
            float start_time;
            cin >> start_time;
            char station_two[32];
            cin >> station_two;

            Entry path[2];
            int steps = dictionary.query_journey(station_one, start_time, station_two, path);

            if(steps == 0){
                cout << "No such journey possible" << endl;
            }
            else if(steps == 1){
                cout << path[0].start_time << endl;
            }
            else if(steps == 2){
                cout << path[0].start_time << " " << path[1].station_one << " " << path[1].start_time << endl;
            }
        }
    }
}

int main()
{
    cout << "Welcome to Dictionary \n";
    cout << "";
    Dictionary dictionary;
    dictionaryHandler(dictionary);

    return 0;
}
