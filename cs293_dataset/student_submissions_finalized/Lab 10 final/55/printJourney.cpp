#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

//I have adopted BFS Search

//Each Instance of this struct stores the switching information
struct TrainSwitchInfo{
  int prevJCode;
  // int nextJCode;
  int prevArrTime;
  // int prevArrDay;
  // int nextArrTime;
  // int nextDepTime;
  // int nextDepDay;
  int switchStationIndex;
  int transitTime;
  TrainInfoPerStation* NextTrainInfoAtSwitchingStation;
  TrainSwitchInfo(int prevJCode, int prevArrTime, TrainInfoPerStation* NextTrainInfoAtSwitchingStation, int switchStationIndex){
    this->prevJCode = prevJCode;
    this->prevArrTime = prevArrTime;
    this->NextTrainInfoAtSwitchingStation = NextTrainInfoAtSwitchingStation;
    this->switchStationIndex = switchStationIndex;
    this->transitTime = -1;
  }
};
  
//Our Result list is made of this struct
struct IndexJC{
  int stnIndex;
  int JrnyCode;
  int trainsChanged;
  TrainInfoPerStation* InfoOfTrainAtTheStation;//Train Information at the station (with index as stnIndex)
  listOfObjects<TrainSwitchInfo*> *switchInfo;//Stores the list of train switching information
  IndexJC(int stnIndex, int JrnyCode, int trainsChanged, TrainInfoPerStation* InfoOfTrainAtTheStation){
    this->stnIndex = stnIndex;
    this->JrnyCode = JrnyCode;
    this->trainsChanged = trainsChanged;
    this->InfoOfTrainAtTheStation = InfoOfTrainAtTheStation;
    this->switchInfo = nullptr;
  }
};




