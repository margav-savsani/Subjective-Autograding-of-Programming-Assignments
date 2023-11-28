#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#include "planner.h"
#include <vector>
#include <list>
#endif

using namespace std;
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  int srcStnIndex=stnNameToIndex.get(srcStnName)->value;
  int destStnIndex=stnNameToIndex.get(destStnName)->value;
  listOfObjects<StationConnectionInfo *> *cur_to_list=adjacency[srcStnIndex].toStations;

  
  list<int> node_queue;
  list<int> stops_queue;
  list<vector<TrainInfoPerStation*>> trains_queue;

  int adjIndex;
  listOfObjects<TrainInfoPerStation *> *trains;
  vector<int> BFS_roots;
  while(cur_to_list!=nullptr) {
    adjIndex=cur_to_list->object->adjacentStnIndex;
    trains=cur_to_list->object->trains;

    while(trains!=nullptr) {
      vector<std::string> temp_stations;
      vector<TrainInfoPerStation*> temp_trains;
      temp_trains.push_back(trains->object);

      node_queue.push_back(adjIndex);
      trains_queue.push_back(temp_trains);
      stops_queue.push_back(0);

      trains=trains->next;
    }
    cur_to_list=cur_to_list->next;
  }

  int cur_node;
  vector<TrainInfoPerStation*> cur_trains;
  int cur_stops;

  while(!node_queue.empty()) {

    cur_node=node_queue.front();
    cur_trains=trains_queue.front();
    cur_stops=stops_queue.front();

    node_queue.pop_front();
    trains_queue.pop_front();
    stops_queue.pop_front();

    if(cur_stops>maxStopOvers) {
      continue;
    }

    if(cur_node==destStnIndex) {
      bool yes_val=true;
      for(int alpha=1; alpha<cur_trains.size()-1; alpha++) {
        int cur_arr_time=cur_trains[alpha]->arrTime;
        int cur_dep_time=cur_trains[alpha+1]->depTime;
        int arr_day, dep_day;
        for(int gamma=0; gamma<7; gamma++) {
          if(cur_trains[alpha]->daysOfWeek[gamma]) arr_day=gamma;
          if(cur_trains[alpha+1]->daysOfWeek[gamma]) dep_day=gamma;
        }
        if (!(cur_dep_time-cur_arr_time<maxTransitTime*60)) {
          yes_val=false;
          break;
        }
      }

      if(!yes_val) {
        continue;
      }

      cout<<"-------------------\n";
      cout<<"Journey:\n\n";

      cout<<"Number of stop-overs: "<<cur_stops<<"\n";
      for(int kappa=0; kappa<cur_trains.size(); kappa++) {
        cout<<"Journey Code of train "<<kappa+1<<": "<<cur_trains[kappa]->journeyCode<<"\n";
      }

      listOfObjects<TrainInfoPerStation*>* final_train_list = new listOfObjects<TrainInfoPerStation*>(cur_trains[0]);
      listOfObjects<TrainInfoPerStation*>* cur_train_node=final_train_list;
      listOfObjects<TrainInfoPerStation*>* temp_train_node;
      for(int beta=1; beta<cur_trains.size(); beta++) {
        temp_train_node=new listOfObjects<TrainInfoPerStation*>(cur_trains[beta]);
        if(temp_train_node->object!=cur_train_node->object) {
          cur_train_node->next=temp_train_node;
          cur_train_node=temp_train_node;
        }
      }

      cout<<"Detailed information of trains:\n";
      printStationInfo(final_train_list);

      continue;
    }
    cur_to_list=adjacency[cur_node].toStations;
    while(cur_to_list!=nullptr) {
      adjIndex=cur_to_list->object->adjacentStnIndex;
      trains=cur_to_list->object->trains;
      while(trains!=nullptr) {
        vector<TrainInfoPerStation*> temp_trains=cur_trains;
        temp_trains.push_back(trains->object);

        node_queue.push_back(adjIndex);
        trains_queue.push_back(temp_trains);
        stops_queue.push_back(cur_stops+1);

        trains=trains->next;
      }
      cur_to_list=cur_to_list->next;
    }
  }
  
  return;
}

#endif
