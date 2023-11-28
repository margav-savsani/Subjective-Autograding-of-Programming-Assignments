#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;


// to store elements of queue of BFS
struct Tuple {
    public:
    int jcode;
    int dcode;
    Tuple(int j, int d) {jcode = j; dcode = d;}
};

// finds the element in the given list
template<typename T>
bool find(T x, listOfObjects<T *> *list){
    while(list != nullptr){
        if(*(list->object) == x)
            return true;
        list = list->next;
    }
    return false;
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
    listOfObjects<TrainInfoPerStation *> *directs = nullptr;    // stores all the direct journeys
    listOfObjects<int *> *direct_jcode = nullptr;               // journey code of all the direct journeys with atleast 1 intermediate station
    listOfObjects<Tuple *> *queue = nullptr;                     // the queue for the BFS algorithm

    int dest_id = stnNameToIndex.get(destStnName)->value;       // index of the destination station
    int start_id = stnNameToIndex.get(srcStnName)->value;       // index of the source station

    listOfObjects<StationConnectionInfo *> *stations = adjacency[start_id].toStations;      // all the stations to which trains go to from source

    // traversing through all trains departing from the source to initialize the queue (distance = 1)
    // itrating through all the connected stations
    while(stations != nullptr) {
        listOfObjects<TrainInfoPerStation *> *trains = stations->object->trains;
        // iterating through all the trains to the adjacent station
        while(trains != nullptr){
            if(stations->object->adjacentStnIndex == dest_id){      // if destination found (0 stop journey), append journey to directs
                // element to be added at beginning
                listOfObjects<TrainInfoPerStation *> *new_direct = new listOfObjects<TrainInfoPerStation *> (trains->object);
                if(directs == nullptr)      // list not yet initiaized
                    directs = new_direct;
                else {                      // append new element at beginning of list
                    new_direct->next = directs;
                    directs->prev = new_direct;
                    directs = new_direct;
                }
            }
            else{                                                   // direct destination not present => perform BFS => append to queue
                // element to be added to beginning
                listOfObjects<Tuple *> *new_tuple = new listOfObjects<Tuple *> (new Tuple(trains->object->journeyCode, stations->object->adjacentStnIndex));
                if(queue == nullptr)        // list not yet initialized
                    queue = new_tuple;
                else {                      // append new element at beginning
                    new_tuple->next = queue;
                    queue->prev = new_tuple;
                    queue = new_tuple;
                }
            }
            trains = trains->next;
        }
        stations = stations->next;
    }

    // The BFS Algorithm
    while(queue != nullptr) {
        listOfObjects<StationConnectionInfo *> *stations = adjacency[queue->object->dcode].toStations;
        int code = queue->object->jcode;
        
        // removing the first element of queue
        listOfObjects<Tuple *> *temp = queue->next;
        delete queue;
        queue = temp;

        while(stations != nullptr) {
            listOfObjects<TrainInfoPerStation *> *trains = stations->object->trains;
            while(trains != nullptr) {
                if(trains->object->journeyCode == code) {       // if the journey belongs to the same journey code in context
                                                                // continue the BFS, else not needed (journey ends before reaching destination)
                    if(stations->object->adjacentStnIndex == dest_id){           // required destination reached: stop BFS and append to direct_jcode
                        listOfObjects<int *> *new_code = new listOfObjects<int *> (new int(code));
                        if(direct_jcode == nullptr)
                            direct_jcode = new_code;
                        else {
                            new_code->next = direct_jcode;
                            direct_jcode->prev = new_code;
                            direct_jcode = new_code;
                        }
                    }
                    else{                                                        // continue BFS until destination reached
                        listOfObjects<Tuple *> *new_tuple = new listOfObjects<Tuple *> (new Tuple(code, stations->object->adjacentStnIndex));
                        if(queue == nullptr)
                            queue = new_tuple;
                        else {
                            new_tuple->next = queue;
                            queue->prev = new_tuple;
                            queue = new_tuple;
                        }
                    }
                }
                trains = trains->next;
            }
            stations = stations->next;
        }
    }

    // adding all the direct journeys possible from source to destination
    listOfObjects<TrainInfoPerStation *> *journeys = stationInfo[start_id];
    while(journeys != nullptr) {
        // if this journey belongs to the class of direct journeys
        if(find(journeys->object->journeyCode, direct_jcode)){
            // appending to the directs list
            listOfObjects<TrainInfoPerStation *> *new_direct = new listOfObjects<TrainInfoPerStation *> (journeys->object);
            if(directs == nullptr)
                directs = new_direct;
            else {
                new_direct->next = directs;
                directs->prev = new_direct;
                directs = new_direct;
            }
        }
        journeys = journeys->next;
    }

    // when no direct journeys are available
    if(directs == nullptr) {
        cout << "No direct journeys available" << endl;
        return;
    }

    // printing all the journeys from source that are direct to destination
    printStationInfo(directs);

    // freeing all the space occupied by directs list
    while(directs != nullptr) {
        listOfObjects<TrainInfoPerStation *> *temp = directs->next;
        delete directs;
        directs = temp;
    }

    // freeing all the space occupied by direct_jcode list
    while(direct_jcode != nullptr) {
        listOfObjects<int *> *temp = direct_jcode->next;
        delete direct_jcode;
        direct_jcode = temp;
    }

    // freeing all the space occupied by queue list
    while(queue != nullptr) {
        listOfObjects<Tuple *> *temp = queue->next;
        delete queue;
        queue = temp;
    }
    
    return;
}

#endif
