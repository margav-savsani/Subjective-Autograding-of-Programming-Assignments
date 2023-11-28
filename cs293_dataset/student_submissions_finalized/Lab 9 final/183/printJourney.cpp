#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
bool verify(int j_c,int s_i,StationAdjacencyList adjacency[],int d_i){
    if(s_i==-1){return false;}     //if end station is reached but not went through destinantion then return false
    if(s_i==d_i){return true;}    //if destination station is reached return true
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

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{ 
  int s_i=stnNameToIndex.get(srcStnName)->value;   //obtaining station index
  int d_i=stnNameToIndex.get(destStnName)->value;  //obtaining destination index
  TrainInfoPerStation *t=new TrainInfoPerStation(0,0,0,0);//dummy
  listOfObjects<TrainInfoPerStation *> *req=new listOfObjects<TrainInfoPerStation *>(t);//to store req stations and journeys
  listOfObjects<StationConnectionInfo *> *s2=adjacency[s_i].toStations;//StationConnectionInfo's from source station
  while(s2!=nullptr){                                                  //go through all StationConnectionInfo's  
      listOfObjects<TrainInfoPerStation *> *j=s2->object->trains;      //trains in corresponing StationConnectionInfo's
      while(j!=nullptr){                                               //go through all trains 
        int j_c=j->object->journeyCode;                                
        if(verify(j_c,s2->object->adjacentStnIndex,adjacency,d_i)){    //checking if train goes till destination or not
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
        j=j->next; //go to next train
      }
    s2=s2->next;  //go to next StationConnectionInfo
  }
  if(req->next==NULL){cout<<"No direct journeys available"<<endl;return;} //if nothing is there in req other than dummy then print no jourenys available
  printStationInfo(req->next);            //now print stationinfo for trains in req list
  return;
}

#endif
