#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "dictionary.cpp"
using namespace std;

void dictionaryHandler(Dictionary &dictionary)
{
    for (int i = 0; i >= 0; i++)
    {
        char input[32];
        //cout << ">>> ";
        cin >> input;
        if (strcmp(input, "EXIT") == 0)
        {
            break;
        }

        // ADD <station_one> <start_time> <station_two> <finish_time>
        if (strcmp(input, "ADD") == 0)
        {

            char st1[32];
            cin >> st1;
            float start;
            cin >> start;
            char st2[32];
            cin >> st2;
            float end;
            cin >> end;
            Entry data;
            strcpy(data.station, st1);
            data.jour = Journey(st2, start, end);
            int hashValueData = dictionary.hashValue(data.station);
            int freeIndexData = dictionary.findFreeIndex(data.station);
            //cout << "Hash Value of "<<data.station<<": "<< hashValueData << endl;
            //cout << "Free Location: " << freeIndexData << endl;
            if (freeIndexData >= 0)
            {
                dictionary.put(data);
                //cout << "Successfully Added " << endl;
            }
            else
            {
                //cout << "NO Available space " << endl;
            }
        }

        // QUERY_STATION <station_one> <start_time>
        if (strcmp(input, "QUERY_STATION") == 0)
        {
            char query[32];
            cin >> query;
            int start; cin>>start;
            dictionary.get(query, start);
        }

        else if (strcmp(input, "QUERY_JOURNEY")==0)
        {
            char st1[32];
            cin>>st1;
            int start;
            cin>>start;
            char st2[32];
            cin>>st2;
            Query* q = new Query(start, st1, st2);
            dictionary.plan(q);
        }
    }
}

void interactive()
{
    cout << "Welcome to Dictionary \n";
    cout << "";
    Dictionary dictionary;
    dictionaryHandler(dictionary);
}

int main()
{
    interactive();
    return 0;
}
