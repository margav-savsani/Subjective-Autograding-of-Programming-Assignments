#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
bool start_check(int startt,int endd,int journey_code, StationAdjacencyList adjacency[]){
    int j=0;
    int i=0;
    int index_adj;
    if(startt==endd){return true;}
    else if (startt==-1){return false;}
    else{
        listOfObjects<StationConnectionInfo *> *station = adjacency[startt].toStations;
        while(station!=nullptr){
            index_adj = station->object->adjacentStnIndex;
            listOfObjects<TrainInfoPerStation *> *X = station->object->trains;
            while(X!=nullptr){
                if(X->object->journeyCode == journey_code){
                   
                }
                else{X=X->next;}
            }
            if(j>0){i++;break;}
            else{station=station->next;}
        }
        if(i>0){return(start_check(index_adj,endd,journey_code,adjacency));}
        else{return false;}
    }
}
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  return;
}

#endif
