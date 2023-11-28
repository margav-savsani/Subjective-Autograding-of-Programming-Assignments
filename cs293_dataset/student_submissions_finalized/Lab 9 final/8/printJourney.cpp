#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

template <typename T>
listOfObjects<T>* add_to_final(listOfObjects<T> *linked_list, listOfObjects<T>* list_obj)
{
    if(!linked_list) return list_obj;
    if(!list_obj) return list_obj;

    list_obj->next = linked_list;
    linked_list->prev=list_obj;

    return list_obj;
}

bool train_traversal(int cur_ind, int this_journey, int destinVal, StationAdjacencyList* all_adjacency)
{
    StationAdjacencyList *src_adj_list = &(all_adjacency[cur_ind]);
    listOfObjects<StationConnectionInfo *> *present_link = src_adj_list->toStations;
    int adjacentValue;
    listOfObjects<TrainInfoPerStation *> *journey;

    while(present_link)
    {

        adjacentValue = present_link->object->adjacentStnIndex;
        journey = present_link->object->trains;

        while(journey){
            if(journey->object->journeyCode == this_journey) break;
            journey = journey->next;
        }
        if(!journey)
        {
            present_link=present_link->next;
            continue;
        }

        if(adjacentValue == destinVal) return true;	

        return train_traversal(adjacentValue, this_journey, destinVal, all_adjacency);
    }


    return false;
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
    Entry<int> *temp =  this->stnNameToIndex.get(srcStnName);
    if(!temp){
        return;
    }
    int sourceVal = temp->value;
    
    temp =  this->stnNameToIndex.get(destStnName);
    if(!temp){
        return;
    } 
    int destinVal = temp->value;


    int adjacentIndex;
    listOfObjects<TrainInfoPerStation *> *train;
    bool noStationAvailable=true;

    StationAdjacencyList *src_adj = &(this->adjacency[sourceVal]);
    listOfObjects<StationConnectionInfo *> *currConnection = src_adj->toStations;
    listOfObjects<TrainInfoPerStation*> *final_trains=nullptr;


    while(currConnection)
    {
        adjacentIndex = currConnection->object->adjacentStnIndex;
        train = currConnection->object->trains;
        while(train)
        {
            if(train_traversal(adjacentIndex, train->object->journeyCode, destinVal, this->adjacency))
            {
                noStationAvailable=false;
                listOfObjects<TrainInfoPerStation *> *final_trains=nullptr;
                final_trains = add_to_final(final_trains, new listOfObjects<TrainInfoPerStation*>(train->object));
                cout << endl << endl << endl;
                this->printStationInfo(final_trains);
            }
            train = train->next;	
        }
        currConnection = currConnection->next;
    }

    if(noStationAvailable)
    {
        cout << "direct journeys not availabe between the given stations" << endl;
    } 

    return;
}


#endif
