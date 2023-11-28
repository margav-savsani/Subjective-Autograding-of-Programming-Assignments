#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;


void add(listOfObjects<int> * ptr,int k){
  if(ptr->object==-1){
    ptr->object = k;
    return;
  }
  while(ptr->next!=NULL){
    ptr = ptr->next;
  }
  ptr->next = new listOfObjects<int>(k);
  return;
}

void addifpresent(listOfObjects<int> *ptr, int k, listOfObjects<int> *fromstart){
  bool b = false;
  if(ptr->object==-1){
     b = true;
  }
  while(ptr->next!=NULL){
    ptr = ptr->next;
  }
  while(fromstart!=NULL){
    if(fromstart->object==k){
      if(b){
        ptr->object = k;
      }
      else
        ptr->next = new listOfObjects<int>(k);
      break;
    }
    fromstart = fromstart->next;
  }
  return;
}

void removehead(listOfObjects<int>* &quee){
  quee = quee->next;
}

void doBFS(int start, listOfObjects<int> * JCfromsource[DICT_SIZE], StationAdjacencyList adjacency[512]){
  listOfObjects<int> *quee = new listOfObjects<int>(start);
  while(quee!=NULL){
    int ind = quee->object;
    //StationAdjacencyList curradjList = adjacency[ind];
    if(adjacency[ind].toStations==NULL || JCfromsource[ind]->object==-1 && ind!=start){
      return;
    }
    if(JCfromsource[ind]->object==-1){
      listOfObjects<StationConnectionInfo *> *adjstn = adjacency[ind].toStations;
      while(adjstn!=NULL){
        int adjstnInd = adjstn->object->adjacentStnIndex;
        listOfObjects<TrainInfoPerStation *> *adjstnCnnList = adjstn->object->trains;
        while(adjstnCnnList!=NULL){
          add(JCfromsource[adjstnInd], adjstnCnnList->object->journeyCode);
          adjstnCnnList = adjstnCnnList->next;
        }
        add(quee,adjstnInd);
        adjstn = adjstn->next;
      }
    }
    else{
      listOfObjects<StationConnectionInfo *> *adjstn = adjacency[ind].toStations;
      while(adjstn!=NULL){
        int adjstnInd = adjstn->object->adjacentStnIndex;
        listOfObjects<TrainInfoPerStation *> *adjstnCnnList = adjstn->object->trains;
        while(adjstnCnnList!=NULL){
          addifpresent(JCfromsource[adjstnInd], adjstnCnnList->object->journeyCode, JCfromsource[ind]);
          adjstnCnnList = adjstnCnnList->next;
        }
        add(quee,adjstnInd);
        adjstn = adjstn->next;
      }
    }
    removehead(quee);
  }  

}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here

  int start = (stnNameToIndex.get(srcStnName))->value;
  int dest = (stnNameToIndex.get(destStnName))->value;

  listOfObjects<int> *JCfromsource[DICT_SIZE];
  for(int i=0; i<DICT_SIZE; i++){
    JCfromsource[i] = new listOfObjects<int>(-1);
  }

  doBFS(start,JCfromsource,adjacency);
  listOfObjects<int>* jcodes = JCfromsource[dest];
  if(jcodes->object==-1){
    cout << "No direct journeys available" << endl;
  }
  else{
    listOfObjects<TrainInfoPerStation *> *Info = stationInfo[start];
    listOfObjects<TrainInfoPerStation *> *js;
    TrainInfoPerStation t(0,0,0,0);
    js = new listOfObjects<TrainInfoPerStation *>(&t); 
    while(jcodes!=NULL){
      int code = jcodes->object;
      while(true){
        if(Info==NULL){
          break;
        }
        if(Info->object->journeyCode){
          js->next = Info;
          js = js->next;
        }
        Info = Info->next;
      }
      jcodes = jcodes->next;
    }
    printStationInfo(js);
    cout << adjacency[start].toStations->object->adjacentStnIndex <<" rootend " <<  endl;
  }

  return;
}

/*#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
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

#endif*/

