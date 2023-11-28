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
listOfObjects<T>* insertIntoFront(listOfObjects<T>* , listOfObjects<T>*);
bool conditionalBFS(int, int, int, StationAdjacencyList*);

/**
 * @brief Pretty prints out a list of direct journeys between two given stations 
 * 
 * @param srcStnName Name of the source station
 * @param destStnName Name of the destination station
 */
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
    Entry<int> *entry =  this->stnNameToIndex.get(srcStnName);
    if(entry == nullptr) return;
    int src_ind = entry->value;
    entry =  this->stnNameToIndex.get(destStnName);
    if(entry == nullptr) return;
    int des_ind = entry->value;

    listOfObjects<TrainInfoPerStation*> *res=nullptr;

    StationAdjacencyList *src_adj = &(this->adjacency[src_ind]);
    listOfObjects<StationConnectionInfo *> *cur_connection = src_adj->toStations;
    listOfObjects<TrainInfoPerStation *> *connecting_train;
    int adj_ind;

    bool did_print=false;
    while(cur_connection != nullptr){
        adj_ind = cur_connection->object->adjacentStnIndex;
        connecting_train = cur_connection->object->trains;
        while(connecting_train != nullptr){
            if(conditionalBFS(adj_ind, connecting_train->object->journeyCode, des_ind, this->adjacency)){
                listOfObjects<TrainInfoPerStation *> *res=nullptr;
                res = insertIntoFront(res, new listOfObjects<TrainInfoPerStation*>(connecting_train->object));
                cout << "---------------------------------\n";
                this->printStationInfo(res);did_print=true;
            }
            connecting_train = connecting_train->next;	
        }
        cur_connection=cur_connection->next;
    }

    if(!did_print) cout << "No direct journeys available\n";

    return;
}

/**
 * @brief Runs a conditional traversal algorithm on the graph of stations, in order to find direct journeys 
 * 
 * @param cur_ind The index of the station from which traversal is to be done
 * @param cond_jc The journey code of the journey whose train is to be followed
 * @param dest_ind The index of the destination station
 * @param all_adjacency The array of adjacency lists of all the stations
 * @return boolean representing whether or not there is a train from current to destination station, with the given journey code
 */
bool conditionalBFS(int cur_ind, int cond_jc, int dest_ind, StationAdjacencyList* all_adjacency){
    StationAdjacencyList *src_adj_list = &(all_adjacency[cur_ind]);
    listOfObjects<StationConnectionInfo *> *cur_connection = src_adj_list->toStations;
    int adj_ind;
    listOfObjects<TrainInfoPerStation *> *connecting_train;

    while(cur_connection != nullptr){
        adj_ind = cur_connection->object->adjacentStnIndex;
        connecting_train = cur_connection->object->trains;

        while(connecting_train != nullptr){
            if(connecting_train->object->journeyCode == cond_jc) break;
            connecting_train = connecting_train->next;
        }
        if(connecting_train == nullptr){cur_connection=cur_connection->next;continue;}

        if(adj_ind == dest_ind) return true;	
        return conditionalBFS(adj_ind, cond_jc, dest_ind, all_adjacency);
    }


    return false;
}

template <typename T>
listOfObjects<T>* insertIntoFront(listOfObjects<T> *list, listOfObjects<T>* node){
    if(list == nullptr) return node;
    if(node == nullptr) return list;

    node->next = list;
    list->prev=node;

    return node;
}

#endif
