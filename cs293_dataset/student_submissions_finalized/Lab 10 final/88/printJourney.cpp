#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class layover{
  public:
  string stn_name; // station involving layover
  int day1, day2, t1, t2, jc1, jc2;
  layover(string sname, int d1, int d2, int time1, int time2, int journeycode1, int journeycode2){
    day1 = d1;
    day2 = d2;
    stn_name = sname;
    t1 = time1;
    t2 = time2;
    jc1 = journeycode1;
    jc2 = journeycode2;
  }
  void show(){
    string day[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    cout<<GREEN<<"Layover"<<RESET<<" at "<<BLUE<<stn_name<<RESET<<" from "<<day[day1]<<" "<<t1<<" till "<<day[day2]<<" "<<t2
        <<"."<<endl<<"Change from train "<<jc1<<" to new train "<<jc2<<endl;
  }
  ~layover(){}
};

class myJourneyObject{
  public:
  int stops;
  listOfObjects<layover *> *layovers;
  TrainInfoPerStation *currTrain;
  int currDay;
  int currStation;
  int nextStation;
  TrainInfoPerStation *startTrain;
  int startDay;
  myJourneyObject(TrainInfoPerStation *cTrain, int cDay, int cStation, int nStation){
    stops=0;
    currTrain=cTrain;
    currDay=cDay;
    currStation=cStation;
    nextStation=nStation;
    layovers=nullptr;
  }
};

