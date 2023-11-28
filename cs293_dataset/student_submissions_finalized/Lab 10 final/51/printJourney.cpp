#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

void printjourney(listOfObjects<TrainInfoPerStation*>* travel,int maxstopovers){
  
  listOfObjects<TrainInfoPerStation*>* dummy;
  listOfObjects<TrainInfoPerStation*>* possibility;
  dummy = travel;
  cout<<"--------"<<'\n'<<endl;
  
  while (dummy != nullptr) {
    possibility = dummy;
    dummy = dummy->next;
  }
  for (int i =1;possibility != nullptr;i++) {
    cout<<"train "<< i <<" paths"<<":"<<endl;
    cout<<possibility->object->journeyCode<<" "<<possibility->object->arrTime<<" "<<possibility->object->depTime<<endl;
    possibility = possibility->prev;
  }
  cout<<'\n';
}
bool Goable(int maxStopOvers, int maxTransitTime,StationAdjacencyList* adjacency,int startstnindex,int laststnindex, int jcode,  listOfObjects<TrainInfoPerStation*>* path) {
  if(maxStopOvers < 0) return false; 
  if(startstnindex == laststnindex) {
    printjourney(path,maxStopOvers);
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
        Goable( maxStopOvers,maxTransitTime,adjacency,toStations->object->adjacentStnIndex,laststnindex, jcode,path);
      }
      else if (trains->object->journeyCode != jcode) {
        new_path = trains;
        new_path->next = new listOfObjects<TrainInfoPerStation*>(path->object);
        path->prev = new listOfObjects<TrainInfoPerStation*>(new_path->object);
        Goable(maxStopOvers-1,maxTransitTime,adjacency,toStations->object->adjacentStnIndex,laststnindex, trains->object->journeyCode, new_path);
      }
      trains = trains->next; 
    }
    toStations = toStations->next;
  } 
  return true;
}



void Planner ::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime) {
  
  int index1 = stnNameToIndex.get(srcStnName)->value;
  int index2 = stnNameToIndex.get(destStnName)->value;      
  
  bool travel = false;
  listOfObjects<TrainInfoPerStation*>* dum_trains;
  listOfObjects<TrainInfoPerStation*>* possibility;
  listOfObjects<StationConnectionInfo*>* toStations = adjacency[index1].toStations;
  

    while (toStations != nullptr) {
      dum_trains = toStations->object->trains;
      while(dum_trains != nullptr) {
        possibility = dum_trains;
        possibility->next = nullptr;
        possibility->prev = nullptr;
        Goable(maxStopOvers,maxTransitTime,adjacency,toStations->object->adjacentStnIndex,index2, dum_trains->object->journeyCode,possibility);
        dum_trains = dum_trains->next;
      }
      toStations = toStations->next;
    }
  
}


bool travel(int index1,int index2, int jcode,StationAdjacencyList* adjacency) {
  if(index1 == index2) return true;
  listOfObjects<TrainInfoPerStation*>* d_trains;
   listOfObjects<StationConnectionInfo*>* g_Stations = adjacency[index1].toStations;
  while (g_Stations != nullptr) {
    d_trains = g_Stations->object->trains;
    while(d_trains != nullptr) {
	
    if (d_trains->object->journeyCode == jcode) {
    return travel(g_Stations->object->adjacentStnIndex,index2, jcode,adjacency);
      }
      d_trains = d_trains->next;
    }
    g_Stations = g_Stations->next;
  }
  return false;
}





#endif