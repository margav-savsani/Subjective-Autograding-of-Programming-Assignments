#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <deque>

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

    // insert your code here

    // cout << "This function is to be implemented by you." << endl;

    // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
    // for the source station and then we can print it out by invoking
    // printStationInfo that we had used in Lab 7.
    // printStationInfo is a private member function of the Planner class
    // It is declared in planner.h and implemented in planner.cpp

    int a = stnNameToIndex.findFreeIndex(srcStnName);
    int b = stnNameToIndex.findFreeIndex(srcStnName);

    StationAdjacencyList L = adjacency[a];
    listOfObjects<StationConnectionInfo *> *T = L.toStations;
    
    while (T != nullptr)
    {
        StationConnectionInfo c = T.object;
        listOfObjects<TrainInfoPerStation *> *tr = c->trains;
        while (tr != nullptr)
        {
            deque<int> dq;
            dq.push_back(T->object->adjacentStnIndex);
            while (!dq.empty())
            {
                StationAdjacencyList v = adjacency[dq.front()];
                dq.pop_front();
                listOfObjects<StationConnectionInfo *> *i = v.toStations;
                listOfObjects<TrainInfoPerStation *> *tra = v->toStations->trains;
                while (tra != nullptr)
                {
                    if (tra->object->journeyCode == tr->object->journeyCode)
                    {
                        if (i->object->adjacentStnIndex == b)
                        {
                        }
                        else
                        {
                            dq.push_back(i->object->adjacentStnIndex);
                        }
                    }
                }
            }
            tr = tr->next;
        }

        T = T->next;
    }

    cout << "No direct journeys available";
}

#endif
