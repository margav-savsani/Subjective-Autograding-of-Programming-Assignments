#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// t1-t2

//print Journeys from the list, along with their station names and transit times(if any)
void printjour(listOfObjects<TrainInfoPerStation *> *list, listOfObjects<string>* stnNames, listOfObjects<double> *transitTimes){
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  listOfObjects<TrainInfoPerStation *> *currList = list;
  TrainInfoPerStation* currInfo;
  TrainInfoPerStation* prevInfo=NULL;
  if(currList==NULL){
    cout << "NO JOURNEYS FOUND" << endl;
  }
  cout << "-----------------------------------" << endl;
  cout << endl;
  cout << stnNames->object << " ->>> " << endl;
  int i=0;
   while (currList != nullptr) {
    currInfo = currList->object;
    if (currInfo != nullptr) {
      ///added
      if(prevInfo!=NULL){
        if(prevInfo->journeyCode!=currInfo->journeyCode){
          // if there is a change of train, then print the transit time
          cout << endl;
          cout << "                       | transit Time: " << transitTimes->object << "hr" << endl;
          transitTimes = transitTimes->next;
          cout << endl;
        }
      }
      cout << "               " << GREEN << "Day(s): " << RESET;
      for (int i=0; i<7; i++) {
  if (currInfo->daysOfWeek[i]) cout << days[i] << " ";
      }
      //cout << endl;
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
      //cout << endl;
    }
    currList = currList->next;
    prevInfo = currInfo;
    cout << endl;
    if(i%2==0){
      //for every 2 alternate stationinfo's the Station changes, print it accordingly 
        stnNames = stnNames->next;
        cout << stnNames->object << " ->>> " << endl;
    }
    i++;
  }
  cout << endl;
  cout << endl;
}

//expand the given list, so that each list element travels only on a single day of week
//Suppose if, 431 travels on mon and tue, expand it to two elements, with each one traveling on a different day
listOfObjects<TrainInfoPerStation *> *expandedlist(listOfObjects<TrainInfoPerStation *> *stnInfolist){
  listOfObjects<TrainInfoPerStation *> *currList, *expandedList;
  TrainInfoPerStation *currInfo;
  currList = stnInfolist;
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
    if (newExpandedElement == nullptr) {
      cerr << "Memory allocation failure." << endl;
      continue;
    }
    newExpandedElement->daysOfWeek[i] = true;

    listOfObjects<TrainInfoPerStation *> *newExpandedListElement = new listOfObjects<TrainInfoPerStation *> (newExpandedElement);
    if (newExpandedListElement == nullptr) {
      cerr << "Memory allocation failure." << endl;
      continue;
    }

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
  return expandedList;
}

// calculate time difference, with time given in HHMM format
double calctimediff(int t1, int t2, int d1, int d2){
  int h1 = t1/100;
  int h2 = t2/100;
  int m1 = t1%100;
  int m2 = t2%100;
  double tdiff = h1-h2 + ((m1-m2)+0.0)/60;
  // if the trains travel on different days, add that time difference in hour format
  if(d1>=d2){
    tdiff = tdiff + 24*(d1-d2);
  }
  else {
    tdiff = tdiff + 24*(7+d1-d2);
  }
  return tdiff;
}

// check which day the train travels
int checkdayofweek(TrainInfoPerStation* tr){
  for(int i=0; i<7; i++){
    if(tr->daysOfWeek[i]){
      return i;
    }
  }
  return -1;
}


