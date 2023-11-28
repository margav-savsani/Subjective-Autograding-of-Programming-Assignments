#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

int* find(StationAdjacencyList *adjacency, int start, int last, int jcode, int stopover, int transitTime,int days)
{
  int c[2];
  c[0]=-1; //to check journey is possible or not
  c[1]=-1; //to check current number of stop overs left 
  listOfObjects<StationConnectionInfo *> *toStations = adjacency[start].toStations; //to stations from starting station
  listOfObjects<TrainInfoPerStation *> *trains; //trains to each destination station
  int arrvtimeprev;
  if (start==last) {c[0]=0; return c;}
  while (toStations != nullptr)
  {
    trains = toStations->object->trains;
    while (trains != nullptr)
    {
      if (trains->object->journeyCode == jcode)
      {
        if ( find(adjacency, toStations->object->adjacentStnIndex, last, jcode, stopover, transitTime,days)[0]==0 && trains->object->daysOfWeek[days]  )
        c[0]=0;
        arrvtimeprev=trains->object->arrTime;
      }
      else if (trains->object->journeyCode != jcode)
      {
        if ( find(adjacency, toStations->object->adjacentStnIndex, last, trains->object->journeyCode, stopover-1, transitTime,days)[0]==0 && trains->object->daysOfWeek[days] )
        { 
        int depTimenext=trains->object->depTime;
        if (depTimenext-arrvtimeprev< transitTime){
          c[0]=0;
          c[1]=stopover-1;
          cout << trains->object->journeyCode << " stopover:" << stopover <<" arrtime:"<<trains->object->arrTime<<" deptime:"<<trains->object->depTime<<endl;
        }
        }
      }
      trains = trains->next;
    }
    toStations = toStations->next;
  }
  return c;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
  int start = stnNameToIndex.get(srcStnName)->value; //srcstn index
  int final = stnNameToIndex.get(destStnName)->value; //destinstn index
  bool check = false;
  int numberofstops=0;
  for (int day =0;day<7;day++){
    while(numberofstops<maxStopOvers){
      listOfObjects<StationConnectionInfo *> *toStations = adjacency[start].toStations;
      listOfObjects<TrainInfoPerStation *> *trains = toStations->object->trains;
      while (toStations != nullptr){
        while (trains != nullptr){
         int currindex=toStations->object->adjacentStnIndex;
         if (currindex==final){check=true;printStationInfo(trains);break;}
         
         else if (find(adjacency,currindex ,final, trains->object->journeyCode, numberofstops, maxTransitTime,day)[0]==0 && trains->object->daysOfWeek[day]) {
            check = true;
            numberofstops=find(adjacency,currindex ,final, trains->object->journeyCode, numberofstops, maxTransitTime,day)[1];
            printStationInfo(trains);
            break;
         }
         trains = trains->next;
        }
        toStations = toStations->next;
        trains = toStations->object->trains;
      }
    }
  }
 if (check == false) cout << "No direct journeys in this route" << endl;
 return;
}

#endif
