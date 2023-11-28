#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "planner.h"
using namespace std;
bool intermediate(Entry *x, int i, Dictionary &dictionary)
{
    char inter[32];
    strcpy(inter, x->journeys_of_train.journey_data->station_2);
    Entry *inter_ = dictionary.get(inter);
    for (int i = 0; i < inter_->journeys_of_train.tail; i++)
    {
        if (strcmp(inter_->journeys_of_train.journey_data->station_2, inter) == 0)
        {
            return true;
        }
    }
    return false;
}
void plannerHandler(Dictionary &dictionary)
{
    cout << "in handler\n";
    int N = 0;

    for (int i = 0; i >= 0; i++)
    {
        cout << "iteration " << i << endl;
        char input[32];
        cout << ">>> ";
        cin >> input;
        if (strcmp(input, "EXIT") == 0)
        {
            break;
        }

        // ADD <station_one> <start_time> <station_two> <finish_time>
        else if (strcmp(input, "ADD") == 0)
        {
            char station_one[32];
            cin >> station_one;
            float start_time;
            cin >> start_time;
            char station_two[32];
            cin >> station_two;
            float finish_time;
            cin >> finish_time;

            cout << "inputs taken in ADD\n";
            struct Journey data;
            data.finish_time = finish_time;
            data.start_time = start_time;
            strcmp(data.station_2, station_two);
            cout << "inputs copied into data in ADD\n";

            Entry station;
            strcpy(station.station_1, station_one);
            station.journeys_of_train.QInsert(data);
            cout << "data copied into station in ADD\n";

            Entry *check_station = dictionary.get(station_one);
            if (check_station == NULL)
            {
                dictionary.put(station);
                cout << "put executed new journey added \n";
                N++;
                cout << "no of stations =" << N << endl;
            }
            else
            {
                check_station->journeys_of_train.QInsert(data);
                cout << "old journey updated\n";
                cout << "no of stations =" << N << endl;
                cout << "newly added route to: " << check_station->journeys_of_train.journey_data[1].station_2 << endl;
            }
            check_station = NULL;
            station.journeys_of_train.journey_data = NULL;
            cout << "pointer changerd to null\n";
        }

        // QUERY_STATION <station_one> <start_time>
        else if (strcmp(input, "QUERY_STATION") == 0)
        {
            char station_one[32];
            cin >> station_one;
            float start_time;
            cin >> start_time;
            Entry *temp = dictionary.get(station_one);
            for (int i = 0; i < temp->journeys_of_train.tail; i++)
            {
                if (temp->journeys_of_train.journey_data[i].start_time >= start_time)
                {
                    cout << temp->journeys_of_train.journey_data[i].start_time << " " << temp->journeys_of_train.journey_data[i].station_2 << endl;
                }
            }
            temp = NULL;
        }

        // QUERY_JOURNEY <station_one> <start_time> <station_two>
        else if (strcmp(input, "QUERY_JOURNEY"))
        {
            char station_one[32];
            cin >> station_one;
            float start_time;
            cin >> start_time;
            char station_two[32];
            cin >> station_two;
            Entry *temp = dictionary.get(station_one);
            Journey temp1;
            int index;
            bool inter = 0;
            for (int i = 0; i < temp->journeys_of_train.tail; i++)
            {
                if (strcmp(temp->journeys_of_train.journey_data[i].station_2, station_two) == 0)

                {
                    temp1 = temp->journeys_of_train.journey_data[i];
                    index = i;
                    inter = 0;
                    break;
                }
                else if (intermediate(temp, i, dictionary))
                {
                    temp1 = temp->journeys_of_train.journey_data[i];
                    index = i;
                    inter = 1;
                    break;
                }
            }
            // checking with others
            for (int i = index + 1; i < temp->journeys_of_train.tail; i++)
            {
                if (strcmp(temp->journeys_of_train.journey_data[i].station_2, station_two) == 0)
                {
                    if (temp1.start_time > temp->journeys_of_train.journey_data[i].start_time)
                    {
                        temp1 = temp->journeys_of_train.journey_data[i];
                        inter = 0;
                    }
                }
                else if (intermediate(temp, i, dictionary))
                {
                    if (temp1.start_time > temp->journeys_of_train.journey_data[i].start_time)
                    {
                        temp1 = temp->journeys_of_train.journey_data[i];
                        inter = 1;
                    }
                }
            }
            // output
            if (inter)
            {
                Entry *x = dictionary.get(temp1.station_2);
                float leave_time = x->journeys_of_train.journey_data->start_time;
                cout << temp1.start_time << " " << temp1.station_2 << " " << leave_time << endl;
                continue;
                x = NULL;
            }
            else
            {
                cout << temp1.start_time << endl;
                continue;
            }
            temp = NULL;
        }
        cout << "end of iteration " << i << endl;
    }
}

void interactive()
{
    Dictionary dictionary;
    plannerHandler(dictionary);
}