void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
  int srcIndex = stnNameToIndex.get(srcStnName)->value;
  int destIndex = stnNameToIndex.get(destStnName)->value;

  listOfObjects<IndexJC*> *result = nullptr;
  listOfObjects<IndexJC*> *Q = nullptr,*Qlast = nullptr;

  listOfObjects<StationConnectionInfo *> *srcToStationList = adjacency[srcIndex].toStations;


  //Queue Initialization
  while(srcToStationList!=nullptr){
    int nextStnIndex = srcToStationList->object->adjacentStnIndex;
    for(listOfObjects<TrainInfoPerStation*> *info = srcToStationList->object->trains; info!=nullptr; info = info->next){
      //
      TrainInfoPerStation* currInfo = info->object;

      listOfObjects<TrainInfoPerStation*> *foundNextJourney = nullptr;
      listOfObjects<TrainInfoPerStation*> *stationInfoNext = stationInfo[nextStnIndex];

      while(stationInfoNext!=nullptr){
        if(stationInfoNext->object->journeyCode == currInfo->journeyCode){
          foundNextJourney = stationInfoNext;
          break;
        }
        stationInfoNext= stationInfoNext->next;
      } 

      TrainInfoPerStation* nextInfo = foundNextJourney->object;

      int jCode = currInfo->journeyCode;
      int stSeq = currInfo->stopSeq;
      int arrTime = currInfo->arrTime;
      int depTime = currInfo->depTime;
      //Splitting according to week days
      for (int i=0; i < 7; i++) {
	      if (currInfo->daysOfWeek[i]) {
          TrainInfoPerStation *newExpandedElement = new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);
          newExpandedElement->setDayOfWeek(i);
          // //!!
          // cout<<i<<endl;
          // //!!
          for(int j=0;j<7;j++){
            int jrnyTime = (j*2400+nextInfo->arrTime)-(i*2400+depTime);
            if(currInfo->daysOfWeek[j] && jrnyTime >0 && jrnyTime<2400){
              // //!!
              // cout<<i<<" "<<j<<endl;
              // cout<<"jrnyTime = "<<jrnyTime<<" = "<<(j*2400+nextInfo->arrTime)<<" - "<<(i*2400+depTime)<<endl;
              // //!!
              TrainInfoPerStation *nextExpandedElement = new TrainInfoPerStation(nextInfo->journeyCode, nextInfo->stopSeq, nextInfo->arrTime, nextInfo->depTime);
              nextExpandedElement->setDayOfWeek(j);
              IndexJC* entry = new IndexJC(nextStnIndex, nextExpandedElement->journeyCode,0,nextExpandedElement);
              TrainSwitchInfo* srcSwitchInfo = new TrainSwitchInfo(-999,-999,newExpandedElement,srcIndex);
              entry->switchInfo = new listOfObjects<TrainSwitchInfo*>(srcSwitchInfo);
              if(Q==nullptr){
                Q = new listOfObjects<IndexJC*>(entry);
                Qlast = Q;
                // //!!
                // cout<<"Added to the queue, Station Index: "<<entry->stnIndex<<" Journey Code: "<<entry->JrnyCode<<endl;
                // //!!
              }
              else{
                Qlast->next = new listOfObjects<IndexJC*>(entry);
                Qlast->next->prev = Qlast;
                Qlast = Qlast->next;
                // //!!
                // cout<<"Added to the queue, Station Index: "<<entry->stnIndex<<" Journey Code: "<<entry->JrnyCode<<endl;
                // //!!
              }
            }
          }
	      }
      }
      //
    }
    srcToStationList = srcToStationList->next;
  }
  //Queue Initialization Done;

  //Queue Update
  while(Q!=nullptr){

    IndexJC* head = Q->object;
    int headStnIndex = head->stnIndex;
    int headJrnyCode = head->JrnyCode;
    int trainsChangedTillNow = head->trainsChanged;
    int dayNumber;
    for(int i=0;i<7;i++){
      if(head->InfoOfTrainAtTheStation->daysOfWeek[i]){
        dayNumber = i;
        break;
      }
    }

    //Found the Destination
    if(headStnIndex == destIndex){
      if(result == nullptr){
        result = new listOfObjects<IndexJC*>(head);
        // //!!
        // cout<<"Added to result"<<endl;
        // //!!
      }
      else{
        result->next = new listOfObjects<IndexJC*>(head);
        result->next->prev = result;
        result = result->next;
        // //!!
        // cout<<"Added to result"<<endl;
        // //!!
      }
      Q = Q->next;
      // //!!
      // cout<<"Popped from Queue and got destination, stn Index: "<<headStnIndex<<" Journey Code: "<<headJrnyCode<<endl;
      // //!!
      if(Q!=nullptr){
        Q->prev = nullptr;
      }

      continue;
    }

    //If Head is not the Destination
    listOfObjects<StationConnectionInfo *> *toStationInfo = adjacency[headStnIndex].toStations;
    while(toStationInfo!=nullptr){
      int nextStationIndex = toStationInfo->object->adjacentStnIndex;
      listOfObjects<TrainInfoPerStation*> *trains = toStationInfo->object->trains;

      while(trains!=nullptr){
        //
        TrainInfoPerStation* nextInfo = nullptr;
        TrainInfoPerStation* InfoOfNextTrainAtCurrentStation = trains->object;

        listOfObjects<TrainInfoPerStation*> *foundNextJourney = nullptr;
        listOfObjects<TrainInfoPerStation*> *stationInfoNext = stationInfo[nextStationIndex];
        while(stationInfoNext!=nullptr){
          if(stationInfoNext->object->journeyCode == InfoOfNextTrainAtCurrentStation->journeyCode){
            foundNextJourney = stationInfoNext;
            break;
          }
          stationInfoNext= stationInfoNext->next;
        } 
        nextInfo = foundNextJourney->object;

        // Make as many copies of currInfo as the total count of days in the week
        // when this train runs from/to this station
        int jCode = nextInfo->journeyCode;
        int stSeq = nextInfo->stopSeq;
        int arrTime = nextInfo->arrTime;
        int depTime = nextInfo->depTime;
    
        for (int i=0; i < 7; i++) {
          if (InfoOfNextTrainAtCurrentStation->daysOfWeek[i]) {
          if(jCode==headJrnyCode){

            if(2400*i + InfoOfNextTrainAtCurrentStation->arrTime==2400*dayNumber + head->InfoOfTrainAtTheStation->arrTime){
              
              TrainInfoPerStation* nextInfoCopy = nextInfo;

              for (int j=0; j<7; j++){
                int jrnyTime = (j*2400+arrTime)-(i*2400+InfoOfNextTrainAtCurrentStation->depTime);
                if(nextInfoCopy->daysOfWeek[j] && jrnyTime<2400 && jrnyTime>0){
                  // //!!
                  // cout<<i<<" "<<j<<endl;
                  // cout<<"jrnyTime = "<<jrnyTime<<" = "<<(j*2400+arrTime)<<" - "<<(i*2400+InfoOfNextTrainAtCurrentStation->depTime)<<endl;
                  // //!!
                  TrainInfoPerStation * nextExpandedElement = new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);
                  nextExpandedElement->setDayOfWeek(j);
                  IndexJC *EntryTrainCont = new IndexJC(toStationInfo->object->adjacentStnIndex,jCode,trainsChangedTillNow,nextExpandedElement);
                  listOfObjects<TrainSwitchInfo*> *newSwitchInfo = nullptr;
                  for(listOfObjects<TrainSwitchInfo*> *headSwitchInfoCopy = head->switchInfo;headSwitchInfoCopy!=nullptr;headSwitchInfoCopy = headSwitchInfoCopy->next){
                    if(newSwitchInfo==nullptr){
                      newSwitchInfo = new listOfObjects<TrainSwitchInfo*>(headSwitchInfoCopy->object);
                    }
                    else{
                      newSwitchInfo->next = new listOfObjects<TrainSwitchInfo*>(headSwitchInfoCopy->object);
                      newSwitchInfo->next->prev = newSwitchInfo;
                      newSwitchInfo = newSwitchInfo->next;
                    }
                  }

                  while(true){
                    if(newSwitchInfo == nullptr){
                      break;
                    }
                    if(newSwitchInfo->prev == nullptr){
                      break;
                    }
                    newSwitchInfo = newSwitchInfo->prev;
                  }
                  EntryTrainCont->switchInfo = newSwitchInfo;
                  Qlast->next = new listOfObjects<IndexJC*>(EntryTrainCont);
                  Qlast->next->prev = Qlast;
                  Qlast = Qlast->next;
                  // //!!
                  // cout<<"Added to the queue, Station Index: "<<EntryTrainCont->stnIndex<<" Journey Code: "<<EntryTrainCont->JrnyCode<<endl;
                  // //!!

                }
              }

            }

          }
          //If train needs to be switched
          else{
            //Checking Stop Over Limit
            if(trainsChangedTillNow + 1 > maxStopOvers){
              continue;
            }
            //Checking Transit Time Limit
            //Here Assumption Used that Transit Time is less than 7 days
            int nextStationIndex = toStationInfo->object->adjacentStnIndex;
            int prevArrTime  = dayNumber*2400 + head->InfoOfTrainAtTheStation->arrTime;
            int NextDeptTime = 2400*i + InfoOfNextTrainAtCurrentStation->depTime;
            int CopyNextDeptTime = NextDeptTime;
            while(CopyNextDeptTime-prevArrTime<0){
              CopyNextDeptTime += 2400*7;
            }
            int tranTime;
            if(CopyNextDeptTime%100>=prevArrTime%100){
              tranTime = CopyNextDeptTime - prevArrTime;
            }
            else{
              tranTime = (CopyNextDeptTime/100 - prevArrTime/100)*100 - 40 + CopyNextDeptTime%100 - prevArrTime%100;
            }
            if(tranTime>maxTransitTime){
              continue;
            }
            //Adding to queue
            else{
              TrainInfoPerStation* nextInfoCopy = nextInfo;
              for (int j=0; j<7; j++){
                int jrnyTime = (j*2400+arrTime)-(i*2400+InfoOfNextTrainAtCurrentStation->depTime);
                if(nextInfoCopy->daysOfWeek[j] && jrnyTime<2400 && jrnyTime>0){
                  // //!!
                  // cout<<i<<" "<<j<<endl;
                  // cout<<"jrnyTime = "<<jrnyTime<<" = "<<(j*2400+arrTime)<<" - "<<(i*2400+InfoOfNextTrainAtCurrentStation->depTime)<<endl;
                  // //!!
                  //NTCS = NextTrainCurrentStation
                  int jCodeNxt = nextInfoCopy->journeyCode;
                  int stSeqNxt = nextInfoCopy->stopSeq;
                  int arrTimeNxt = nextInfoCopy->arrTime;
                  int depTimeNxt = nextInfoCopy->depTime;
                  TrainInfoPerStation * nextExpandedElement = new TrainInfoPerStation(jCodeNxt, stSeqNxt, arrTimeNxt, depTimeNxt);
                  nextExpandedElement->setDayOfWeek(j);
                  IndexJC* EntryTrainChange = new IndexJC(nextStationIndex,jCode,trainsChangedTillNow+1,nextExpandedElement);

                  listOfObjects<TrainSwitchInfo*> *newSwitchInfo = nullptr;
                  for(listOfObjects<TrainSwitchInfo*> *headSwitchInfoCopy = head->switchInfo;headSwitchInfoCopy!=nullptr;headSwitchInfoCopy = headSwitchInfoCopy->next){
                    if(newSwitchInfo==nullptr){
                      newSwitchInfo = new listOfObjects<TrainSwitchInfo*>(headSwitchInfoCopy->object);
                    }
                    else{
                      newSwitchInfo->next = new listOfObjects<TrainSwitchInfo*>(headSwitchInfoCopy->object);
                      newSwitchInfo->next->prev = newSwitchInfo;
                      newSwitchInfo = newSwitchInfo->next;
                    }
                  }
                  while(newSwitchInfo->next!=nullptr){
                    newSwitchInfo = newSwitchInfo->next;
                  }
                  int jCodeNTCS = InfoOfNextTrainAtCurrentStation->journeyCode;
                  int stSeqNTCS = InfoOfNextTrainAtCurrentStation->stopSeq;
                  int arrTimeNTCS = InfoOfNextTrainAtCurrentStation->arrTime;
                  int depTimeNTCS = InfoOfNextTrainAtCurrentStation->depTime;
                  TrainInfoPerStation * nextExpandedElementForSwitch = new TrainInfoPerStation(jCodeNTCS, stSeqNTCS, arrTimeNTCS, depTimeNTCS);
                  nextExpandedElementForSwitch->setDayOfWeek(i);
                  TrainSwitchInfo* nextSwitchInfo = new TrainSwitchInfo(headJrnyCode,head->InfoOfTrainAtTheStation->arrTime,nextExpandedElementForSwitch,headStnIndex);
                  nextSwitchInfo->transitTime = tranTime;
                  newSwitchInfo->next = new listOfObjects<TrainSwitchInfo*>(nextSwitchInfo);
                  newSwitchInfo->next->prev = newSwitchInfo;
                  while(true){
                    if(newSwitchInfo == nullptr){
                      break;
                    }
                    if(newSwitchInfo->prev == nullptr){
                      break;
                    }
                    newSwitchInfo = newSwitchInfo->prev;
                  }
                  EntryTrainChange->switchInfo = newSwitchInfo;

                  Qlast->next = new listOfObjects<IndexJC*>(EntryTrainChange);
                  Qlast->next->prev = Qlast;
                  Qlast = Qlast->next;
                  // //!!
                  // cout<<"Added to the queue, Station Index: "<<EntryTrainChange->stnIndex<<" Journey Code: "<<EntryTrainChange->JrnyCode<<endl;
                  // //!!
                }
              }

            }
          }
        }
        }
        //
        //Next Iteration
        trains = trains->next;
      }

      //Next Iteration
      toStationInfo = toStationInfo->next; 
    }

    Q = Q->next;
    // //!!
    // cout<<"Popped from Queue and not destination, stn Index: "<<headStnIndex<<" Journey Code: "<<headJrnyCode<<" Day Number: "<<dayNumber<<endl;
    // //!!
    if(Q!=nullptr){
      Q->prev = nullptr;
    }

  }
  //Restore Result before printing
  while(true){
    if(result == nullptr){
      break;
    }
    if(result->prev == nullptr){
      break;
    }
    result = result->prev;
  }

  //Printing the found journeys
  // //!!
  // cout<<"Printing Result"<<endl;
  // //!!
  int JourneyCounter = 0;
  if(result == nullptr){
    cout << "No Journeys Available"<<endl;
  }
  else{

    cout<<"These are the possible Journey Options for you"<<endl;
    while(result!=nullptr){
      listOfObjects<TrainSwitchInfo*> *switchInfo = result->object->switchInfo;
      cout<<"New Journey"<<endl;
      JourneyCounter+=1;
      while(switchInfo!=nullptr){
        if(switchInfo->object->prevArrTime == -999){
          cout<<"Journey Starts"<<endl;
          printStationInfo(new listOfObjects<TrainInfoPerStation*>(switchInfo->object->NextTrainInfoAtSwitchingStation));
        }
        else{
          cout<<"Switch the Train at: "<< stnNameToIndex.getKeyAtIndex(switchInfo->object->switchStationIndex) <<endl;
          cout<<"Transit Time: "<<switchInfo->object->transitTime <<endl;
          cout<<"Next Train Info: "<<endl;
          printStationInfo(new listOfObjects<TrainInfoPerStation*>(switchInfo->object->NextTrainInfoAtSwitchingStation));

        }
        switchInfo = switchInfo->next;
      }
      result = result->next;
    }
  }
  cout<<"Number Of Journeys Available: "<<JourneyCounter<<endl;
 
  return;
}

#endif