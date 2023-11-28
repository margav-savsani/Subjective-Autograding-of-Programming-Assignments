#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName) {
    // insert your code here
    listOfObjects<TrainInfoPerStation *> *ans { nullptr };
    listOfObjects<pair<int, TrainInfoPerStation *>> *queue { nullptr };
    auto first = adjacency[stnNameToIndex.get(srcStnName)->value].toStations;
    while (first) {
        auto trn = first->object->trains;
        while (trn) {
            if (queue) {
                auto n = new listOfObjects<pair<int, TrainInfoPerStation *>> { {first->object->adjacentStnIndex, trn->object} };
                n->next = queue;
                queue = n;
            } else queue = new listOfObjects<pair<int, TrainInfoPerStation *>> { {first->object->adjacentStnIndex, trn->object} };

            auto z = stationInfo[stnNameToIndex.get(srcStnName)->value];
            while (z->object->journeyCode != trn->object->journeyCode) z = z->next;
            queue->object.second = z->object;

            trn = trn->next;
        }
        first = first->next;
    }

    while (queue) {
        pair<int, TrainInfoPerStation *> cur = queue->object;
        auto temp = queue->next;
        delete queue;
        queue = temp;
        
        // cout << cur.first << ' ' << (cur.second ? cur.second->journeyCode : 0) << ' ' << stnNameToIndex.get(destStnName)->value << endl;
        if (cur.first == stnNameToIndex.get(destStnName)->value) {
            if (ans) {
                auto a = ans;
                while (a->next) a = a->next;
                a->next = new listOfObjects<TrainInfoPerStation *> { cur.second };
            } else ans = new listOfObjects<TrainInfoPerStation *> { cur.second };
            continue;
        }
        
        auto nxt = adjacency[cur.first].toStations;
        while (nxt) {
            auto t = nxt->object->trains;
            while (t) {
                if (!cur.second || t->object->journeyCode == cur.second->journeyCode) {
                    if (queue) {
                        auto n = new listOfObjects<pair<int, TrainInfoPerStation *>> { {nxt->object->adjacentStnIndex, cur.second} };
                        n->next = queue;
                        queue = n;
                    } else queue = new listOfObjects<pair<int, TrainInfoPerStation *>> { {nxt->object->adjacentStnIndex, cur.second} };
                }
                t = t->next;
            }
            nxt = nxt->next;
        }
    }

    printStationInfo(ans);
    // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
    // for the source station and then we can print it out by invoking
    // printStationInfo that we had used in Lab 7.
    // printStationInfo is a private member function of the Planner class
    // It is declared in planner.h and implemented in planner.cpp
    
    return;
}

#endif