void automatic()
{
    Dictionary dictionary;
    freopen("input1.in", "r", stdin);

    cout << ">>> in automatic\n";
    int N = 0;

    for (int i = 0; i >= 0; i++)
    {
        cout << "iteration " << i << endl;
        char input[32];
        cout << ">>> ";
        cin >> input;
        if (strcmp(input, "EXIT") == 0)
        {
            break;
        }

        // ADD <station_one> <start_time> <station_two> <finish_time>
        else if (strcmp(input, "ADD") == 0)
        {
            char station_one[32];
            cin >> station_one;
            float start_time;
            cin >> start_time;
            char station_two[32];
            cin >> station_two;
            float finish_time;
            cin >> finish_time;
            cout << "QUERY ADD :\n";
            cout<<"\tfor :"<<station_one<<" "<<start_time<<" "<<station_two<<" "<<finish_time<<endl;

            struct Journey data;
            data.finish_time = finish_time;
            data.start_time = start_time;
            strcmp(data.station_2, station_two);

            Entry station;
            strcpy(station.station_1, station_one);
            station.journeys_of_train.QInsert(data);

            Entry *check_station = dictionary.get(station_one);
            if (check_station == NULL)
            {
                dictionary.put(station);
                cout << "\t>>> Desired output: put executed new journey added \n";
                N++;
                cout << "\tno of stations =" << N << endl;
            }
            else
            {
                cout << "\tfor " << station_one << " ";
                check_station->journeys_of_train.QInsert(data);
                cout << "\t>>> Desired output:  old journey updated\n";
                cout << "\tno of stations =" << N << endl;
                cout << "\tnewly added route to: " << check_station->journeys_of_train.journey_data[1].station_2 << endl;
            }
            check_station = NULL;
            station.journeys_of_train.journey_data = NULL;
            cout << "pointer changerd to null\n";
        }

        // QUERY_STATION <station_one> <start_time>
        else if (strcmp(input, "QUERY_STATION") == 0)
        {
            char station_one[32];
            cin >> station_one;
            float start_time;
            cin >> start_time;
            cout << "QUERY 2 for " << station_one << endl;
            Entry *temp = dictionary.get(station_one);
            for (int i = 0; i < temp->journeys_of_train.tail; i++)
            {
                if (temp->journeys_of_train.journey_data[i].start_time >= start_time)
                {
                    cout << "\t>>> Desired output: " << endl;
                    cout << "\tJourneys of " << temp->station_1 << endl;
                    cout << "\t" << temp->journeys_of_train.journey_data[i].start_time << " " << temp->journeys_of_train.journey_data[i].station_2 << endl;
                }
            }
            temp = NULL;
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
            cout << "QUERY 2 for " << station_one << " to " << station_two << endl;
            Entry *temp = dictionary.get(station_one);
            Journey temp1;
            int index;
            bool inter = 0;
            for (int i = 0; i < temp->journeys_of_train.tail; i++)
            {
                cout << "\t1st for loop entered\n";
                if (strcmp(temp->journeys_of_train.journey_data[i].station_2, station_two) == 0)

                {
                    temp1 = temp->journeys_of_train.journey_data[i];
                    index = i;
                    inter = 0;
                    cout << "\ttemp2 added-direct\n";
                    break;
                }
                else if (intermediate(temp, i, dictionary))
                {
                    temp1 = temp->journeys_of_train.journey_data[i];
                    index = i;
                    inter = 1;
                    cout << "\ttemp2 added-intermediate\n";
                    break;
                }
                cout << "\tboth for failed for i= " << i << endl;
            }
            cout << "\ttemp added\n";
            // checking with others
            for (int i = index + 1; i < temp->journeys_of_train.tail; i++)
            {
                if (strcmp(temp->journeys_of_train.journey_data[i].station_2, station_two) == 0)
                {
                    if (temp1.start_time > temp->journeys_of_train.journey_data[i].start_time)
                    {
                        temp1 = temp->journeys_of_train.journey_data[i];
                        inter = 0;
                    }
                }
                else if (intermediate(temp, i, dictionary))
                {
                    if (temp1.start_time > temp->journeys_of_train.journey_data[i].start_time)
                    {
                        temp1 = temp->journeys_of_train.journey_data[i];
                        inter = 1;
                    }
                }
            }
            cout << "\tchecking the queue completed\n";
            // output
            if (inter)
            {
                Entry *x = dictionary.get(temp1.station_2);
                float leave_time = x->journeys_of_train.journey_data->start_time;
                cout << ">>> Desired output: \n"
                     << "\t" << temp1.start_time << " " << temp1.station_2 << " " << leave_time << endl;
                continue;
                x = NULL;
            }
            else
            {
                cout << ">>> Desired output: \n"
                     << "\t" << temp1.start_time << endl;
                continue;
            }
            temp = NULL;
        }

        cout << "end of iteration " << i << endl;
    }
}

int main()
{
    cout << "Enter 1 for interactive testing and 0 for automatic" << endl;
    int which;
    cin >> which;

    if (which == 1)
    {
        interactive();
    }
    else
    {
        automatic();
    }
    return 0;
}