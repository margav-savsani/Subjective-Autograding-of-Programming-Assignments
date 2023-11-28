#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

 int start = stnNameToIndex.get(srcStnName)->value; //index of the start station
  int end = stnNameToIndex.get(destStnName)->value;  //index of the end station
  StationAdjacencyList *from_source = new StationAdjacencyList();
  from_source = &adjacency[start]; //the start source
  listOfObjects<StationConnectionInfo*>* from =  from_source->toStations; //stores the to stations from source
  listOfObjects<TrainInfoPerStation *> *dest = nullptr; //setting dest to nullptr initially which stores the info of the direct trains
  listOfObjects<TrainInfoPerStation *> *dest_copy;      //head of the dest
  listOfObjects<StationConnectionInfo*>* adj_source;    //adjacent source 
  while(from!=nullptr){                         //iterating through the adjacent stations of the source
    if(from->object->adjacentStnIndex == end) { //checking if the adjacent station is the destination
      listOfObjects<TrainInfoPerStation*>* Trains1 = from->object->trains; //trains from the corresponding adjacent station
      while(Trains1!=nullptr){ //iterating through the trains from the adjacent index
        if(dest == nullptr){   //initiating the dest
          dest = new listOfObjects<TrainInfoPerStation *>(Trains1->object);
          dest_copy = dest;    //initialising the head of the dest
          Trains1 = Trains1->next;
        }
        else{
          dest->next = new listOfObjects<TrainInfoPerStation*>(Trains1->object);
          dest->next->prev = dest; //setting the prev element
          dest = dest->next;       //updating the tail
          Trains1 = Trains1->next;
        }
      }
      from = from->next;
    }
  }
  if(dest!=nullptr){ //if there is a direct train 
    printStationInfo(dest_copy);
  }
  else{ //if there is no direct train
    cout<<"No direct journeys available"<<endl;
  }

  
  return;
}

#endif
