#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include<queue>

using namespace std;

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

    // insert your code here

    cout << "This function is to be implemented by you." << endl;

    // Whenever you need to print a journey, construct a
    // listOfObjects<TrainInfoPerStation *> appropriately, and then
    // use printStationInfo that we had used in Lab 7.
    // printStationInfo is a private member function of
    // the Planner class. It is declared in planner.h and implemented in
    // planner.cpp

    int s_i = stnNameToIndex.findFreeIndex(srcStnName);
    int d_i = stnNameToIndex.findFreeIndex(srcStnName);

    StationAdjacencyList L = adjacency[s_i];
    listOfObjects<StationConnectionInfo *> *T = L.toStations;

    while (T != nullptr)
    {   
        StationConnectionInfo* c = T->object;
        listOfObjects<TrainInfoPerStation *> *tr = c->trains;

        while (tr != nullptr)
        {
            queue<int> q;
            q.push(T->object->adjacentStnIndex);
            while (!q.empty())
            {
                StationAdjacencyList v = adjacency[q.front()];
                q.pop();
                listOfObjects<StationConnectionInfo *> *i = v.toStations;
                listOfObjects<TrainInfoPerStation *> *tra = v.toStations->object->trains;
                while (tra != nullptr)
                {
                    if (tra->object->journeyCode == tr->object->journeyCode)
                    {
                        if (i->object->adjacentStnIndex == d_i)
                        {
                        }
                        else
                        {
                            q.push(i->object->adjacentStnIndex);
                        }
                    }
                }
            }
            tr = tr->next;
        }
        T = T->next;
    }

    
}

#endif
