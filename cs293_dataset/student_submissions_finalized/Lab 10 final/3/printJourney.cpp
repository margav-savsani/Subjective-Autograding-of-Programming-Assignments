#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

bool isTravelable(StationAdjacencyList* adjacency,int startstnindex,int laststnindex, int jcode) {
  if(startstnindex == laststnindex) return true;
  listOfObjects<StationConnectionInfo*>* toStations = adjacency[startstnindex].toStations;
  listOfObjects<TrainInfoPerStation*>* trains;

  while (toStations != nullptr) {
    trains = toStations->object->trains;
    while(trains != nullptr) {
      if (trains->object->journeyCode == jcode) {
        return isTravelable(adjacency,toStations->object->adjacentStnIndex,laststnindex, jcode);
      }
      trains = trains->next;
    }
    toStations = toStations->next;
  }
  return false;
}

void add_object(listOfObjects<TrainInfoPerStation*>* train1,listOfObjects<TrainInfoPerStation*>* train2) {
  listOfObjects<TrainInfoPerStation*>* temp_train1 = train1->next;
  listOfObjects<TrainInfoPerStation*>* temp_train2 = train1->prev;
  train1 = train2;
  train1->next = temp_train1;
  train1->prev = temp_train2;

}
void printpath(StationAdjacencyList* adjacency, listOfObjects<TrainInfoPerStation*>* path){
  listOfObjects<TrainInfoPerStation*>* new_path;
  listOfObjects<TrainInfoPerStation*>* temp;
  cout<<"****************************"<<'\n'<<"NEW PATH"<<endl;

  temp = path;
  while (temp != nullptr) {
    new_path = temp;
    temp = temp->next;
  }
  for (int temp =1;new_path != nullptr;temp++) {
    cout<<"train "<<temp<<" possibilities"<<":"<<endl;
    cout<<new_path->object->journeyCode<<" "<<new_path->object->arrTime<<" "<<new_path->object->depTime<<endl;
    new_path = new_path->prev;
  }
  cout<<'\n';
}

bool isGoable(StationAdjacencyList* adjacency,int startstnindex,int laststnindex, int jcode, int maxStopOvers, int maxTransitTime, listOfObjects<TrainInfoPerStation*>* path) {
  if(maxStopOvers < 0) return false; 
  if(startstnindex == laststnindex) {
    printpath(adjacency,path);
    return true;
  }
  bool isgoable = false;
  listOfObjects<StationConnectionInfo*>* toStations = adjacency[startstnindex].toStations;
  listOfObjects<TrainInfoPerStation*>* trains;
  listOfObjects<TrainInfoPerStation*>* new_path;

  while (toStations != nullptr) {
    trains = toStations->object->trains;
    while(trains != nullptr) {
      if (trains->object->journeyCode == jcode) {
        isGoable(adjacency,toStations->object->adjacentStnIndex,laststnindex, jcode, maxStopOvers,maxTransitTime,path);
      }
      else if (trains->object->journeyCode != jcode) {
        new_path = trains;
        new_path->next = new listOfObjects<TrainInfoPerStation*>(path->object);
        path->prev = new listOfObjects<TrainInfoPerStation*>(new_path->object);
        isGoable(adjacency,toStations->object->adjacentStnIndex,laststnindex, trains->object->journeyCode, maxStopOvers-1,maxTransitTime,new_path);
      }
      trains = trains->next; 
    }
    toStations = toStations->next;
  } 
  return true;
}

void Planner ::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime) {
  Entry<int> *index1 = stnNameToIndex.get(srcStnName);
  int stn_index1 = index1->value;

  Entry<int> *index2 = stnNameToIndex.get(destStnName);
  int stn_index2 = index2->value;

  bool istravelable = false;
  listOfObjects<StationConnectionInfo*>* toStations = adjacency[stn_index1].toStations;
  listOfObjects<TrainInfoPerStation*>* trains;
  listOfObjects<TrainInfoPerStation*>* new_path;

    while (toStations != nullptr) {
      trains = toStations->object->trains;
      while(trains != nullptr) {
        new_path = trains;
        new_path->next = nullptr;
        new_path->prev = nullptr;
        isGoable(adjacency,toStations->object->adjacentStnIndex,stn_index2, trains->object->journeyCode,maxStopOvers,maxTransitTime,new_path);
        trains = trains->next;
      }
      toStations = toStations->next;
    }
  
}

#endif