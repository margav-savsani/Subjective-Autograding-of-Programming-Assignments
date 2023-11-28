#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <queue>
#include <list>
#include <tuple>

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

  int srcStnIndex=stnNameToIndex.get(srcStnName)->value;
  int destStnIndex=stnNameToIndex.get(destStnName)->value;
  listOfObjects<StationConnectionInfo *> *cur_to_list=adjacency[srcStnIndex].toStations;

  vector<int> list_of_journey_codes;
  vector<int> BFS_roots;
  listOfObjects<TrainInfoPerStation *> *trains;
  int adjIndex;
  while(cur_to_list!=nullptr) {
    adjIndex=cur_to_list->object->adjacentStnIndex;
    trains=cur_to_list->object->trains;
    while(trains!=nullptr) {
      list_of_journey_codes.push_back(trains->object->journeyCode);
      BFS_roots.push_back(adjIndex);
      trains=trains->next;
    }
    cur_to_list=cur_to_list->next;
  }

  for(int theta=0; theta<BFS_roots.size(); theta++) {
    int cur_root=BFS_roots[theta];
    int cur_journey_code=list_of_journey_codes[theta];
    int cur_node;
    list<int> queue;
    queue.push_back(cur_root);
    while(!queue.empty()) {
      cur_node=queue.front();
      if(cur_node==destStnIndex) {
        cout<<"Journey Code: "<<cur_journey_code<<"\n";
        break;
      }
      queue.pop_front();
      cur_to_list=adjacency[cur_node].toStations;
      while(cur_to_list!=nullptr) {
        adjIndex=cur_to_list->object->adjacentStnIndex;
        trains=cur_to_list->object->trains;
        while(trains!=nullptr) {
          if(trains->object->journeyCode==cur_journey_code) {
            queue.push_back(adjIndex);
          }
          trains=trains->next;
        }
        cur_to_list=cur_to_list->next;
      }
    }
  }  
  return;
}

#endif