void myPrintStationInfo(TrainInfoPerStation *currInfo, int currDay)
{
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  TrainInfoPerStation *newExpandedElement = new TrainInfoPerStation(currInfo->journeyCode, currInfo->stopSeq, currInfo->arrTime,currInfo->depTime);
  newExpandedElement->setDayOfWeek(currDay);
  currInfo = newExpandedElement;
  if (currInfo != nullptr) {
    cout << GREEN << "Day(s): " << RESET;
    for (int i=0; i<7; i++) {
	if (currInfo->daysOfWeek[i]) cout << days[i] << " ";
      }
      cout << endl;
      cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << "\t";
      cout << RED << "Arr: " << RESET;
      if (currInfo->arrTime == -1) {
	cout << "Starts";
      }
      else {
	cout << currInfo->arrTime;
      }
      cout << RED << " Dep: " << RESET;
      if (currInfo->depTime == -1) {
	cout << "Ends";
      }
      else {
	cout << currInfo->depTime;
      }
      cout << endl;
    }
}
  
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

  listOfObjects<StationConnectionInfo *> *currStation = adjacency[idx_src].toStations; // stores current train being processed
  
  listOfObjects<myJourneyObject *> *q = nullptr;
  listOfObjects<myJourneyObject *> *curr_q_index, *last_q_index;

  int num_results=0;
  while(currStation != nullptr){
    int nextStation = currStation->object->adjacentStnIndex;
    listOfObjects<TrainInfoPerStation *> *currTrain = currStation->object->trains;
    while(currTrain != nullptr){
      
      for(int i=0; i<7; i++){
        if(currTrain->object->daysOfWeek[i]){
          myJourneyObject *newObj = new myJourneyObject(currTrain->object,i,idx_src,nextStation);
          newObj->startTrain = currTrain->object;
          newObj->startDay = i;
          if(q == nullptr){
            q = new listOfObjects<myJourneyObject *>(newObj);
            curr_q_index = q;
          }
          else{
            // cout<<(q==curr_q_index)<<" "<<(curr_q_index == nullptr)<<endl;
            curr_q_index->next = new listOfObjects<myJourneyObject *>(newObj);
            curr_q_index = curr_q_index->next;
            last_q_index=curr_q_index;
          }
        }
      }
      currTrain=currTrain->next;
    }
    currStation=currStation->next;
  }
  
  curr_q_index = q;
  while(curr_q_index != nullptr){
    // myPrintStationInfo(curr_q_index->object->currTrain,curr_q_index->object->currDay);

    listOfObjects<TrainInfoPerStation *> *currTrain = stationInfo[curr_q_index->object->nextStation];
    int arrTime;
    listOfObjects<StationConnectionInfo *> *prevStation = adjacency[curr_q_index->object->nextStation].fromStations;
    //cout<<prevStation->object->adjacentStnIndex<<" "<<curr_q_index->object->currStation<<endl;
    //cout<<stnNameToIndex.getKeyAtIndex(prevStation->object->adjacentStnIndex)<<" "<<stnNameToIndex.getKeyAtIndex(curr_q_index->object->currStation)<<endl;
    while(prevStation->object->adjacentStnIndex != curr_q_index->object->currStation){
      //cout<<stnNameToIndex.getKeyAtIndex(prevStation->object->adjacentStnIndex)<<" "<<stnNameToIndex.getKeyAtIndex(curr_q_index->object->currStation)<<endl;
      prevStation = prevStation->next;
      //cout<<prevStation->object->adjacentStnIndex<<endl;
    }
    currTrain = prevStation->object->trains;
    while(currTrain->object->journeyCode != curr_q_index->object->currTrain->journeyCode){
      currTrain = currTrain->next;
    }
    arrTime = currTrain->object->arrTime;
    if(arrTime<curr_q_index->object->currTrain->depTime){
      curr_q_index->object->currDay = (curr_q_index->object->currDay+1)%7;
    }
    if(curr_q_index->object->nextStation == idx_dest){ // found destination
      num_results++;
      cout<<"Found a journey with "<<RED<<curr_q_index->object->stops<<RESET<<" layovers:"<<endl;
      cout<<"Departure:"<<endl;
      myPrintStationInfo(curr_q_index->object->startTrain,curr_q_index->object->startDay);
      if(curr_q_index->object->stops>0){
        listOfObjects<layover *> *currNode = curr_q_index->object->layovers;
        for(int li=0;li<curr_q_index->object->stops;li++){
          currNode->object->show();
          currNode = currNode->next;
        }
      }
      cout<<"Arrival:"<<endl;
      prevStation = adjacency[curr_q_index->object->nextStation].fromStations;
      while(prevStation->object->adjacentStnIndex != curr_q_index->object->currStation){
        prevStation = prevStation->next;
      }
      currTrain = prevStation->object->trains;
      while(currTrain->object->journeyCode != curr_q_index->object->currTrain->journeyCode){
        currTrain = currTrain->next;
      }
      myPrintStationInfo(currTrain->object,curr_q_index->object->currDay);
      cout<<endl;
    }
    else{ // looking for connecting trains
      currStation = adjacency[curr_q_index->object->nextStation].toStations;
      while(currStation != nullptr){
        currTrain = currStation->object->trains;
        while(currTrain != nullptr){
          if(currTrain->object->journeyCode == curr_q_index->object->currTrain->journeyCode){
            myJourneyObject *newObj=new myJourneyObject(*curr_q_index->object);
            //cout<<arrTime<<" "<<curr_q_index->object->currTrain->depTime<<endl;
            if(arrTime<curr_q_index->object->currTrain->depTime){
              newObj->currDay = (curr_q_index->object->currDay+1)%7;
            }
            newObj->currStation = curr_q_index->object->nextStation;
            newObj->currTrain = currTrain->object;
            newObj->nextStation = currStation->object->adjacentStnIndex;
            last_q_index->next = new listOfObjects<myJourneyObject *>(newObj);
            last_q_index = last_q_index->next;
            // myPrintStationInfo(newObj->currTrain, newObj->currDay);
            // cout<<endl;
          }
          else{
            //cout<<arrTime<<" "<<curr_q_index->object->currTrain->depTime<<endl;
            // if(arrTime<curr_q_index->object->currTrain->depTime){
            //   newObj->currDay = (curr_q_index->object->currDay+1)%7;
            // }
            if(curr_q_index->object->stops<maxStopOvers){
              for(int i_day=0; i_day<7; i_day++){
                if(currTrain->object->daysOfWeek[i_day]){
                  int transitTime = (currTrain->object->depTime-arrTime) + ((7+i_day-curr_q_index->object->currDay)%7)*2400;
                  if(transitTime<=maxTransitTime*100 and transitTime>=0){
                    myJourneyObject *newObj=new myJourneyObject(*curr_q_index->object);
                    newObj->stops++;
                    newObj->currDay = i_day;
                    layover *new_layover = new layover(stnNameToIndex.getKeyAtIndex(curr_q_index->object->nextStation),curr_q_index->object->currDay,i_day,arrTime,currTrain->object->depTime,curr_q_index->object->currTrain->journeyCode,currTrain->object->journeyCode);
                    
                    listOfObjects<layover *> *prevLayover = curr_q_index->object->layovers;
                    listOfObjects<layover *> *currLayover = newObj->layovers;
                    if(prevLayover != nullptr){
                      layover *layover_obj = new layover(*prevLayover->object);
                      newObj->layovers = new listOfObjects<layover *>(layover_obj);
                      currLayover = newObj->layovers;
                      prevLayover = prevLayover->next;
                    }
                    while(prevLayover != nullptr){
                      layover *layover_obj = new layover(*prevLayover->object);
                      currLayover->next = new listOfObjects<layover *>(layover_obj);
                      prevLayover = prevLayover->next;
                      currLayover = currLayover->next;
                    }
                    if(currLayover != nullptr){
                      currLayover->next = new listOfObjects<layover *>(new_layover);
                    }
                    else{
                      newObj->layovers = new listOfObjects<layover *>(new_layover);
                    }

                    // newObj->layovers.push_back(new_layover);
                    newObj->currStation = curr_q_index->object->nextStation;
                    newObj->currTrain = currTrain->object;
                    newObj->nextStation = currStation->object->adjacentStnIndex;
                    last_q_index->next = new listOfObjects<myJourneyObject *>(newObj);
                    last_q_index=last_q_index->next;
                  }
                }
              }
            }
          }
          currTrain=currTrain->next;
        }
        currStation = currStation->next;
      }
    }
    curr_q_index = curr_q_index->next;
  }
  if(num_results == 0){
    cout<<RED<<"NO JOURNEY FOUND"<<RESET<<endl;
  }
  else{
    cout<<GREEN<<num_results<<" JOURNEYS FOUND"<<RESET<<endl;
  }
  return;
}


#endif
