#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

listOfObjects<TrainInfoPerStation *>* dfs(int stn_idx, TrainInfoPerStation *) {

}
    
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime) {

    // insert your code here

    listOfObjects<pair<int, TrainInfoPerStation *>> *queue { nullptr };
    auto first = adjacency[stnNameToIndex.get(srcStnName)->value].toStations;
    while (first) {
        auto trn = first->object->trains;
        while (trn) {
            auto z = stationInfo[stnNameToIndex.get(srcStnName)->value];
            while (z->object->journeyCode != trn->object->journeyCode) z = z->next;
            queue->object.second = z->object;

            printStationInfo(dfs(first->object->adjacentStnIndex, z->object));
            trn = trn->next;
        }
        first = first->next;
    }
    

    // Whenever you need to print a journey, construct a
    // listOfObjects<TrainInfoPerStation *> appropriately, and then
    // use printStationInfo that we had used in Lab 7.
    // printStationInfo is a private member function of
    // the Planner class. It is declared in planner.h and implemented in
    // planner.cpp

    return;
}

#endif