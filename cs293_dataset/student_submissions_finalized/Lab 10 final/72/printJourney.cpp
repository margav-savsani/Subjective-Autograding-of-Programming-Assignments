#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class stopInfo{
  // A class whose instances are stored to intermediate train changes
public:
  int stopIndex;
  int arrJcode;
  int deptJcode;
  int arrTime;
  int deptTime;
  int arrDay;
  int deptDay;
  int transTime;
  stopInfo(int sI, int aJ, int dJ, int aT, int dT, int aD, int dD, int tT){
    stopIndex = sI;
    arrJcode = aJ;
    deptJcode = dJ;
    arrTime = aT;
    deptTime = dT;
    arrDay = aD;
    deptDay = dD;
    transTime = tT;
  }
};

// Counts the total journeys possible
int routes =0;


void myPrint(listOfObjects<stopInfo *> *stops, Dictionary<int> stnNameToIndex){
  // Function to print the journey path
  if(stops == nullptr)return;
  routes++;
  string days[7];
  days[0]="Sunday"; days[1]="Monday"; days[2]="Tuesday"; days[3]="Wednesday"; days[4]="Thursday"; days[5]="Friday"; days[6]="Saturday"; 
  int i = 0;
  listOfObjects<stopInfo *> *stop = stops;
  cout<<RED<<"\n###########################\n ROUTE "<< routes<<"\n###########################\n"<<RESET;
  while(stop != nullptr){
    if(stop->object->arrJcode == -1){
      // Printing boarding station
      cout << "Boarding at " <<BLUE<< stnNameToIndex.getKeyAtIndex(stop->object->stopIndex)<<RESET << endl;
      cout << "  Journey Code: " << stop->object->deptJcode <<endl<<"  Dep: " << stop->object->deptTime << "  "<<days[stop->object->deptDay] << endl;
    }else if(stop->object->deptJcode == -1){
      // Printing destination
      cout << "Destination " <<BLUE<< stnNameToIndex.getKeyAtIndex(stop->object->stopIndex)<<RESET << endl;
      cout << "  Journey Code: " << stop->object->arrJcode<<endl <<"  Arr: " << stop->object->arrTime << "  " << days[stop->object->arrDay] << endl;
      
    }else{
      // Printing intermediate stations
      cout << GREEN<<"Intermediate stop number " << i <<RESET<< endl;
      cout << "Station: " << BLUE<< stnNameToIndex.getKeyAtIndex(stop->object->stopIndex)<<RESET<< endl;
      cout << "  Arr train info Jcode: " << stop->object->arrJcode   << "  Time: "<< stop->object->arrTime << "   " << days[stop->object->arrDay]<< endl;
      cout << "  Dep train info Jcode: " << stop->object->deptJcode<< "  Time: "<<stop->object->deptTime<<"   "<< days[stop->object->deptDay]<<endl;
      cout << "  Transit time: " << (stop->object->transTime)/100 << "hrs " << (stop->object->transTime)%100 << "mins"<<endl;
    }
    i++;
    cout << "\n";
    stop = stop->next;
  }
  
  return;
}

