#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
bool direct(int stni, int desti, StationAdjacencyList adjacency[],int jcode,listOfObjects < TrainInfoPerStation * > *t,listOfObjects<listOfObjects < TrainInfoPerStation * > *> * f,int stops,int max) {
  bool t1=false;
  if(stops>max+1){return false;}
  if(stni==desti) {
    listOfObjects<listOfObjects < TrainInfoPerStation * > *> *x=f;
    while(x->next!=nullptr){
      x=x->next;
    }
    listOfObjects<listOfObjects < TrainInfoPerStation * > *> * p = new listOfObjects<listOfObjects < TrainInfoPerStation * > *>(t);
    x->next=p;
    return true;
    }
  if (stni == -1) {
    return false; 
  }
  else{ 
  int jcode2;
  listOfObjects < StationConnectionInfo * > * adjsta = adjacency[stni].toStations; //to stations of stations with stni index
  while (adjsta != nullptr) {
    int stni1 = adjsta -> object -> adjacentStnIndex;
    listOfObjects < TrainInfoPerStation * > * train = adjsta -> object -> trains;  //list of trains of tostation
    while (train != nullptr) {
      int s=stops;
      if(jcode!=train->object->journeyCode){
        stops++;}
      TrainInfoPerStation *T=new TrainInfoPerStation(0, 0, 0, 0);
      listOfObjects < TrainInfoPerStation * > *t10=new listOfObjects < TrainInfoPerStation * >(T); //copy of t
      listOfObjects < TrainInfoPerStation *> *t9;
      listOfObjects < TrainInfoPerStation *> *t7=t;
      while(t7!=nullptr){
        listOfObjects < TrainInfoPerStation *> *t11=t10;
        while(t11->next!=NULL){
          t11=t11->next;
        }
        t11->next=new listOfObjects < TrainInfoPerStation * >(t7->object);
        t9=t11->next;
        t7=t7->next;
      }
      listOfObjects < TrainInfoPerStation * > *y=t;
      while(y->next!=nullptr){
        y=y->next;
      }
      y->next=new listOfObjects < TrainInfoPerStation * > (train -> object);
      
      if(direct(stni1,desti,adjacency,train->object->journeyCode,t,f,stops,max)==true){
         t1=true;
      }
      t=t10;
      if(jcode==0){
      TrainInfoPerStation * z1 = new TrainInfoPerStation(0, 0, 0, 0);
      t=new listOfObjects < TrainInfoPerStation * > (z1);
      }
      train=train->next;
      stops=s;
    }
    adjsta=adjsta->next;
  }
  if(t1==true){ return true;}
  return false;
  }
  
  }
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  int jcode;                                                                         //journey code
  bool gotit = false;                                                                //bool for direct journey codes
  int toindex = stnNameToIndex.get(srcStnName) -> value;                             //source station index value
  int desti = stnNameToIndex.get(destStnName) -> value;                              //destination station index value
  listOfObjects < StationConnectionInfo * > * src_ = adjacency[toindex].toStations; //adjacency list
  TrainInfoPerStation * y = new TrainInfoPerStation(0, 0, 0, 0);                     //traininfoperstation constructor
  listOfObjects < TrainInfoPerStation * > * z = new listOfObjects < TrainInfoPerStation * > (y);
  listOfObjects<listOfObjects < TrainInfoPerStation * > *> * directjour = new listOfObjects<listOfObjects < TrainInfoPerStation * > *>(z);
  TrainInfoPerStation * z1 = new TrainInfoPerStation(0, 0, 0, 0);                     //traininfoperstation constructor
  listOfObjects < TrainInfoPerStation * > * directjour1 = new listOfObjects < TrainInfoPerStation * > (z1);
  direct(toindex,desti,adjacency,0,directjour1,directjour,0,maxStopOvers);           //to find journey with max stop overs
  listOfObjects<listOfObjects < TrainInfoPerStation * > *> * x=directjour->next;
  int i=1;

  while(x!=nullptr){
    gotit=true;
    cout<<"JOURNEY:"<<i<<endl;
    printStationInfo(x->object);                                                       //print all the  journeys
    x=x->next;
    i++;}
  if (!gotit) {
    cout << "No direct journeys available" << endl;
  }
  return;
}

#endif
