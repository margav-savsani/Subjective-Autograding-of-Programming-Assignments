#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
int R;
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
static int c=0;
int a=stnNameToIndex.get(srcStnName)->value;
int b=stnNameToIndex.get(destStnName)->value;
listOfObjects<StationConnectionInfo*>*stations=adjacency[a].toStations;



while (stations!=NULL)
{  listOfObjects<TrainInfoPerStation*>*trains=stations->object->trains;
int index=stations->object->adjacentStnIndex;

  while(trains!=NULL){
    
    listOfObjects<TrainInfoPerStation*>*all_journeys;
 
    //checking wheather waiting time in given range
     bool time=false;
     if(trains->object->depTime>trains->object->arrTime&&(trains->object->depTime-trains->object->arrTime)<=maxTransitTime){
       time=true;
     }
     else if(trains->object->depTime<trains->object->arrTime&&(2400-trains->object->arrTime+trains->object->depTime)<=maxTransitTime){
      time=true;
      
     }

     //if given station is destination station or not
     
      if(destStnName==stnNameToIndex.getKeyAtIndex(index)&&time){
        
        if(all_journeys==NULL){

        all_journeys=trains;
      
        printStationInfo(all_journeys);
        }
        else{
          all_journeys->next=trains;
          all_journeys=all_journeys->next;
          printStationInfo(all_journeys);
         
        }
      }

      //recursion on trains if given station is not destination station
     else if(time){
      
      if(c==0){
        R=trains->object->journeyCode;
        c++;
        
         printPlanJourneys(stnNameToIndex.getKeyAtIndex(index),destStnName,maxStopOvers,maxTransitTime);
      }
       else if(maxStopOvers>0&&R!=trains->object->journeyCode){
        R=trains->object->journeyCode;
     printPlanJourneys(stnNameToIndex.getKeyAtIndex(index),destStnName,maxStopOvers-1,maxTransitTime);
       }
       else{
         printPlanJourneys(stnNameToIndex.getKeyAtIndex(index),destStnName,maxStopOvers,maxTransitTime);
       }
     }
     trains=trains->next;
  }
  
  stations=stations->next;
 
}
  

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp
  return;
}

#endif
