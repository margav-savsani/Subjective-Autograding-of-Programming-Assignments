#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

listOfObjects<listOfObjects<TrainInfoPerStation *> *> *DFS(int indexStn1, int indexStn2, StationAdjacencyList adjacency[], StationAdjacencyList expandedAdjacency[], listOfObjects<listOfObjects<TrainInfoPerStation *> *> *journeys, listOfObjects<TrainInfoPerStation *> *journey, int remainingStopOvers, int MaxTrainsitTime, int arrTime)
{
    if (expandedAdjacency[indexStn1].toStations == nullptr) // Computing expanded list
    {
        listOfObjects<StationConnectionInfo *> *t = expandedAdjacency[indexStn1].toStations;
        listOfObjects<StationConnectionInfo *> *tempStn = adjacency[indexStn1].toStations;
        while (tempStn != nullptr)
        {
            listOfObjects<TrainInfoPerStation *> *train = tempStn->object->trains;
            listOfObjects<TrainInfoPerStation *> *expandedTrain;
            while (train != nullptr)
            {
                for (int i = 0; i < 7; i++)
                {
                    if (train->object->daysOfWeek[i])
                    {
                        TrainInfoPerStation *t1 = new TrainInfoPerStation(train->object->journeyCode, train->object->stopSeq, train->object->arrTime, train->object->depTime);
                        t1->setDayOfWeek(i);
                        if (expandedTrain == nullptr)
                        {
                            expandedTrain = new listOfObjects<TrainInfoPerStation *>(t1);
                        }
                        else
                        {
                            expandedTrain->next = new listOfObjects<TrainInfoPerStation *>(t1);
                            expandedTrain = expandedTrain->next;
                        }
                    }
                }
                train = train->next;
            }
            StationConnectionInfo *t2 = new StationConnectionInfo(tempStn->object->adjacentStnIndex);
            t2->trains = expandedTrain;
            if (t == nullptr)
            {
                t = new listOfObjects<StationConnectionInfo *>(t2);
            }
            else
            {
                t->next = new listOfObjects<StationConnectionInfo *>(t2);
                t = t->next;
            }
            tempStn = tempStn->next;
        }
    }

    if (remainingStopOvers == 0)
    {
        return journeys;
    }

    listOfObjects<StationConnectionInfo *> *toStn = expandedAdjacency[indexStn1].toStations;
    while (toStn != nullptr)
    {
        listOfObjects<TrainInfoPerStation *> *train = toStn->object->trains;
        while (train != nullptr)
        {
            if (arrTime == -1 || train->object->depTime - arrTime <= MaxTrainsitTime)
            {
                listOfObjects<TrainInfoPerStation *> *j = journey;
                if (journey == nullptr)
                {
                    journey = new listOfObjects<TrainInfoPerStation *>(train->object);
                }
                else
                {
                    while (j->next != nullptr)
                        j = j->next;
                    j->next = new listOfObjects<TrainInfoPerStation *>(train->object);
                }
                if (toStn->object->adjacentStnIndex == indexStn2)
                {
                    if (journeys == nullptr)
                    {
                        journeys = new listOfObjects<listOfObjects<TrainInfoPerStation *> *>(journey);
                    }
                    else
                    {
                        listOfObjects<listOfObjects<TrainInfoPerStation *> *> *js = journeys;
                        while (js->next != nullptr)
                            js = js->next;
                        js->next = new listOfObjects<listOfObjects<TrainInfoPerStation *> *>(journey);
                    }
                    continue;
                }
                int nextStation = toStn->object->adjacentStnIndex;
                listOfObjects<StationConnectionInfo *> *from = expandedAdjacency[nextStation].fromStations;
                while (from != nullptr)
                {
                    if (from->object->adjacentStnIndex == indexStn1)
                        break;
                    from = from->next;
                }
                listOfObjects<TrainInfoPerStation *> *tr = from->object->trains;
                while (tr != nullptr)
                {
                    if (tr->object->journeyCode == train->object->journeyCode)
                        break;
                    tr = tr->next;
                }
                journeys = DFS(nextStation, indexStn2, adjacency, expandedAdjacency, journeys, journey, remainingStopOvers - 1, MaxTrainsitTime, tr->object->arrTime);
            }
            train = train->next;
        }
        listOfObjects<TrainInfoPerStation *> *last = journey;
        if (last != nullptr)
        {
            if (last->next == nullptr)
                last == nullptr;
            else
            {
                while (last->next->next != nullptr)
                    last = last->next;
                last->next = nullptr;
            }
        }

        toStn = toStn->next;
    }
    return journeys;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

    // insert your code here

    // cout << "This function is to be implemented by you." << endl;

    // Whenever you need to print a journey, construct a
    // listOfObjects<TrainInfoPerStation *> appropriately, and then
    // use printStationInfo that we had used in Lab 7.
    // printStationInfo is a private member function of
    // the Planner class. It is declared in planner.h and implemented in
    // planner.cpp
    int indexStn1 = stnNameToIndex.get(srcStnName)->value;
    int indexStn2 = stnNameToIndex.get(destStnName)->value;                         // indices of src and dest stations
    listOfObjects<StationConnectionInfo *> *temp = adjacency[indexStn1].toStations; // list of stations adjacent to src
    listOfObjects<TrainInfoPerStation *> *srcTrains = stationInfo[indexStn1];       // trains from src

    StationAdjacencyList expandedAdjacency[DICT_SIZE];
    listOfObjects<listOfObjects<TrainInfoPerStation *> *> *journeys;
    listOfObjects<TrainInfoPerStation *> *journey;

    journeys = DFS(indexStn1, indexStn2, adjacency, expandedAdjacency, journeys, journey, maxStopOvers, maxTransitTime, -1);
    listOfObjects<listOfObjects<TrainInfoPerStation *> *> *js = journeys;
    while (js != nullptr)
    {   
        cout << 1 << endl;
        printStationInfo(js->object);
        js->next;
    }
}

#endif
