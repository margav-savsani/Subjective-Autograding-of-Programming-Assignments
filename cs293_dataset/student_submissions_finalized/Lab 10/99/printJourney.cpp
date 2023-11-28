#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP
#ifndef PLANNER_H
#include "planner.h"
#endif
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
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
    Entry<int> * src = stnNameToIndex.get(srcStnName);
    Entry<int> * dest = stnNameToIndex.get(destStnName);
    // invalid source or destination
    if (src == nullptr || dest == nullptr) 
    {
        cout << "No direct journeys available\n";
        return;
    }
    int srcIndex = src->value;
    int destIndex = dest->value;

    listOfObjects<TrainInfoPerStation *> * journeys = nullptr; // stores the list of trains with direct journeys
    listOfObjects<TrainInfoPerStation *> * temp = nullptr; // points to the end of the journeys list

    // make a "queue" of the stations not yet visited
    Stations * forQueue = new Stations(0, nullptr);
    listOfObjects<Stations *> * queue = new listOfObjects<Stations *>(forQueue);
    listOfObjects<Stations *> * queueEnd = queue; // points to the end of the queue
    int count = 0;

    // stores the list of neighbours of the source
    listOfObjects<StationConnectionInfo *> * srcNeighbours = adjacency[srcIndex].toStations;
    // get the list of trains associated with the source and the destination
    listOfObjects<TrainInfoPerStation *> * fromSrc = stationInfo[srcIndex];
    listOfObjects<TrainInfoPerStation *> * srcTemp = fromSrc;
    listOfObjects<TrainInfoPerStation *> * toDest = stationInfo[destIndex];
    listOfObjects<TrainInfoPerStation *> * destTemp = toDest;
    // going over all the neighbours (to which one can go from the source) of the source
    while (srcNeighbours != nullptr)
    {
        // if the neighbour is the destination, directly add it to the list of journeys
        if (srcNeighbours->object->adjacentStnIndex == destIndex)
        {
            while (srcTemp != nullptr)
            {
                destTemp = toDest;
                while (destTemp != nullptr)
                {
                    if (srcTemp->object->journeyCode == destTemp->object->journeyCode)
                    {
                        if (journeys == nullptr)
                        {
                            journeys = new listOfObjects<TrainInfoPerStation *>(srcTemp->object);
                            temp = journeys;
                        }
                        else
                        {
                            temp->next = new listOfObjects<TrainInfoPerStation *>(srcTemp->object);
                            temp = temp->next;
                        }
                    }
                    destTemp = destTemp->next;
                }
                srcTemp = srcTemp->next;
            }
        }
        // add it to the queue otherwise
        else
        {
            Stations * nextInQueue = new Stations(srcNeighbours->object->adjacentStnIndex, srcNeighbours->object->trains);
            if (count == 0)
            {
                queue->object = nextInQueue;
                count++;
            }
            else
            {
                queueEnd->next = new listOfObjects<Stations *>(nextInQueue);
                queueEnd = queueEnd->next;
            }
        }
        srcNeighbours = srcNeighbours->next;
    }

    // bfs while the queue is non-empty
    while (queue != nullptr)
    {
        Stations * currStation = queue->object;
        listOfObjects<StationConnectionInfo *> * currNeighbours = adjacency[currStation->index].toStations;

        while (currNeighbours != nullptr)
        {
            int neighbourIndex = currNeighbours->object->adjacentStnIndex; // index of the neighbour
            listOfObjects<TrainInfoPerStation *> * neighbourTrains = currNeighbours->object->trains; // trains from this neighbour
            listOfObjects<TrainInfoPerStation *> * filteredTrains = nullptr; // the trains that already have a direct path so far

            // for all the trains from one neighbour...
            while (neighbourTrains != nullptr)
            {
                // ... if there is a train from the current station to that neighbour, it is allowed
                if (currStation->isPresent(neighbourTrains->object->journeyCode))
                {
                    if (filteredTrains == nullptr)
                    {
                        filteredTrains = new listOfObjects<TrainInfoPerStation *>(neighbourTrains->object);
                    }
                    else
                    {
                        filteredTrains->next = new listOfObjects<TrainInfoPerStation *>(neighbourTrains->object);
                        filteredTrains = filteredTrains->next;
                    }
                }
                neighbourTrains = neighbourTrains->next;
            }
            // keep going only if there is a valid train upto that point
            if (filteredTrains != nullptr)
            {
                // if the path is complete
                if (destIndex == neighbourIndex)
                {
                    if (journeys == nullptr)
                    {
                        journeys = filteredTrains;
                        temp = journeys;
                    }
                    else
                    {
                        temp->next = filteredTrains;
                        temp = temp->next;
                    }
                }
                // add the station to the queue
                Stations * nextInQueue = new Stations(neighbourIndex, filteredTrains);
                queueEnd->next = new listOfObjects<Stations *>(nextInQueue);
                queueEnd = queueEnd->next;
            }
            // go to the next neighbour
            currNeighbours = currNeighbours->next;
        }
        // pop the first element from the queue
        queue = queue->next;
    }
    
    if (journeys != nullptr) printStationInfo(journeys);
    else cout << "No direct journeys available\n";
  
}

#endif
