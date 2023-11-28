#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
bool recursion(int journeyCode,int index,int dest,StationAdjacencyList *adjacency){
  listOfObjects<StationConnectionInfo*> *d=adjacency[index].toStations;
  if(index==dest){
      return true;
    }
  while(d!=nullptr){
      listOfObjects<TrainInfoPerStation*> *toadd=d->object->trains;
      while(toadd!=nullptr){
        if(journeyCode==toadd->object->journeyCode){
        return recursion(toadd->object->journeyCode,d->object->adjacentStnIndex,dest,adjacency);
        }
        toadd=toadd->next;
      }
    d=d->next;
  }
  return false;
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  int src=stnNameToIndex.get(srcStnName)->value;
  int dest=stnNameToIndex.get(destStnName)->value;
  listOfObjects<StationConnectionInfo*> *dummy=adjacency[src].toStations;
  TrainInfoPerStation*t=new TrainInfoPerStation(0,0,0,0);
  listOfObjects<TrainInfoPerStation*> *pointer=new listOfObjects<TrainInfoPerStation*> (t);
  listOfObjects<TrainInfoPerStation*> *output=pointer;

  while(dummy!=nullptr){
      listOfObjects<TrainInfoPerStation*> *toadd=dummy->object->trains;
      while(toadd!=nullptr){
        if(recursion(toadd->object->journeyCode,dummy->object->adjacentStnIndex,dest,adjacency)){
          pointer->next=new listOfObjects<TrainInfoPerStation *>(toadd->object);
          pointer=pointer->next;
        }
        toadd=toadd->next;
      }
    dummy=dummy->next;
  }
  if(output->next==nullptr) {
    cout<<"No direct journey's available"<<endl;
  }
  else{
    printStationInfo(output->next);
  }

  // insert your code here
  
  //cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}


#endif