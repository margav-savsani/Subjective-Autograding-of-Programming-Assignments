#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif


#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
// A structure to store info about current journey
struct JourneyStore{
  int startstn,endstn,trainnm;
  JourneyStore(int a, int b, int c){
    startstn = a;
    endstn = b;
    trainnm = c;
  }
  //Next a function to print the info
  void printjrny(Dictionary<int> stnNameToIndex){
    cout<<stnNameToIndex.getKeyAtIndex(startstn)<<" to "<<stnNameToIndex.getKeyAtIndex(endstn)<<" with train "<<trainnm<<endl;
  }
};


void DFS(int stn_index, int trn_index, int& maxStops, int maxTime, int req , listOfObjects<JourneyStore*> *currJourney, StationAdjacencyList adjacency[], Dictionary<int> stnNameToIndex){
  // First check if we have reached required place
  if(stn_index == req){
    cout<<"Start:"<<endl;
    while(currJourney->prev!=NULL){
      currJourney = currJourney->prev;
    }
    while(currJourney->next!=NULL){
      currJourney->next->object->printjrny(stnNameToIndex);
      currJourney = currJourney->next;
    }
    cout<<"End"<<endl;
    cout<<endl;
  }
  else{
    listOfObjects<StationConnectionInfo*>* li = adjacency[stn_index].toStations;
    while(li!=NULL){
      int stn = li->object->adjacentStnIndex;

      //List of trains between these stations 
      listOfObjects<TrainInfoPerStation*>* tli = li->object->trains;
      
      while(tli!=NULL){
        int new_trn_index = tli->object->journeyCode;
        
        

        //We apply DFS on every station train pair and decrement maxStops if required
        if(trn_index != new_trn_index){
          if(maxStops == 0){
            tli = tli->next;
            continue;
          }
          else {
            //We add to the currJourney
            JourneyStore *temp;
            temp = new JourneyStore(stn_index,stn,tli->object->journeyCode);
            currJourney->next = new listOfObjects<JourneyStore*>(temp);
            currJourney->object->endstn = stn_index;
            currJourney->next->prev = currJourney;
            currJourney = currJourney->next;
            maxStops--;
            DFS(stn,tli->object->journeyCode,maxStops,maxTime, req, currJourney, adjacency, stnNameToIndex);
            maxStops++;
            currJourney = currJourney->prev;
          }
        }
        else DFS(stn,tli->object->journeyCode,maxStops,maxTime, req, currJourney, adjacency, stnNameToIndex);
        tli = tli->next;
      }

      li = li->next;
    }

  }

}



void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  listOfObjects<JourneyStore*> *currJourney;
  JourneyStore *u = new JourneyStore(0,0,0);
  currJourney = new listOfObjects<JourneyStore*>(u);
  //To get the index from station names
  int start=stnNameToIndex.get(srcStnName)->value;
  int req=stnNameToIndex.get(destStnName)->value;

  
  //List fo adjacent stations
  listOfObjects<StationConnectionInfo*>* li = adjacency[start].toStations;
  while(li!=NULL){
    int stn = li->object->adjacentStnIndex;

    //List of trains between these stations 
    listOfObjects<TrainInfoPerStation*>* tli = li->object->trains;
    
    while(tli!=NULL){
      JourneyStore *temp;
      temp = new JourneyStore(start,stn,tli->object->journeyCode);
      currJourney->next = new listOfObjects<JourneyStore*>(temp);
      currJourney->next->prev = currJourney;
      currJourney = currJourney->next;
      //We apply DFS on every station train pair 
      DFS(stn,tli->object->journeyCode,maxStopOvers,maxTransitTime, req, currJourney, adjacency, stnNameToIndex);
      currJourney = currJourney->prev;
      tli = tli->next;
    }

    li = li->next;
  }
  // insert your code here
  
  //cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  return;
}

#endif