// A recursive function which takes a station index and journey code of a tarin arring at that station
void myfunc(int enStn, int src, int des, StationAdjacencyList *adjacency, listOfObjects<TrainInfoPerStation *>* *stationInfo, Dictionary<int> stnNameToIndex, listOfObjects<stopInfo *> *stops, int Jcode, int stopOvers, int TransitTime, int entDay, int prevDT){
  if(stopOvers < 0)return;// base case for the recursion
  if(enStn == des){
    // When the destinaton is reached 
    // Copying the stops list and appending the destination to it 
    listOfObjects<stopInfo *> *newlist = new listOfObjects<stopInfo *>(stops->object);
    listOfObjects<stopInfo *> *oldTail = stops;
    listOfObjects<stopInfo *> *newTail = newlist;
    while(oldTail->next != nullptr){
      newTail->next = new listOfObjects<stopInfo *>(oldTail->next->object);
      newTail = newTail->next;
      oldTail = oldTail->next;
    }
    listOfObjects<TrainInfoPerStation *> *ltrai = stationInfo[des];
    int aT=0;int ssq=0;
    while(ltrai != nullptr){
      if(ltrai->object->journeyCode == Jcode){aT = ltrai->object->arrTime; ssq=ltrai->object->stopSeq; break;}
      ltrai = ltrai->next;
    }
    if(aT >= prevDT){
      // Calling print
      newTail->next = new listOfObjects<stopInfo *>(new stopInfo(des, Jcode, -1, aT , 0, entDay ,0,0));
      myPrint(newlist, stnNameToIndex);
    }else{
      newTail->next = new listOfObjects<stopInfo *>(new stopInfo(des, Jcode, -1, aT , 0, (entDay+1)%7 ,0,0));
      myPrint(newlist, stnNameToIndex);
    }
    
    return;
  }
  
  listOfObjects<TrainInfoPerStation *> *trai = stationInfo[enStn];
  int aT=0;int entssq=0;
  while(trai != nullptr){
    if(trai->object->journeyCode == Jcode){aT = trai->object->arrTime; entssq=trai->object->stopSeq; break;}
    trai =trai->next;
  }

  listOfObjects<StationConnectionInfo *> * adjToList = adjacency[enStn].toStations;
  while(adjToList != nullptr){
    listOfObjects<TrainInfoPerStation *> *ltrai = adjToList->object->trains;
    while(ltrai != nullptr){
      // Iterating through all trains from the station
      int idx = adjToList->object->adjacentStnIndex;
      int djc = ltrai->object->journeyCode;
      int dT = ltrai->object->depTime;
      int ssq = ltrai->object->stopSeq;
      if(Jcode == djc){
        // if same train is availabe then just continue
        if(aT >= prevDT){
          if(dT >= aT)myfunc(idx, src, des, adjacency, stationInfo, stnNameToIndex, stops, djc, stopOvers, TransitTime, entDay, dT);
          else myfunc(idx, src, des, adjacency, stationInfo, stnNameToIndex, stops, djc, stopOvers, TransitTime, (entDay+1)%7, dT);
        }else{
          if(dT >= aT)myfunc(idx, src, des, adjacency, stationInfo, stnNameToIndex, stops, djc, stopOvers, TransitTime, (entDay+1)%7, dT);
          else myfunc(idx, src, des, adjacency, stationInfo, stnNameToIndex, stops, djc, stopOvers, TransitTime, (entDay+1)%7, dT);
        }
        
      }else{
        // Change of train at the station
        // Trying all trains leaving
        for(int i = 0; i < 7; i++){
          if(ltrai->object->daysOfWeek[i]){
            int d=0;
            if(ltrai->object->arrTime <= ltrai->object->depTime){
              d=i;
            }else{d=i+1;}
            int arrD = 0;
            if(aT >= prevDT)arrD=entDay;
            else arrD = (entDay+1)%7;
            // Calculating the transit time
            int tttt = d-arrD;
            if(tttt < 0)tttt+=7;
            int tts = 0;
            if(dT%100 >= aT%100)tts =dT - aT;
            else{
              tts = (dT/100 - aT/100)*100 -100 +60 + dT%100 - aT%100;
            } 
            int tranT = (tttt)*2400 +(tts);
            if(tranT <= TransitTime*100 && tranT>=0){
              // Copying stops into a new list
              listOfObjects<stopInfo *> *newlist = new listOfObjects<stopInfo *>(stops->object);
              listOfObjects<stopInfo *> *oldTail = stops;
              listOfObjects<stopInfo *> *newTail = newlist;
              while(oldTail->next != nullptr){
                newTail->next = new listOfObjects<stopInfo *>(oldTail->next->object);
                newTail = newTail->next;
                oldTail = oldTail->next;
              }
              // appending stop info to the newlist
              newTail->next = new listOfObjects<stopInfo *>(new stopInfo(enStn, Jcode, djc, aT, dT, arrD, d, tranT));
              // Making the recursive call with one less stopover
              myfunc(idx, src, des, adjacency,stationInfo, stnNameToIndex, newlist, djc, stopOvers-1, TransitTime, d ,dT);
            }
          }
        }
      }

      ltrai = ltrai->next;
    }
    adjToList = adjToList->next;
  }
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  routes=0;
  // insert your code here
  int srcStnIdx = stnNameToIndex.get(srcStnName)->value;
  int destStnIdx = stnNameToIndex.get(destStnName)->value;

  listOfObjects<StationConnectionInfo *> * adjToList = adjacency[srcStnIdx].toStations;

  while(adjToList !=nullptr){
    listOfObjects<TrainInfoPerStation *> *ltrai = adjToList->object->trains;
    while(ltrai != nullptr){
      // For all trains leaving the source station
      int idx = adjToList->object->adjacentStnIndex;
      int jc = ltrai->object->journeyCode;
      int dT = ltrai->object->depTime;
      int ssq = ltrai->object->stopSeq;
      for(int i = 0; i < 7; i++){
        // For each day the traind leaves the station
        if(ltrai->object->daysOfWeek[i]){
          listOfObjects<stopInfo *> *myList = new listOfObjects<stopInfo *>(new stopInfo(srcStnIdx, -1, jc, 0,dT, 0 , i, 0));
          myfunc(idx, srcStnIdx, destStnIdx, adjacency, stationInfo, stnNameToIndex, myList, jc, maxStopOvers, maxTransitTime, i, dT);
        }
      }
      ltrai = ltrai->next;
    }
    adjToList = adjToList->next;
  }
  
  // When there is no path
  if(routes==0)cout<<RED<<"NO JOURNEYS AVAILABLE\n"<<RESET;
  return;
}

#endif
