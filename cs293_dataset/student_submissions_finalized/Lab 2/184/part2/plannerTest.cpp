#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "planner.cpp"
using namespace std;

void dictionaryHandler(Dictionary &dictionary)
{
    for (int i = 0; i >= 0; i++)
    {
        char input[32];
        cout << ">>> " ;
        cin >> input;
        
        
        if (strcmp(input, "EXIT") == 0){
            break;
        }

        else if (strcmp(input, "ADD") == 0)
        {
            Entry start_station;
            Entry destination;

            //cout<<"x1"<<endl;//
            char inputKey1[32];
            cin >> inputKey1;
            //cout<<"x2"<<endl;//
            int value1;
            cin >> value1;
            //cout<<"x3"<<endl;//
            strcpy(start_station.key, inputKey1);
            start_station.value = value1;
            start_station.is_start = 0;
            start_station.link = &destination;
            

            //cout<<"y1"<<endl;//
            char inputKey2[32];
            cin >> inputKey2;
            //cout<<"y2"<<endl;//
            int value2;
            cin >> value2;
            //cout<<"y3"<<endl;//
            strcpy(destination.key, inputKey2);
            destination.value = value2;
            destination.is_start = 1;
            destination.link= &start_station;

            //cout<<start_station.link->key<<endl;//
            dictionary.put(&start_station);
            //cout<<destination.link->key<<endl;//
            dictionary.put(&destination);
        }

        else if (strcmp(input, "QUERY_STATION") == 0)
        {
            char inputKey[32];
            cin >> inputKey;
            int value;
            cin >> value;
            Entry Station;
            strcpy(Station.key, inputKey);
            Station.value = value;
            Station.is_start = 0;
            //cout<<Station.key<<endl;
            dictionary.query_station(&Station);
        }

        else if (strcmp(input, "QUERY_JOURNEY") == 0)
        {

            Entry start_station;
            Entry destination;

            char inputKey1[32];
            cin >> inputKey1;
            int value1;
            cin >> value1;
            strcpy(start_station.key, inputKey1);
            start_station.value = value1;
            start_station.is_start = 0;

            char inputKey2[32];
            cin >> inputKey2;
            strcpy(destination.key, inputKey2);
            dictionary.query_journey(&start_station, &destination);
        }

    }
}

int main()
{
    Dictionary dictionary;
    dictionaryHandler(dictionary);
    return 0;
}
