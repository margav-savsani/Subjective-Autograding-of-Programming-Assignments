#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
bool verify(int j_c,int s_i,StationAdjacencyList adjacency[],int d_i,int &stops){
    if(s_i==-1){return false;}     //if end station is reached but not went through destinantion then return false
    if(s_i==d_i){return true;}     //if destination station is reached return true
    else{
      listOfObjects<StationConnectionInfo *> *s1=adjacency[s_i].toStations;
      int present=0;
      int p=0;
      while(s1!=nullptr){                 //checking if train with journeycode j_c departures from this station 
                int found=0;              
                listOfObjects<TrainInfoPerStation *> *j=s1->object->trains;  //going through all trains departing from this station
                while(j!=nullptr){
                    if(j->object->journeyCode==j_c){
                    p=s1->object->adjacentStnIndex;
                    stops++;
                    found++;                               //if found
                    break;
                  }
                  else{j=j->next;}
              }
              if(found!=0){present++;break;}
              else{s1=s1->next;}
            }
      if(present!=0){return verify(j_c,p,adjacency,d_i);} //if such train is present in this station continue checking in next station
      else return false;                                  //else stop checking and return false
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
  int stops=0;
  int s_i=stnNameToIndex.get(srcStnName)->value;   //obtaining station index
  int d_i=stnNameToIndex.get(destStnName)->value;  //obtaining destination index
  TrainInfoPerStation *t=new TrainInfoPerStation(0,0,0,0);//dummy
  listOfObjects<TrainInfoPerStation *> *req=new listOfObjects<TrainInfoPerStation *>(t);//to store req stations and journeys
  listOfObjects<StationConnectionInfo *> *s2=adjacency[s_i].toStations;//StationConnectionInfo's from source station
  if(stops<maxStopOvers) stops++;
  while(s2!=nullptr){ 
      int stops_1=stops;                                                //go through all StationConnectionInfo's  
      listOfObjects<TrainInfoPerStation *> *j=s2->object->trains;      //trains in corresponing StationConnectionInfo's
      while(j!=nullptr){                                               //go through all trains 
        int j_c=j->object->journeyCode;                                
        if(verify(j_c,s2->object->adjacentStnIndex,adjacency,d_i,stops1)){    //checking if train goes till destination or not
            if(stops<maxStopOvers){
              listOfObjects<TrainInfoPerStation *> *x=req;               //if yes add train to required list
              while(true){ 
                  if(x->next==nullptr){                                  
                      x->next=new listOfObjects<TrainInfoPerStation *>(j->object);
                      x->next->prev=x;
                      break;
                    }
                  x=x->next;
              }
            }
        }
        j=j->next; //go to next train
      }
    s2=s2->next;  //go to next StationConnectionInfo
  }
  if(req->next==NULL){cout<<"No direct journeys available"<<endl;return;} //if nothing is there in req other than dummy then print no jourenys available
  printStationInfo(req->next);            //now print stationinfo for trains in req list
  return;
  
  return;
}

#endif
