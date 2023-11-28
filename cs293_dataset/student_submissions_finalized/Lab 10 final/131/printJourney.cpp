#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
void  DFS( listOfObjects<StationConnectionInfo *> * toList, StationConnectionInfo * parent  ,StationAdjacencyList * adjacency ,int maxStopOvers, int maxTransitTime, listOfObjects<TrainInfoPerStation *> *stationInfo[DICT_SIZE],listOfObjects<TrainInfoPerStation *> *changetrain, int day ,Dictionary<int> stnNameToIndex);

int predday[1000]= {0}; // to store day of arrival of the preceeding station
int predjc[1000]= {0}; //  to store train code of train arriving at the preceeding station
int transit[1000]= {0};// to store transit time(non zero only for stop overs) of the preceeding station
int ongoing_journey;
int change =0; //store how many times trains are changed

StationConnectionInfo ** pred = new StationConnectionInfo* [1000] ; // to store predessors/parent encountered in DFS
bool visited[1000]={false}; // array storing if station is visited
 int  deststnIndex; // global declarations to access in DFS function
 string srcstnname;

  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{ srcstnname =srcStnName;

   Entry <int>* stnEntry = stnNameToIndex.get(srcStnName);  //get the entry corresponding to string in dictionary
  int stnIndex = stnEntry->value; // get dict index of source station
 
  Entry <int>*deststnEntry = stnNameToIndex.get(destStnName);  //get the entry corresponding to string in dictionary
  deststnIndex = deststnEntry->value; // get dict index of dest station
  
  listOfObjects<StationConnectionInfo *> *toList = adjacency[stnIndex].toStations; // base case
  if (toList==nullptr) 
  { cout<<"NO DIRECT JOURNEYS"; // if the source station has no outgoing routes
    return ;                      
  }
  StationConnectionInfo * parent = nullptr; // source is a null parent ;

   listOfObjects<TrainInfoPerStation *> *source = stationInfo[stnIndex];
   while(source!= nullptr){  // looped over all the possible train codes a person can board a train from the source station 
    ongoing_journey = source->object->journeyCode;
    int day;
    for(int i=0;i<7;i++){
        if(source->object->daysOfWeek[i]==1){ // looped over all the possible days a person can start from the source station
          day =i;
    
          DFS(toList , parent ,adjacency , maxStopOvers, maxTransitTime ,stationInfo, source, day, stnNameToIndex);
          change =0;                   // reinitialise all variables 
          memset(visited, false, 1000);// to be ready for the next loop  starting from the source station
          memset(predday, 0, 1000);     
          memset(predjc, 0, 1000);
          memset(transit, 0, 1000);
          ongoing_journey = source->object->journeyCode;
          parent = nullptr;}
   }
   source=source->next;}
  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp
  return;
}


