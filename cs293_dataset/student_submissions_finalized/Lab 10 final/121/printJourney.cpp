#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP
#ifndef PLANNER_H
#include "planner.h"
#endif
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include<vector>
using namespace std;

class Transit{
  public:
  int stnindex;
  int fromJC, toJC;
  int time;
  Transit(int StnIndex, int from, int to, int time){
    this->time = time;
    stnindex = StnIndex;
    fromJC = from;
    toJC = to;
  }
};

class Tour{
  //we should somehow store all the journey in it and the last arrival time as well so that it helps in knowing
  //which trains to consider for the next station
  public:
  int stops;  //no of stops to manage number of stops
  int lastStnIndex; //to continue in the loop
  // StationConnectionInfo* stnConInfo;
  listOfObjects<TrainInfoPerStation*> * tripSoFar; //to print and know the if the next one is a new train or not
  int lastArrTime, dayOfWeek; //to check in the loop if every train which comes is in the range of maxTransitTime
  listOfObjects<Transit*>* transit=nullptr;
  Tour(){
    stops=0;
    // stnConInfo = nullptr;
    tripSoFar=nullptr;
    lastArrTime=0;
    dayOfWeek=-1;
    lastStnIndex=-1;
  }
};

//gives the linked list of common trains of the trains list a and b
listOfObjects<TrainInfoPerStation *> * commonTrains(listOfObjects<TrainInfoPerStation *> *a, listOfObjects<TrainInfoPerStation *> *b){
  //current train of a
  listOfObjects<TrainInfoPerStation *> *curr = a;
  listOfObjects<TrainInfoPerStation *> *common = nullptr;
  listOfObjects<TrainInfoPerStation *> *tailCommon = nullptr;
  while(curr!=nullptr){ //going through every element of a 
    listOfObjects<TrainInfoPerStation *> *currcomp = b;
    while(currcomp != nullptr){  //going through b list for every element of a 
      if(currcomp->object->journeyCode == curr->object->journeyCode){ //found a match for this element of a in b
        if(common == nullptr){ //common list is empty yet
          common = new listOfObjects<TrainInfoPerStation *>(curr->object) ; //create the linked list
          tailCommon = common;
        }
        else{ //linked list is not empty
          tailCommon->next = new listOfObjects<TrainInfoPerStation *>(curr->object); //else just add to the tail
          tailCommon->next->prev = tailCommon;  //and shift the tail
          tailCommon = tailCommon->next;
        }
        //finally this inner while loop can be broken
        break;
      }
      currcomp = currcomp->next;
    }
    curr = curr->next;
  }
  return common;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  maxTransitTime = maxTransitTime*100;
  // cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp
  int srcindex = stnNameToIndex.get(srcStnName)->value;   //index of given source station
  int destIndex = stnNameToIndex.get(destStnName)->value; //index of given destination station
  
  listOfObjects<StationConnectionInfo*> * srcConnected = adjacency[srcindex].toStations;  //stations info connected to source
  listOfObjects<StationConnectionInfo*> * currentCon = srcConnected;    //directly connected station that we are currently searching a path from
  if(srcConnected==nullptr) {
    cout<<"No journeys start from this station"<<endl;
    return;
  }
  //we need a queue for bfs, can be done using a linked list
  listOfObjects<Tour*> * queue = nullptr;  
  listOfObjects<Tour*> *tailqueue = queue;   //tail of the queue for addition of new object
  
  //adding all the tours from station to adjacent stations in linked list
  while(currentCon!=nullptr){ //for every connection
    //for every train of that connection
    listOfObjects<TrainInfoPerStation*> * currtrain = currentCon->object->trains;
    while(currtrain!=nullptr){
      for (int i=0; i<7;i++){  //for every day of the week of that connection
        if(currtrain->object->daysOfWeek[i]){ //if this train runs on this day
          //add this tour to queue
          if(queue==nullptr){ //queue is uninitialised
            queue = new listOfObjects<Tour*> (new Tour());
            queue->object->dayOfWeek=i;
            queue->object->lastArrTime = currtrain->object->arrTime;
            queue->object->lastStnIndex= currentCon->object->adjacentStnIndex;
            queue->object->stops=0;
            queue->object->tripSoFar = new listOfObjects<TrainInfoPerStation*> (currtrain->object);
            tailqueue = queue;
          }
          else{ // queue is initialised
            tailqueue->next = new listOfObjects<Tour*> (new Tour());
            tailqueue->next->object->dayOfWeek=i;
            tailqueue->next->object->lastArrTime = currtrain->object->arrTime;
            tailqueue->next->object->lastStnIndex= currentCon->object->adjacentStnIndex;
            tailqueue->next->object->stops=0;
            tailqueue->next->object->tripSoFar = new listOfObjects<TrainInfoPerStation*> (currtrain->object); 
            tailqueue->next->prev = tailqueue;
            tailqueue = tailqueue->next;
          }
        }
      }
      currtrain = currtrain->next;
    }
    currentCon = currentCon->next;
  }

  listOfObjects<Tour*>* availableTour = nullptr;
  listOfObjects<Tour*>* tailAvlTour = nullptr;
  while(queue!=nullptr){ //if there are elements in the queue
    Tour* currTour = queue->object;
    int currStnIndex = currTour->lastStnIndex;
    //if the current station of tour is final destination
    if(currTour->lastStnIndex == destIndex ){
      //add this tour to available tours
      if(availableTour==nullptr){
        availableTour = new listOfObjects<Tour*> (currTour);
        tailAvlTour = availableTour;
      }
      else{
        tailAvlTour->next = new listOfObjects<Tour*> (currTour);
        tailAvlTour->next->prev = tailAvlTour;
        tailAvlTour=tailAvlTour->next;
      }
      queue = queue->next;
      // delete queue->prev;
      continue;
    }
    listOfObjects<StationConnectionInfo*> * outStations = adjacency[currStnIndex].toStations;
    listOfObjects<StationConnectionInfo*> * currOutStn = outStations;
    while(currOutStn!=nullptr){ //for every station reachable from current station
      listOfObjects<TrainInfoPerStation*> *currtrain = currOutStn->object->trains;
      while(currtrain!=nullptr){ //for every train between these two stations
        for (int i=0; i<7; i++){ //for every day this train is available on
          if(currtrain->object->daysOfWeek[i]){ //If this train runs on given day of the week
            //calculating the transit time
            int transitTime = 0;
            transitTime += 2400* ((i - currTour->dayOfWeek)%7);
            transitTime += currtrain->object->depTime - currTour->lastArrTime;
            if(transitTime <0) { //which means same day but earlier than arrival, which is 
                                  //equivalent to next week
              transitTime = 2400*7 + transitTime ;
            }
            if(transitTime < maxTransitTime){ //if this train is feasible
              listOfObjects<TrainInfoPerStation*>* lastTrip = currTour->tripSoFar;
              while(lastTrip->next!=nullptr){
                lastTrip= lastTrip->next;
              }
              if(currTour->stops +1 <= maxStopOvers){  //if addition of another stop is feasible, transit case
                tailqueue->next = new listOfObjects<Tour*> (new Tour());
                tailqueue->next->object->dayOfWeek=i;
                tailqueue->next->object->lastArrTime = currtrain->object->arrTime;
                tailqueue->next->object->lastStnIndex= currOutStn->object->adjacentStnIndex;
                tailqueue->next->object->stops=currTour->stops+1;
                tailqueue->next->object->tripSoFar = currTour->tripSoFar;
                //adding the next tripsofar                
                lastTrip->next= new listOfObjects<TrainInfoPerStation*> (currtrain->object);
                //adding transit
                if(tailqueue->next->object->transit==nullptr){
                 tailqueue->next->object->transit = new listOfObjects<Transit*> (new Transit(currOutStn->object->adjacentStnIndex, lastTrip->object->journeyCode, currtrain->object->journeyCode, transitTime));
                }
                else{
                  listOfObjects<Transit*>* currtransit = tailqueue->next->object->transit;
                  while(currtransit->next!=nullptr){
                    currtransit=currtransit->next;
                  }
                  currtransit->next = new listOfObjects<Transit*> (new Transit(currOutStn->object->adjacentStnIndex, lastTrip->object->journeyCode, currtrain->object->journeyCode, transitTime));
                }
                tailqueue->next->prev = tailqueue;
                tailqueue = tailqueue->next;
              }
              else if ((lastTrip->object->journeyCode == currtrain->object->journeyCode) && (i == currTour->dayOfWeek)){ //no need of change in no of stops
                tailqueue->next = new listOfObjects<Tour*> (new Tour());
                tailqueue->next->object->dayOfWeek=i;
                tailqueue->next->object->lastArrTime = currtrain->object->arrTime;
                tailqueue->next->object->lastStnIndex= currOutStn->object->adjacentStnIndex;
                tailqueue->next->object->stops=currTour->stops;
                tailqueue->next->object->tripSoFar = currTour->tripSoFar;
                //adding the next tripsofar                
                lastTrip->next= new listOfObjects<TrainInfoPerStation*> (currtrain->object);
                tailqueue->next->prev = tailqueue;
                tailqueue = tailqueue->next;
              }
            }
          }
        }
        currtrain = currtrain->next;
      }
      currOutStn = currOutStn->next;
    }
    queue = queue->next;
    // delete queue->prev;
  }

  //now available tours is ready, printing it
  listOfObjects<Tour*> * currTour= availableTour;
  //for every tour available
  while(currTour!=nullptr){
    vector <listOfObjects<TrainInfoPerStation*>*> trains ;
    trains.push_back(currTour->object->tripSoFar);
    listOfObjects<TrainInfoPerStation*> * currtrain = currTour->object->tripSoFar;
    while(currtrain!=nullptr){
      if(currtrain->object->journeyCode != trains[trains.size()-1]->object->journeyCode){
        trains.push_back(currtrain);
      }
      currtrain=currtrain->next;
    }
    //now that the vector is ready
    cout<<"Journey Starts ------------------"<<endl;
    printStationInfo(trains[0]);
    listOfObjects<Transit*>* currtransit = currTour->object->transit;
    for (int i =1; i<trains.size() && currtransit!=nullptr; i++){
      cout<<"Change train on station "<<stnNameToIndex.getKeyAtIndex(currtransit->object->stnindex)<<" from Journey code "<<currtransit->object->fromJC<< " to Journey code "<<currtransit->object->toJC<<". \nTransit time is : "<<currtransit->object->time<<endl;
      printStationInfo(trains[i]);
      currtransit = currtransit->next;
    }
    cout<<"Journey Ends --------------------"<<endl;
    currTour=currTour->next;
  }
  if(availableTour==nullptr){
  cout<<"No available tours for between these stations"<<endl;

  }
  return;
}

#endif