bool addtolistif(listOfObjects<TrainInfoPerStation *> *list, listOfObjects<TrainInfoPerStation *> *sInfo, TrainInfoPerStation* tobeadded2, TrainInfoPerStation* tobechecked, int maxTime, bool &trainchange, listOfObjects<double>* transitTimes){
// check for corresponding TrainStationInfo of tobeadded2 in sInfo, by comparing journey codes and time difference
  TrainInfoPerStation* tobeadded1;
  int time = 10000;
  int t=0;
  while(sInfo!=NULL){
    if(sInfo->object->journeyCode == tobeadded2->journeyCode){
      t = calctimediff(tobeadded2->arrTime,sInfo->object->depTime,checkdayofweek(tobeadded2),checkdayofweek(sInfo->object));
       if(t>=0 && t<time){
         time = t;
         tobeadded1 = sInfo->object;
       }
    }
    sInfo = sInfo->next;
  }
  int d1 = checkdayofweek(tobeadded1);
  int d2 = checkdayofweek(tobechecked);

  while(list->next!=NULL){
    list = list->next;
  }
  // Add tobeadde1, tobeadded2 to the given list only if the time difference between tobechecked and tobeadded1 is within maxTransitTime
  if( (calctimediff(tobeadded1->depTime,tobechecked->arrTime,d1,d2))<= maxTime && (calctimediff(tobeadded1->depTime,tobechecked->arrTime,d1,d2))>=0){
    list->next = new listOfObjects<TrainInfoPerStation *>(tobeadded1);
    list = list->next;
    list->next = new listOfObjects<TrainInfoPerStation *>(tobeadded2);
    if(tobeadded1->journeyCode != tobechecked->journeyCode){
      //if there is a change of train, add the transitTime to the given list
      while(transitTimes->next!=NULL){
        transitTimes = transitTimes->next;
      }
      transitTimes->next = new listOfObjects<double>(calctimediff(tobeadded1->depTime,tobechecked->arrTime,d1,d2));
      trainchange = true; 
    }
    return true;
  }

  return false;
}
void addtolist(listOfObjects<TrainInfoPerStation *> *list, listOfObjects<TrainInfoPerStation *> *sInfo, TrainInfoPerStation* tobeadded2){
// check for corresponding TrainStationInfo of tobeadded2 in sInfo, by comparing journey codes and time difference
  TrainInfoPerStation* tobeadded1;
  int time = 10000;
  int t=0;
  while(sInfo!=NULL){
    if(sInfo->object->journeyCode == tobeadded2->journeyCode){
      t = calctimediff(tobeadded2->arrTime,sInfo->object->arrTime,checkdayofweek(tobeadded2),checkdayofweek(sInfo->object));
       if(t>=0 && t<time){
         time = t;
         tobeadded1 = sInfo->object;
       }
    }
    sInfo = sInfo->next;
  }


  while(list->next!=NULL){
    list = list->next;
  }
  // add tobeadded1 and tobeadded2 to the given list
  list->next = new listOfObjects<TrainInfoPerStation *>(tobeadded1);
  list = list->next;
  list->next = new listOfObjects<TrainInfoPerStation *>(tobeadded2);
  return;
}

//Add string to the list
void addstringtolist(listOfObjects<string>* list, string s){
  while(list->next!=NULL){
    list = list->next;
  }
  list->next = new listOfObjects<string>(s);
  return;
}

// remove T object from the list
template <typename T>
void removefromlist(listOfObjects<T> *list){
  listOfObjects<T> *prev =NULL;
  while(list->next!=NULL){
    prev = list;
    list = list->next;
  }

  prev->next = NULL;
  return;
}

