#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

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

    int srcStnIndex = stnNameToIndex.get(srcStnName)->value;
    int desStnIndex = stnNameToIndex.get(destStnName)->value;

    // Will Implement BFS on this mapping
    queueOfJourneys Q(journeyObject(srcStnIndex, 0));
    bool just_started = 1;

    StationAdjacencyList* mapping; // adjacency list of stations
    listOfObjects<StationConnectionInfo *> *adjStation = nullptr; // station in the adjacency list
    listOfObjects<TrainInfoPerStation *> *a_train = nullptr; // trains to this station
    
    // Successfully Found Journeys from source to destination
    listOfObjects<TrainInfoPerStation*> *success = nullptr;

    // Start BFS
    while (!Q.empty()) {
        journeyObject currentJourney = Q.head->object;
        int traincode = currentJourney.journeyCode;

        // Pop the queue
        listOfObjects<journeyObject> *newhead = Q.head->next;
        if (Q.tail == Q.head)
        {
            Q.tail = newhead;
        }
        delete Q.head;
        Q.head = newhead;

        // Traverse journeys in the adjacency list

        mapping = adjacency + currentJourney.stationIndex;
        adjStation = mapping->toStations;
        while (adjStation != nullptr) {
            a_train = adjStation->object->trains;
            while (a_train != nullptr) {
                if (a_train->object->journeyCode == traincode||just_started) {
                    if (adjStation->object->adjacentStnIndex==desStnIndex){
                        // Reached destination
                        if (success==nullptr){
                            success = new listOfObjects<TrainInfoPerStation*>(a_train->object);
                        }
                        else {
                            success->prev = new listOfObjects<TrainInfoPerStation*>(a_train->object);
                            success->prev->next = success;
                            success = success->prev;
                        }
                        a_train = a_train->next;
                        continue;
                    }
                    // Add new entry
                    journeyObject newentry(adjStation->object->adjacentStnIndex, a_train->object->journeyCode);
                    listOfObjects<journeyObject> *possibility = new listOfObjects<journeyObject>(newentry);
                    if (Q.tail != nullptr) {
                        Q.tail->next = possibility;
                        possibility->prev = Q.tail;
                    }
                    else {
                        Q.head = possibility;
                    }
                    Q.tail = possibility;
                }
                a_train = a_train->next;
            }
            adjStation = adjStation->next;
        }
        just_started = 0;
    }
    printStationInfo(success);

    return;
}

#endif
