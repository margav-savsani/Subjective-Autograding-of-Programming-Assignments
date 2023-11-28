#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <queue>

using namespace std;

class layover{
  public:
  string stn_name;
  TrainInfoPerStation *train1;
  TrainInfoPerStation *train2;
  layover(string sname, TrainInfoPerStation *t1, TrainInfoPerStation *t2){
    train1 = t1;
    train2 = t2;
    stn_name = sname;
  }
  void show(){
    string day[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    int date1, date2;
    for(int i=0;i<7;i++){
      if(train1->daysOfWeek[i] == true) date1=i;
      if(train2->daysOfWeek[i] == true) date2=i;
    }
    cout<<"Layover at "<<stn_name<<" from "<<day[date1]<<" "<<train1->depTime<<" till "<<day[date2]<<" "<<train1->arrTime
        <<" change from train "<<train1->journeyCode<<" to new train "<<train2->journeyCode<<endl;
  }
  ~layover(){}
};

class myJourneyObject{
  public:
  int stops;
  vector<layover> layovers;
  TrainInfoPerStation *currTrain;
  int currDay;
  int currStation;
  int nextStation;
  TrainInfoPerStation *startTrain;
  myJourneyObject(TrainInfoPerStation *cTrain, int cDay, int cStation, int nStation){
    stops=0;
    currTrain=cTrain;
    currDay=cDay;
    currStation=cStation;
    nextStation=nStation;
  }
};
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  int idx_src = stnNameToIndex.get(srcStnName)->value; // getting the index of both stations
  int idx_dest = stnNameToIndex.get(destStnName)->value;

  listOfObjects<TrainInfoPerStation *> *journey; // will store all valid journeys
  listOfObjects<StationConnectionInfo *> *currStation = adjacency[idx_src].toStations; // stores current train being processed
  
  queue<myJourneyObject> q;
  while(currStation != nullptr){
    int nextStation = currStation->object->adjacentStnIndex;
    listOfObjects<TrainInfoPerStation *> *currTrain = currStation->object->trains;
    while(currTrain != nullptr){
      for(int i=0; i<7; i++){
        if(currTrain->object->daysOfWeek[i]){
          myJourneyObject newObj(currTrain->object,i,idx_src,nextStation);
          newObj.startTrain = currTrain->object;
          q.push(newObj);
        }
      }
      currTrain=currTrain->next;
    }
    currStation=currStation->next;
  }
  while(!q.empty()){
    myJourneyObject currObject=q.front();
    if(currObject.nextStation == idx_dest){
      cout<<"Found one:"<<endl;
      listOfObjects<TrainInfoPerStation *> *journey;
      journey->object=currObject.startTrain;
      listOfObjects<TrainInfoPerStation *> *currJourneyNode=journey;
      for(int i=0;i<currObject.stops;i++){
        currJourneyNode->next=new listOfObjects<TrainInfoPerStation *>(currObject.layovers[i].train2);
        currJourneyNode->next->prev=currJourneyNode;
        currJourneyNode=currJourneyNode->next;
      }
      currJourneyNode->next=new listOfObjects<TrainInfoPerStation *>(currObject.currTrain);
      currJourneyNode->next->prev=currJourneyNode;
      currJourneyNode=currJourneyNode->next;
      printStationInfo(journey);
      for(int i=0;i<currObject.stops;i++){
        currObject.layovers[i].show();
      }
    }
    else{
      currStation = adjacency[currObject.nextStation].toStations;
      while(currStation != nullptr){
        int nextStation = currStation->object->adjacentStnIndex;
        listOfObjects<TrainInfoPerStation *> *currTrain = currStation->object->trains;
        while(currTrain != nullptr){
          for(int i=0; i<7; i++){
            if(currTrain->object->daysOfWeek[i]){
              myJourneyObject newObj(currTrain->object,i,idx_src,nextStation);
              bool valid=true;
              if(currTrain->object->journeyCode != currObject.currTrain->journeyCode){
                if(currObject.stops+1>maxStopOvers) valid=false;
                int layovertime = ((i - currObject.currDay)%7)*2400 + currTrain->object->arrTime - currObject.currTrain->depTime;
                if(layovertime>maxTransitTime) valid=false;
                else{
                  newObj.stops++;
                  layover newLayover = layover(stnNameToIndex.getKeyAtIndex(currObject.currStation),currObject.currTrain,currTrain->object);
                  newObj.layovers.push_back(newLayover);
                }
              }
              q.push(newObj);
            }
          }
          currTrain=currTrain->next;
        }
        currStation=currStation->next;
      }
    }
    q.pop();
  }
  return;
}

#endif