//count the number of train changes from the given journey
int trainshifts(listOfObjects<TrainInfoPerStation *> *list){
  listOfObjects<TrainInfoPerStation *> *prev = list;
  listOfObjects<TrainInfoPerStation *> *curr = list->next;
  int shift=0;
  while(curr!=NULL){
    if(prev->object->journeyCode!=curr->object->journeyCode){
      shift++;
    }
    prev = curr;
    curr = curr->next;
  }

  return shift;
}
bool destreached=false;
//doDFS from the source index
void doDFS(listOfObjects<double>* transitTimes, listOfObjects<string>* stnNames, Dictionary<int> stnNameToIndex, listOfObjects<TrainInfoPerStation *> *list, TrainInfoPerStation* prevstop, int currind, int destind, StationAdjacencyList adjacency[DICT_SIZE], listOfObjects<TrainInfoPerStation *> *stationInfo[DICT_SIZE], int maxTime, int maxStopOvers){
  if(prevstop==NULL){
    //if currind is source, just add the TrainStationInfo's from adjacencylist, and call DFS from that adjacentIndex
      listOfObjects<StationConnectionInfo *> *adjstn = adjacency[currind].toStations;
      while(adjstn!=NULL){
        // do DFS for all the adjacent indices, for all possible paths
         int adjstnInd = adjstn->object->adjacentStnIndex;
         listOfObjects<TrainInfoPerStation *> *adjstnCnnList = adjstn->object->trains;
         while(adjstnCnnList!=NULL){
          //Add starting TrainStationInfo and TrainStationInfo of adjcent index
           addtolist(list,stationInfo[currind],adjstnCnnList->object);
           //add the names of Stations at currindex and adjstnInd
           addstringtolist(stnNames,stnNameToIndex.getKeyAtIndex(currind));
           addstringtolist(stnNames,stnNameToIndex.getKeyAtIndex(adjstnInd));
           doDFS(transitTimes, stnNames, stnNameToIndex, list, adjstnCnnList->object, adjstnInd,destind, adjacency,stationInfo, maxTime, maxStopOvers);
           //remove items from list after checking all the paths connecting it
           removefromlist<TrainInfoPerStation *>(list);
           removefromlist<TrainInfoPerStation *>(list);
           removefromlist<string>(stnNames);
           removefromlist<string>(stnNames);
           adjstnCnnList = adjstnCnnList->next;
         }
         adjstn = adjstn->next;
      }
  }
  else {

    //if reached destination, the print the journey so far from source to here
    if(currind==destind){
      //print only if the trainshifts are less than maxStopOvers
      if(trainshifts(list->next)<=maxStopOvers){
        printjour(list->next, stnNames->next, transitTimes->next);
        destreached = true;
      }
      return;
    }

    listOfObjects<StationConnectionInfo *> *adjstn = adjacency[currind].toStations;
    while(adjstn!=NULL){
         int adjstnInd = adjstn->object->adjacentStnIndex;
         listOfObjects<TrainInfoPerStation *> *adjstnCnnList = adjstn->object->trains;
         while(adjstnCnnList!=NULL){
            bool trainchange = false;
            // add to the only if the journey corresponding to adjstnCnnList->object is within maxtransitTime of the prevstop.
            if(addtolistif(list,stationInfo[currind], adjstnCnnList->object,prevstop, maxTime, trainchange, transitTimes)){
              //add the Station name of adjacent station to the list
              addstringtolist(stnNames,stnNameToIndex.getKeyAtIndex(adjstnInd));
              doDFS(transitTimes, stnNames, stnNameToIndex,list, adjstnCnnList->object, adjstnInd, destind,adjacency, stationInfo, maxTime, maxStopOvers);
              //remove items from list after checking all the paths connecting it
              removefromlist<TrainInfoPerStation *>(list);
              removefromlist<TrainInfoPerStation *>(list);
              removefromlist<string>(stnNames);
              if(trainchange)
                removefromlist<double>(transitTimes);
            }
           adjstnCnnList = adjstnCnnList->next;
         }
         adjstn = adjstn->next;
    }
  }
  return;

}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  int start = (stnNameToIndex.get(srcStnName))->value;
  int dest = (stnNameToIndex.get(destStnName))->value;

  TrainInfoPerStation t(0,0,0,0);
  listOfObjects<TrainInfoPerStation *> *list = new listOfObjects<TrainInfoPerStation *>(&t);
  TrainInfoPerStation *prstop = NULL;

  listOfObjects<TrainInfoPerStation *> *sInfo[DICT_SIZE];
  StationAdjacencyList* adj = adjacency;
  for(int i=0; i<DICT_SIZE; i++){
    sInfo[i] = expandedlist(stationInfo[i]);
  }
  for(int i=0; i<DICT_SIZE; i++){
    listOfObjects<StationConnectionInfo *> *adjstn = adjacency[i].toStations;
    listOfObjects<StationConnectionInfo *> *ad = adj[i].toStations;
    while(adjstn!=NULL){
         listOfObjects<TrainInfoPerStation *> *adjstnCnnList = adjstn->object->trains;
         listOfObjects<TrainInfoPerStation *> *l = expandedlist(adjstnCnnList);
         ad->object->trains = new listOfObjects<TrainInfoPerStation *>(new TrainInfoPerStation(0,0,0,0));
         ad->object->trains = l;
         adjstn = adjstn->next;
         ad = ad->next;
    }
  }
  listOfObjects<string>* stnNames = new listOfObjects<string>("start");
  listOfObjects<double>* transitTimes = new listOfObjects<double>(-1);
  doDFS(transitTimes, stnNames, stnNameToIndex,list,prstop,start,dest,adj,sInfo,maxTransitTime,maxStopOvers);
  if(destreached==false){
    cout << RED << "NO JOURNEYS FOUND" << RESET << endl;
  }
  return;
}
