#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include<string>

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  int srcindex = stnNameToIndex.get(srcStnName)->value;
  int destindex = stnNameToIndex.get(destStnName)->value;

  StationAdjacencyList srcadj = adjacency[srcindex];
  listOfObjects<StationConnectionInfo *> *srcadjlist =  srcadj.toStations;
  
  StationAdjacencyList destadj = adjacency[destindex];
  listOfObjects<StationConnectionInfo *> *destadjlist = destadj.fromStations;

  // creating an array of trains going from src station
  TrainInfoPerStation **srcarray;
  srcarray = new TrainInfoPerStation *[100];
  int srccount=0;
  int destcount=0;
  int i=0;
  while(srcadjlist!=nullptr){ // iterating through stations
    listOfObjects<TrainInfoPerStation *> *srctrainslst = srcadjlist->object->trains;
    while(srctrainslst!=nullptr){ //expanding linked list
      srcarray[i]=srctrainslst->object;
      srccount++; // increasing no.of trains in array till now 
      i++;
      srctrainslst=srctrainslst->next;
    }
    srcadjlist=srcadjlist->next;
  }  

  // creating an array of trains coming to dest station
  TrainInfoPerStation **destarray;
  destarray = new TrainInfoPerStation *[100];
  int j=0;
  while(destadjlist!=nullptr){ // iterating through stations
    listOfObjects<TrainInfoPerStation *> *destrainslst = destadjlist->object->trains;
    while(destrainslst!=nullptr){ //expanding linked list
      destarray[j]=destrainslst->object;
      destcount++;  // increasing no.of trains till now in array
      j++;
      destrainslst=destrainslst->next;
    }
    destadjlist=destadjlist->next;
  }

  listOfObjects<TrainInfoPerStation *> *tmplst;
  listOfObjects<TrainInfoPerStation *> *dirlst = tmplst;
  // creating a linked list of common trains in both arrays
  for(int i=0;i<srccount;i++){
    for(int j=0;j<destcount;j++){
      if(srcarray[i]->journeyCode==destarray[j]->journeyCode){  // checking journeycodes of trains to see if they are same trains
        tmplst->object=srcarray[i];
        tmplst=tmplst->next;
      }
    }
  }

  printStationInfo(dirlst);
  
  return;
}

#endif
