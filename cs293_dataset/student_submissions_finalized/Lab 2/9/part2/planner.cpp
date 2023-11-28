#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "dictionary.cpp"
using namespace std;

/*

In interactive mode you can give commands '
  ADD <station_one> <start_time> <station_two> <finish_time>
  QUERY_STATION <station_one> <start_time>
  QUERY_JOURNEY <station_one> <start_time> <station_two>
  EXIT

*/

// 64 here is the dict size
char station[64][32];

void planner(Dictionary &dictionary)
{
    // the keys are just char(s) from aaa to zzz,i.e., 26*3 - 2, not implemented the 26^3 implementation since anyway it's going to be tested against at max 64 inputs.
    // keys will be aaa - zaa, zaa - zza, zza - zzz
    char count[4] = "aaa"; // key
    int i = 0;
    while (1) // always true
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
            char start[32];
            cin >> start;
            char starttime[5];
            cin >> starttime;
            char end[32];
            cin >> end;
            char endtime[5];
            cin >> endtime;
            char value[74] = "";

            strcat(value, start);
            strcat(value, " ");
            strcat(value, starttime);
            strcat(value, " ");
            strcat(value, end);
            strcat(value, " ");
            strcat(value, endtime);

            Entry data;
            strcpy(data.key, count);
            strcpy(data.value, value);

            int hashValueData = dictionary.hashValue(data.key);
            int freeIndexData = dictionary.findFreeIndex(data.key);
            if (freeIndexData >= 0)
            {
                dictionary.put(data);
            }
            if (count[i] == 'z')
            {
                i++;
            }
            count[i]++;
        }

        // QUERY_STATION <station_one> <start_time>
        else if (strcmp(input, "QUERY_STATION") == 0)
        {
            char start1[32];
            cin >> start1;
            char starttime1[5];
            cin >> starttime1;

            char key[4] = "aaa";
            int i = 0;
            int tr = 0; // valid train or not
            int st = 0; // station

            while (1)
            {
                Entry *entry = dictionary.get(key);

                if (entry != NULL)
                {
                    // cout << entry->key << entry->value << endl;

                    char value[74];
                    strcpy(value, entry->value);
                    char start[32];

                    char *ptr;
                    ptr = strtok(value, " ");
                    strcpy(start, ptr);

                    if (strcmp(start1, start) == 0)
                    {
                        st = 1;
                        char starttime[5];

                        ptr = strtok(NULL, " ");
                        strcpy(starttime, ptr);

                        int stime1 = stoi(starttime1);
                        int stime = stoi(starttime);

                        if ((stime1 / 100 < stime / 100) or ((stime1 / 100 == stime / 100) and (stime1 % 100 <= stime % 100)))
                        {

                            tr++;
                            char end[32];
                            char endtime[5];

                            ptr = strtok(NULL, " ");
                            strcpy(end, ptr);

                            ptr = strtok(NULL, " ");
                            strcpy(endtime, ptr);

                            cout << "Train " << tr << " : " << start << " " << starttime << " " << end << " " << endtime << endl;
                        }
                    }

                    if (count[i] == 'z')
                    {
                        i++;
                    }
                    key[i]++;
                }
                else
                {
                    break;
                }
            }
            if (not st)
            {
                cout << "No valid station." << endl;
            }
            else if (not tr)
            {
                cout << "No trains at required time." << endl;
            }
        }

        // QUERY_JOURNEY <station_one> <start_time> <station_two>
        else if (strcmp(input, "QUERY_JOURNEY") == 0)
        {
            char start1[32];
            char end1[32];
            char starttime1[5];

            cin >> start1;
            cin >> starttime1;
            cin >> end1;
            char ftkey[4] = "";
            int fttime = 2400;
            char key[4] = "aaa";
            int i = 0;
            int tr = 0; // valid train or not
            int st = 0; // station

            while (1)
            {
                Entry *entry = dictionary.get(key);

                if (entry != NULL)
                {
                    char value[74];
                    strcpy(value, entry->value);
                    char start[32];

                    char *ptr;
                    ptr = strtok(value, " ");
                    strcpy(start, ptr);

                    char starttime[5];

                    ptr = strtok(NULL, " ");
                    strcpy(starttime, ptr);

                    char end[32];
                    char endtime[5];

                    ptr = strtok(NULL, " ");
                    strcpy(end, ptr);

                    ptr = strtok(NULL, " ");
                    strcpy(endtime, ptr);

                    // case for direct trains

                    if (strcmp(end, end1) == 0)
                    {

                        if (strcmp(start1, start) == 0)
                        {
                            st = 1;

                            int stime1 = stoi(starttime1);
                            int stime = stoi(starttime);

                            if ((stime1 / 100 < stime / 100) or ((stime1 / 100 == stime / 100) and (stime1 % 100 <= stime % 100)))
                            {

                                tr++;
                                if (stime < fttime)
                                {
                                    strcpy(ftkey, key);
                                    fttime = stime;
                                }
                            }
                        }
                    }

                    if (count[i] == 'z')
                    {
                        i++;
                    }
                    key[i]++;
                }
                else
                {
                    break;
                }
            }

            Entry *entry1 = dictionary.get(ftkey);

            char value[74];
            strcpy(value, entry1->value);
            char start[32];

            char *ptr;
            ptr = strtok(value, " ");
            strcpy(start, ptr);

            char starttime[5];

            ptr = strtok(NULL, " ");
            strcpy(starttime, ptr);

            char end[32];
            char endtime[5];

            ptr = strtok(NULL, " ");
            strcpy(end, ptr);

            ptr = strtok(NULL, " ");
            strcpy(endtime, ptr);
            cout << "Earliest Train for you is : " << start << " " << starttime << " " << end << " " << endtime << endl;
            if (not st)
            {
                cout << "No valid station." << endl;
            }
            else if (not tr)
            {
                cout << "No trains at required time." << endl;
            }
        }
    }
}

int main()
{
    cout << "Welcome to my Railway Planner. You can use the following commands :";

    cout << "ADD <station_one> <start_time> <station_two> <finish_time>\nQUERY_STATION <station_one> <start_time>\nQUERY_JOURNEY <station_one> <start_time> <station_two>\nEXIT\n";
    Dictionary rp;
    // rp = railway planner

    planner(rp);

    return 0;
}