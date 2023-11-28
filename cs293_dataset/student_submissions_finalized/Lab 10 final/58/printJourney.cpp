#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#include<cmath>
#endif

using namespace std;

void myprint(listOfObjects<TrainInfoPerStation *> *expandedList,listOfObjects<int> *transit,listOfObjects<string> *stnnames,int current){
  listOfObjects<TrainInfoPerStation *> *currList = expandedList;
  listOfObjects<int> *a = transit;
  int noofstops = current;

  a = transit;

  listOfObjects<string> *b = stnnames;

  TrainInfoPerStation *currInfo;
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

  cout << endl;

  if(noofstops!=0){
    cout << "Journey:   " << "No of stops: " << noofstops <<endl;
  }
  else{
    cout << "Direct Journey-no stops" << endl;
  }

  while (currList != nullptr) {
    currInfo = currList->object;

    if (currInfo != nullptr) {
      cout << GREEN <<  b->object;
      if(a->object!=0){
        cout << " Transit Time: " << a->object << RESET;
      }
      else{
        cout << RESET;
      }
      cout << endl;

      cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << endl;
      int i =0;
      for(int j=0; j<7; j++){
	      if(currInfo->daysOfWeek[j]){
          i = j;
          break;
        }
      }

      cout << RED << "Day: " << RESET;
      cout << days[i] << "\t";

      cout << RED << "Arr: " << RESET;

      if(currInfo->arrTime == -1) {
	      cout << "Starts" << "   ";
      }
      else {
	      cout << currInfo->arrTime << "     ";
      }

      cout << RED << "Dep: " << RESET;
      if (currInfo->depTime == -1) {
	      cout << "Ends";
      }
      else {
	    cout << currInfo->depTime;
      }
      cout << endl;
    }
    currList = currList->next;
    a = a->next;
    b = b->next;
  }
}

