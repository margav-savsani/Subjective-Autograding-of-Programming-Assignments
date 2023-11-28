#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class journeyObject
{
public:
    int stationIndex;
    int journeyCode;
    journeyObject(int i, int c) : stationIndex(i), journeyCode(c){};
    journeyObject(){
        stationIndex = -99;
        journeyCode = -999;
    }
};

class queueOfJourneys
{
public:
    listOfObjects<journeyObject> *head; // Head of the queue, for dequeue
    listOfObjects<journeyObject> *tail; // Tail of the queue, for enqueue
    queueOfJourneys()
    {
        head = nullptr;
        tail = nullptr;
    }
    queueOfJourneys(journeyObject j)
    {
        head = new listOfObjects<journeyObject>(j);
        tail = head;
    }
    bool empty()
    {
        return (head == nullptr);
    }
};

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{


    // insert your code here
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
                    // Add these possible routes in the queue
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

    // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
    // for the source station and then we can print it out by invoking
    // printStationInfo that we had used in Lab 7.
    // printStationInfo is a private member function of the Planner class
    // It is declared in planner.h and implemented in planner.cpp

    printStationInfo(success);

    return;
}

#endif
