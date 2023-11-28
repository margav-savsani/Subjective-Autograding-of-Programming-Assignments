#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <bits/stdc++.h>
using namespace std;

struct trnInfoInJrny{ //struct to store the information on a train in a journey
public:
  TrainInfoPerStation* train;
  int sourceIndex;      //source station info
  int destIndex;        //destination station info
  bool* daysOfWeekToTrack;  //number of days of week the train is valid for the journey

  trnInfoInJrny(TrainInfoPerStation* train, int src, int dest, bool* daysOfWeekToTrack){  //constructor
    this->train = train;
    sourceIndex = src;
    destIndex = dest;
    this->daysOfWeekToTrack = daysOfWeekToTrack;
  }
};

class jrnyInfo{   //contains the whole information about one of the many journeys
public:
  listOfObjects<trnInfoInJrny*>* trainsInJrny;  //list of trains in the journey
  TrainInfoPerStation* lastTrain;               //last train of the journey
  bool invalidJrny;                             //tells if the journey has become invalid after crossing the maximum number of stop overs

  jrnyInfo(TrainInfoPerStation* curr, int src, int dest, bool* trackDaysOfWeek){
    lastTrain = curr;
    trainsInJrny = new listOfObjects(new trnInfoInJrny(curr, src, dest, trackDaysOfWeek));
    invalidJrny = false;
  }
  ~jrnyInfo(){;}

  trnInfoInJrny* getLastTrainInfo(){  //returns the last train info
    listOfObjects<trnInfoInJrny*>* StoreJrny = trainsInJrny;

    while(trainsInJrny->object->train->journeyCode != lastTrain->journeyCode){
      trainsInJrny = trainsInJrny->next;
    }
    trnInfoInJrny* lastTrainInfo = trainsInJrny->object;
    trainsInJrny = StoreJrny;

    return lastTrainInfo;
  }

  void addTrnToJrny(TrainInfoPerStation* train, int src, int dest, int maxStopOvers, bool* trackerDaysOfWeek){
    //adding a new train in a journey

    if(!invalidJrny){
      trnInfoInJrny* newTrainInJrny = new trnInfoInJrny(train, src, dest, trackerDaysOfWeek);
      listOfObjects<trnInfoInJrny*>* StoreJrny = trainsInJrny;
      int stops = 0;
      while(trainsInJrny->next != nullptr){
        stops++;
        trainsInJrny = trainsInJrny->next;
      }
      trainsInJrny->next = new listOfObjects(newTrainInJrny); 
      if(stops > maxStopOvers){
        invalidJrny = true;
      }
      lastTrain = train;
      trainsInJrny = StoreJrny;
    }

  }
  void updateJrny(TrainInfoPerStation* train, int newDest, bool* trackDaysOfWeek){
    //updates the destination of the last train
    //useful for journeys like 1->2->2
    if(!invalidJrny){
      lastTrain = train;
      listOfObjects<trnInfoInJrny*>* StoreJrny = trainsInJrny;
      while(trainsInJrny->next != nullptr){
        trainsInJrny = trainsInJrny->next;
      }
      trainsInJrny->object->destIndex = newDest;
      trainsInJrny->object->daysOfWeekToTrack = trackDaysOfWeek;
      trainsInJrny->object->train = train;

      trainsInJrny = StoreJrny;
    }
  }
};

bool* validJourney(trnInfoInJrny* arrivingTrn, TrainInfoPerStation* leavingTrn, int maxTransitTime){
  //returns an array of each day of the week telling if the leaving train is valid in the journey or not
  bool *validWeekInfo = new bool[7];

  //let us break down the maxTransitTime
  int numberOfDays = maxTransitTime/24;
  int numberOfActHrs = maxTransitTime % 24;

  bool* arrivingTrnWeekTracker = arrivingTrn->daysOfWeekToTrack;
  bool* departingTrnWeekTracker = leavingTrn->daysOfWeek;

  int timeDelay = leavingTrn->depTime - arrivingTrn->train->arrTime;

  for(int i = 0; i < 7; i++){
    if(arrivingTrnWeekTracker[i]){
      for(int j = i; j != (i+numberOfDays)%7; j = (j+1)%7){
        if(departingTrnWeekTracker[j] && leavingTrn->depTime != -1){
          if(timeDelay < 0){
            timeDelay = timeDelay + 24;
          }
          if(timeDelay <= numberOfActHrs){
            validWeekInfo[i] = true;
          }
        }
      }
    }
  }
  
  return validWeekInfo;
}