void addtrains(int JCode,int z,int y,int current,int maxStopOvers,int maxTransitTime,listOfObjects<TrainInfoPerStation *> *l,StationAdjacencyList *adjacency,Dictionary<int> stnnametoindex,listOfObjects<TrainInfoPerStation *> **stationinfo,listOfObjects<int> *transit,listOfObjects<string> *stnnames){
  if(z==y && current<=maxStopOvers){
    myprint(l,transit,stnnames,current);
    return;
  }

  if(current>maxStopOvers){
    return;
  }

  listOfObjects<TrainInfoPerStation *> *currTrain = stationinfo[z];
  while(currTrain->object->journeyCode!=JCode){
    currTrain = currTrain->next;
  }

  listOfObjects<TrainInfoPerStation *> *p = l;
  while(p->next!=nullptr){
    p = p->next;
  }

  listOfObjects<int> *q = transit;
  while(q->next!=nullptr){
    q = q->next;
  }

  listOfObjects<string> *r = stnnames;
  while(r->next!=nullptr){
    r = r->next;
  }

  int day = 0;
  for(int i=0;i<7;i++){
    if(currTrain->object->daysOfWeek[i]){
      day = i;
      break;
    }
  }
 
  listOfObjects<StationConnectionInfo *> *a = adjacency[z].toStations;
  while(a!=nullptr){

    int w = a->object->adjacentStnIndex;
    listOfObjects<TrainInfoPerStation *> *b = a->object->trains;

    listOfObjects<TrainInfoPerStation *> *currList, *expandedList;
    TrainInfoPerStation *currInfo;
    string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    // Expanding information in stnInfoList to get a list of train info
    // in which each element of the list refers to a single day of the
    // week.  This is the list that has to be finally sorted using
    // quicksort.

    currList = b;
    expandedList = nullptr;
    int listLength = 0;
    while (currList != nullptr) {
      currInfo = currList->object;
      if (currInfo != nullptr) {
        // Make as many copies of currInfo as the total count of days in the week
        // when this train runs from/to this station
        int jCode = currInfo->journeyCode;
        int stSeq = currInfo->stopSeq;
        int arrTime = currInfo->arrTime;
        int depTime = currInfo->depTime;
      
        for (int i=0; i < 7; i++) {
          if (currInfo->daysOfWeek[i]) {
            TrainInfoPerStation *newExpandedElement = new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);
 
            newExpandedElement->setDayOfWeek(i);

            listOfObjects<TrainInfoPerStation *> *newExpandedListElement = new listOfObjects<TrainInfoPerStation *> (newExpandedElement);

            if (expandedList == nullptr) {
              expandedList = newExpandedListElement;
            }
            else {
              newExpandedListElement->next = expandedList;
              expandedList->prev = newExpandedListElement;
              expandedList = newExpandedListElement;
            }
            listLength++;
          }
        }
      }
      currList = currList->next;
    }

    while(expandedList!=nullptr){
      int day1 = 0;
      for(int i=0;i<7;i++){
        if(expandedList->object->daysOfWeek[i]){
          day1 = i;
          break;
        }
      }
      if(expandedList->object->arrTime==-1){
        if(day1>=day){
          int m = expandedList->object->depTime;int n = currTrain->object->arrTime;
          double time = (m/100 - n/100) + (m%100-n%100)/60.0 + (day1-day)*24;
          if(time>=0 && time<=maxTransitTime){
            p->next = new listOfObjects<TrainInfoPerStation *>(expandedList->object);
            if(expandedList->object->journeyCode == currTrain->object->journeyCode){
              q->next = new listOfObjects<int>(0);
            }
            else{
              q->next = new listOfObjects<int>(round(time));
            }
            r->next = new listOfObjects<string>(stnnametoindex.getKeyAtIndex(z));

            if(JCode==expandedList->object->journeyCode){
            addtrains(expandedList->object->journeyCode,w,y,current,maxStopOvers,maxTransitTime,l,adjacency,stnnametoindex,stationinfo,transit,stnnames);}
            else{
              addtrains(expandedList->object->journeyCode,w,y,current+1,maxStopOvers,maxTransitTime,l,adjacency,stnnametoindex,stationinfo,transit,stnnames);
            }
          }
        }

        if(day1<day){
          int m = expandedList->object->depTime;int n = currTrain->object->arrTime;
          double time = 7*24 + (m/100 - n/100) + (m%100-n%100)/60.0 + (day1-day)*24;
          if(time>=0 && time<=maxTransitTime){
            p->next = new listOfObjects<TrainInfoPerStation *>(expandedList->object);
            if(expandedList->object->journeyCode == currTrain->object->journeyCode){
              q->next = new listOfObjects<int>(0);
            }
            else{
              q->next = new listOfObjects<int>(round(time));
            }
            r->next = new listOfObjects<string>(stnnametoindex.getKeyAtIndex(z));
            if(JCode==expandedList->object->journeyCode){
            addtrains(expandedList->object->journeyCode,w,y,current,maxStopOvers,maxTransitTime,l,adjacency,stnnametoindex,stationinfo,transit,stnnames);}
            else{
              addtrains(expandedList->object->journeyCode,w,y,current+1,maxStopOvers,maxTransitTime,l,adjacency,stnnametoindex,stationinfo,transit,stnnames);
            }
          }
        }

      }

      else if(expandedList->object->arrTime < expandedList->object->depTime){
        if(day1>=day){
          int m = expandedList->object->depTime;int n = currTrain->object->arrTime;
          double time = (m/100 - n/100) + (m%100-n%100)/60.0 + (day1-day)*24;
          if(time>=0 && time<=maxTransitTime){
            p->next = new listOfObjects<TrainInfoPerStation *>(expandedList->object);
            if(expandedList->object->journeyCode == currTrain->object->journeyCode){
              q->next = new listOfObjects<int>(0);
            }
            else{
              q->next = new listOfObjects<int>(round(time));
            }
            r->next = new listOfObjects<string>(stnnametoindex.getKeyAtIndex(z));
            if(JCode==expandedList->object->journeyCode){
            addtrains(expandedList->object->journeyCode,w,y,current,maxStopOvers,maxTransitTime,l,adjacency,stnnametoindex,stationinfo,transit,stnnames);}
            else{
              addtrains(expandedList->object->journeyCode,w,y,current+1,maxStopOvers,maxTransitTime,l,adjacency,stnnametoindex,stationinfo,transit,stnnames);
            }
          }
        }

        else{
          int m = expandedList->object->depTime;int n = currTrain->object->arrTime;
          double time = 7*24 + (m/100 - n/100) + (m%100-n%100)/60.0 + (day1-day)*24;
          if(time>=0 && time<=maxTransitTime){
            p->next = new listOfObjects<TrainInfoPerStation *>(expandedList->object);
            if(expandedList->object->journeyCode == currTrain->object->journeyCode){
              q->next = new listOfObjects<int>(0);
            }
            else{
              q->next = new listOfObjects<int>(round(time));
            }
            r->next = new listOfObjects<string>(stnnametoindex.getKeyAtIndex(z));
            if(JCode==expandedList->object->journeyCode){
            addtrains(expandedList->object->journeyCode,w,y,current,maxStopOvers,maxTransitTime,l,adjacency,stnnametoindex,stationinfo,transit,stnnames);}
            else{
              addtrains(expandedList->object->journeyCode,w,y,current+1,maxStopOvers,maxTransitTime,l,adjacency,stnnametoindex,stationinfo,transit,stnnames);
            }
          }
        }
      }

      else if(expandedList->object->arrTime > expandedList->object->depTime){
        day1 = (day1+1)%7;
        if(day1>=day){
          int m = expandedList->object->depTime;int n = currTrain->object->arrTime;
          double time = (m/100 - n/100) + (m%100-n%100)/60.0 + (day1-day)*24;
          if(time>=0 && time<=maxTransitTime){
            p->next = new listOfObjects<TrainInfoPerStation *>(expandedList->object);
            if(expandedList->object->journeyCode == currTrain->object->journeyCode){
              q->next = new listOfObjects<int>(0);
            }
            else{
              q->next = new listOfObjects<int>(round(time));
            }
            r->next = new listOfObjects<string>(stnnametoindex.getKeyAtIndex(z));
            if(JCode==expandedList->object->journeyCode){
            addtrains(expandedList->object->journeyCode,w,y,current,maxStopOvers,maxTransitTime,l,adjacency,stnnametoindex,stationinfo,transit,stnnames);}
            else{
              addtrains(expandedList->object->journeyCode,w,y,current+1,maxStopOvers,maxTransitTime,l,adjacency,stnnametoindex,stationinfo,transit,stnnames);
            }
          }
        }

        if(day1<day){
          int m = expandedList->object->depTime;int n = currTrain->object->arrTime;
          double time = 7*24 + (m/100 - n/100) + (m%100-n%100)/60.0 + (day1-day)*24;
          if(time>=0 && time<=maxTransitTime){
            p->next = new listOfObjects<TrainInfoPerStation *>(expandedList->object);
            if(expandedList->object->journeyCode == currTrain->object->journeyCode){
              q->next = new listOfObjects<int>(0);
            }
            else{
              q->next = new listOfObjects<int>(round(time));
            }
            r->next = new listOfObjects<string>(stnnametoindex.getKeyAtIndex(z));
            if(JCode==expandedList->object->journeyCode){
            addtrains(expandedList->object->journeyCode,w,y,current,maxStopOvers,maxTransitTime,l,adjacency,stnnametoindex,stationinfo,transit,stnnames);}
            else{
              addtrains(expandedList->object->journeyCode,w,y,current+1,maxStopOvers,maxTransitTime,l,adjacency,stnnametoindex,stationinfo,transit,stnnames);
            }
          }
        }
      }

      expandedList = expandedList->next;
    }

    a = a->next;
  }
  return;
}
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  Entry<int> *a1 = stnNameToIndex.get(srcStnName);
  int x = a1->value;
  Entry<int> *a2 = stnNameToIndex.get(destStnName);
  int y = a2->value;

  listOfObjects<StationConnectionInfo *> *a = adjacency[x].toStations;
  listOfObjects<TrainInfoPerStation *> *l;
  listOfObjects<int> *transit;
  listOfObjects<string> *stnnames;

  int no_of_trains = 0;// CHeck this out later

  while(a!=nullptr){

    int z = a->object->adjacentStnIndex;
    listOfObjects<TrainInfoPerStation *> *b = a->object->trains;

    listOfObjects<TrainInfoPerStation *> *currList, *expandedList;
    TrainInfoPerStation *currInfo;
    string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    // Expanding information in stnInfoList to get a list of train info
    // in which each element of the list refers to a single day of the
    // week.  This is the list that has to be finally sorted using
    // quicksort.

    currList = b;
    expandedList = nullptr;
    int listLength = 0;
    while (currList != nullptr) {
      currInfo = currList->object;
      if (currInfo != nullptr) {
        // Make as many copies of currInfo as the total count of days in the week
        // when this train runs from/to this station
        int jCode = currInfo->journeyCode;
        int stSeq = currInfo->stopSeq;
        int arrTime = currInfo->arrTime;
        int depTime = currInfo->depTime;
      
        for (int i=0; i < 7; i++) {
      if (currInfo->daysOfWeek[i]) {
      TrainInfoPerStation *newExpandedElement = new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);

      newExpandedElement->setDayOfWeek(i);

      listOfObjects<TrainInfoPerStation *> *newExpandedListElement = new listOfObjects<TrainInfoPerStation *> (newExpandedElement);

      if (expandedList == nullptr) {
        expandedList = newExpandedListElement;
      }
      else {
        newExpandedListElement->next = expandedList;
        expandedList->prev = newExpandedListElement;
        expandedList = newExpandedListElement;
      }
      listLength++;
    }
        }
      }
      currList = currList->next;
    }

    while(expandedList!=nullptr){
      l = new listOfObjects<TrainInfoPerStation *>(expandedList->object);
      transit = new listOfObjects<int>(0);
      stnnames = new listOfObjects<string>(srcStnName);
      addtrains(expandedList->object->journeyCode,z,y,0,maxStopOvers,maxTransitTime,l,adjacency,stnNameToIndex,stationInfo,transit,stnnames);


      expandedList = expandedList->next;
    }
    a = a->next;
  }
  
  return;
}

#endif