void  DFS( listOfObjects<StationConnectionInfo *> * toList, StationConnectionInfo * parent  ,StationAdjacencyList * adjacency , int maxStopOvers ,int maxTransitTime ,listOfObjects<TrainInfoPerStation *> *stationInfo[DICT_SIZE],listOfObjects<TrainInfoPerStation *> *changetrain,int day,Dictionary<int> stnNameToIndex ){
  
  while(toList!=nullptr ){
  bool increment = false; // to check if change of train happened 
  bool found= false; // to check if we have found the destination station
  bool crossed_limit = false; // to check if we have crossed the bounds of maxstopovers and maxtransittime
  int redo = ongoing_journey; // reset the values after checking each entry in adjacency list
  int redo2 = day;
  if (toList->object->adjacentStnIndex == deststnIndex){ // we have found the dest station
    found =true ; 
    visited [toList->object->adjacentStnIndex]= false; // to include the possibility to encountring 
                                                       //the dest station on a different route
  }
 
  if (!visited[toList->object->adjacentStnIndex])  // check if station not already visited
          {   visited[toList->object->adjacentStnIndex] = true;   // change value of visited to true
       
              pred[toList->object->adjacentStnIndex]= parent;  // update the predecessor value of the station
              predday[toList->object->adjacentStnIndex] = day; // of the previous station , previous day and 
              predjc[toList->object->adjacentStnIndex]=ongoing_journey; // the previous train code
            
              listOfObjects<TrainInfoPerStation *> *train2 = toList->object->trains;
              listOfObjects<TrainInfoPerStation *> *train3=stationInfo[toList->object->adjacentStnIndex];
              bool same= false ;   // indication whether we are on board on the same train or not 

              while(train2!= nullptr){
                    if (ongoing_journey == train2->object->journeyCode){
                        same = true ;  // indicating we have got a common jouney code 
                        while(train3!= nullptr){
                          if (train3->object->journeyCode == ongoing_journey){
                            break;
                          }
                          train3 = train3->next; // train info with the same train code as predecessor
                        }
                        if (train3->object->arrTime <changetrain->object->depTime){
                          day =(day+1)%7; // to find if the day has changed while travelling on the same train
                        }
                        break;}
                    train2=train2->next;
              }
    
              if( same==false) // the train has to be changed
                    { 
                      change ++; // one more change of train happened 
                      increment= true;
                      if (change > maxStopOvers ){ // check condition of max stopovers allowed 
                          found = false;  // reset values because 
                          crossed_limit = true; // we do not have to print this journey
                      }
                     
                      train2 = stationInfo[toList->object->adjacentStnIndex];  // linked list of the trains through that station
                      if (pred[toList->object->adjacentStnIndex]==nullptr){ // case when parent is a nullptr
                        return;
                      }
                      listOfObjects<TrainInfoPerStation *> *train1= stationInfo[pred[toList->object->adjacentStnIndex]->adjacentStnIndex];
                      bool journeychange = false;
                      
                      while(train1 != nullptr){  // firstly traverse the dest station and its predecessor 
                          while(train2!=nullptr){//to find common jouney codes
                             
                              if (train1->object->journeyCode == train2->object->journeyCode)
                              {   train3 = train2; // now we find that connects this sation and its predecessor
                                  ongoing_journey = train1->object->journeyCode; // there must be a train other than the arriving train 
                                  bool transitvalid = false; // to check if we have crossed the limit of max transit time or not
                                  for(int i=0;i<7;i++){
                                      if(train1->object->daysOfWeek[i]==1) // check the array of dayOfWeek array
                                          { if(0<((i-day)%7)*2400+ train1->object->depTime -changetrain->object->arrTime && ((i-day)%7)*2400+ train1->object->depTime -changetrain->object->arrTime<maxTransitTime)
                                              { // this array is made to store transit times during change of trains      
                                              transit[pred[toList->object->adjacentStnIndex]->adjacentStnIndex]=((i-day)%7)*2400+ train1->object->depTime -changetrain->object->arrTime;
                                              day = i;  // we have found the earliest train within transit time 
                                              transitvalid = true;
                                              break;}
                                          }
                                  } 
                                  if (transitvalid== false){
                                        found = false; // reset values because
                                        crossed_limit = true; // we do not have to print this journey
                                  }
                                  journeychange =true; //we have changed  or tried changing our train
                                  break;
                              }
                                  train2 = train2->next;
                          }
                      if (journeychange==true ) break;
                      train2=stationInfo[toList->object->adjacentStnIndex];
                      train1 = train1->next;
                    }
                    }
              
              if (found==false && crossed_limit==false ){
                  
                  DFS (adjacency[toList->object->adjacentStnIndex].toStations, toList->object, adjacency, maxStopOvers, maxTransitTime, stationInfo, train3, day, stnNameToIndex);
                 // recursive call
                  }//printing the valid journeyts
               
              if (found == true){cout<<"ARRIVAL DATA PRINTED IN REVERSE ORDER:"<<endl;
              StationConnectionInfo * predecessor = toList->object;
              cout<<"DAY OF THE WEEK: "<<day<<" "<<"TRAIN CODE: "<<ongoing_journey<<" ";
              while(predecessor != nullptr)
              { cout<<"TRANSIT TIME IN HOURS: "<<transit[predecessor->adjacentStnIndex]<<" ";
                cout<<"STATION NAME: "<<stnNameToIndex.getKeyAtIndex(predecessor->adjacentStnIndex)<<endl<<"DAY OF THE WEEK: "<<predday[predecessor->adjacentStnIndex]<<" "<<"TRAIN CODE: "<<predjc[predecessor->adjacentStnIndex]<<" ";
                predecessor= pred[predecessor->adjacentStnIndex];
              }
              cout<<"STATION NAME: "<<srcstnname<<endl;

           }  }
  ongoing_journey = redo;
  day = redo2;
  if(parent!=nullptr)
    transit[parent->adjacentStnIndex]=0;
  if (increment== true)
       change --;
  toList= toList->next;     //if (toList->object->adjacentStnIndex == deststnIndex)
  }
  
  return ;
 }
 
#endif
