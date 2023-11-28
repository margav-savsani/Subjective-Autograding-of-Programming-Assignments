#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class Node
{
public:
    int index;

    Node(int i)
    {
        index = i;
    }
}

void
Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

    // insert your code here

    cout << "This function is to be implemented by you." << endl;

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

    Node *source = new Node(indexStn1);
    listOfObjects<Node *> *queue = new listOfObjects<Node *>(source); // source station is inserted in the queue
    listOfObjects<TrainInfoPerStation *> *intermediate = nullptr;     // list of intermediate stations from src to dest
    listOfObjects<TrainInfoPerStation *> *directTrains = nullptr;     // list of direct trains from src to dest.

    while (temp != nullptr)
    {
        if (temp->object->adjacentStnIndex == indexStn1)
        {
            if (directTrains == nullptr)
            {
                directTrains = new listOfObjects<TrainInfoPerStation *>(new listOfObjects<TrainInfoPerStation *>(temp->object->trains));
            }
        }
        temp = temp->next;
    }
    printStationInfo(directTrains);
    return;
}

#endif