void printGlobalJrnyList(listOfObjects<jrnyInfo*>* globalJrnyList, Dictionary<int> stnNameToIndex){
  
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

  listOfObjects<jrnyInfo*>* StoreglobalJrnyList = globalJrnyList;
  int journeyCount = 0;
  while(globalJrnyList != nullptr){
    if(!globalJrnyList->object->invalidJrny){ //if the journey is not invalid
      listOfObjects<trnInfoInJrny*>* trainList = globalJrnyList->object->trainsInJrny;
      
      journeyCount++;
      cout<<"Journey "<<journeyCount<<" :\n";
      
      while(trainList != nullptr){
        cout<<"-----------------------------------------------------------------------"<<endl;
        cout<<"Train "<<trainList->object->train->journeyCode<<" from "<<stnNameToIndex.getKeyAtIndex(trainList->object->sourceIndex)<<" to "<<stnNameToIndex.getKeyAtIndex(trainList->object->destIndex)<<endl;
        cout<<"On days: \n";
        for(int i = 0; i < 7; i++){
          if(trainList->object->daysOfWeekToTrack[i]){
            if(trainList->object->train->arrTime != -1 && trainList->object->train->depTime != -1){
              cout<<days[i]<<" Arr: "<<trainList->object->train->arrTime<<"     Dep: "<<trainList->object->train->depTime<<endl;
            }
            else if(trainList->object->train->arrTime == -1 && trainList->object->train->depTime != -1){
              cout<<days[i]<<" Arr: "<<"Starts"<<"     Dep: "<<trainList->object->train->depTime<<endl;
            }
            else if(trainList->object->train->arrTime != -1 && trainList->object->train->depTime == -1){
              cout<<days[i]<<" Arr: "<<trainList->object->train->arrTime<<"     Dep: "<<"Ends"<<endl;
            }
            
          }
        }
        trainList = trainList->next;
      }
    }
    

    globalJrnyList = globalJrnyList->next;
  }
  globalJrnyList = StoreglobalJrnyList;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  int srcStnIndex = stnNameToIndex.get(srcStnName)->value;  //source station name index
  int destStnIndex = stnNameToIndex.get(destStnName)->value;  // destination station name index

  queue<int> qOfstnIndex;   // the main queue of bfs which stores the current station indexes
  qOfstnIndex.push(srcStnIndex);   //adding the source station to the queue
  int* parentStns = new int[DICT_SIZE];   //array for storing the indexes of parent stations of the each station
  
  //need a list of journeys independent of station
  listOfObjects<jrnyInfo*>* globalJrnyList = nullptr;
  listOfObjects<jrnyInfo*>* storeglobalJrnyList;
  //this dictionary stores instances of the global journey list alongside each station
  Dictionary<listOfObjects<jrnyInfo*>*> trInfoStn;
  
  //let us traverse the graph
  bool destFound = false;
  while(!qOfstnIndex.empty()){
    if(qOfstnIndex.front() == destStnIndex){
      destFound = true;
    } 
    listOfObjects<StationConnectionInfo *> *adjStn = adjacency[qOfstnIndex.front()].toStations; //list of adjacent stations

    while(adjStn != nullptr){ //insertion of adjacent stations in the queue
      //leaving the parent station we have to traverse every other adjacent station
      if(parentStns[qOfstnIndex.front()] != adjStn->object->adjacentStnIndex){
        qOfstnIndex.push(adjStn->object->adjacentStnIndex);    //insertion in the queue
        parentStns[adjStn->object->adjacentStnIndex] = qOfstnIndex.front();             //storing the parent

        listOfObjects<TrainInfoPerStation*>* trnsToCurrStn = adjStn->object->trains;
        listOfObjects<TrainInfoPerStation*>* StoretrnsToCurrStn = trnsToCurrStn;
        //lets make the case for neighbours of the source station that is when current station is the source station
        if(parentStns[adjStn->object->adjacentStnIndex] == srcStnIndex){
          //initiate the global journey list by starting all the journeys from source to current adjacent station
          bool firstJrny = true;
          
          while(trnsToCurrStn != nullptr){
            if(firstJrny){
              firstJrny = false;
              globalJrnyList = new listOfObjects(new jrnyInfo(trnsToCurrStn->object, srcStnIndex, adjStn->object->adjacentStnIndex, trnsToCurrStn->object->daysOfWeek));
              storeglobalJrnyList = globalJrnyList;
            }
            else{
              globalJrnyList->next = new listOfObjects(new jrnyInfo(trnsToCurrStn->object, srcStnIndex, adjStn->object->adjacentStnIndex, trnsToCurrStn->object->daysOfWeek));
              globalJrnyList = globalJrnyList->next;
            }
            trnsToCurrStn = trnsToCurrStn->next;
          }
          globalJrnyList = storeglobalJrnyList;
          trnsToCurrStn = StoretrnsToCurrStn;
        }
        else{
          //we compare the departure time of trains in transit from current station to curr adjacent station with the arrival time of the valid trains from parent station to current station
          //so the list of valid trains contains all those trains which (if not in direct journey)
          
          //getting the journey list of parent station journeys
          listOfObjects<jrnyInfo*>* jrnysFrmPStn = trInfoStn.get(stnNameToIndex.getKeyAtIndex(parentStns[adjStn->object->adjacentStnIndex]))->value;

          bool firstJrny = true;  //for creating the new global journey list
          //iterating through the list of journeys of parent station
          while(jrnysFrmPStn != nullptr){
            //now we loop through all trains to the current adjacent station from the current station
            while(trnsToCurrStn != nullptr){
              bool* daysOfWeekTracked = validJourney(jrnysFrmPStn->object->getLastTrainInfo(), trnsToCurrStn->object, maxTransitTime);
              bool validJourneyFound = false;
              for(int i = 0; i < 7; i++){
                if(daysOfWeekTracked[i]){
                  validJourneyFound = true;
                  break;
                }
              }
              if(!jrnysFrmPStn->object->invalidJrny && validJourneyFound){
                if(firstJrny){
                  firstJrny = false;
                  globalJrnyList = new listOfObjects(jrnysFrmPStn->object);
                  if(jrnysFrmPStn->object->lastTrain->journeyCode == trnsToCurrStn->object->journeyCode){
                    globalJrnyList->object->updateJrny(trnsToCurrStn->object, adjStn->object->adjacentStnIndex, daysOfWeekTracked);
                  }
                  else{
                    globalJrnyList->object->addTrnToJrny(trnsToCurrStn->object, parentStns[adjStn->object->adjacentStnIndex],adjStn->object->adjacentStnIndex, maxStopOvers, daysOfWeekTracked);
                  }
                  storeglobalJrnyList = globalJrnyList;
                }
                else{
                  globalJrnyList->next = new listOfObjects(jrnysFrmPStn->object);
                  globalJrnyList = globalJrnyList->next;
                  if(jrnysFrmPStn->object->lastTrain->journeyCode == trnsToCurrStn->object->journeyCode){
                    globalJrnyList->object->updateJrny(trnsToCurrStn->object, adjStn->object->adjacentStnIndex, daysOfWeekTracked);
                  }
                  else{
                    globalJrnyList->object->addTrnToJrny(trnsToCurrStn->object, parentStns[adjStn->object->adjacentStnIndex],adjStn->object->adjacentStnIndex, maxStopOvers, daysOfWeekTracked);
                  }
                }
              }

            trnsToCurrStn = trnsToCurrStn->next;
            }

            jrnysFrmPStn = jrnysFrmPStn->next;
            trnsToCurrStn = StoretrnsToCurrStn;
          }

        }
        globalJrnyList = storeglobalJrnyList;

        //now we have the new instance of the global journey list
        // let us store it in the dictionary associated with the station in consideration
        Entry<listOfObjects<jrnyInfo*>*> jrnyInfoAtStn(globalJrnyList);
        jrnyInfoAtStn.key = stnNameToIndex.getKeyAtIndex(adjStn->object->adjacentStnIndex);
        trInfoStn.put(jrnyInfoAtStn);

      }
      
      adjStn = adjStn->next;

    }
    
    qOfstnIndex.pop();    //deleting the first element from the queue
  }
  if(destFound){
    printGlobalJrnyList(trInfoStn.get(destStnName)->value, stnNameToIndex);
  }
  else{
    cout<<"Sorry! No journeys available!\n";
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
