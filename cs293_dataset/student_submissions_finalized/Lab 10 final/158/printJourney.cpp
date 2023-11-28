#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef CODES_H
#include "codes.h"
#endif

using namespace std;

string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

// The TrainInfoPerStation doesn't contain the names of the starting point; Why?
class TrainInfoPerStationX{
  public:
    string sourceStnName;
    TrainInfoPerStation* info;

    TrainInfoPerStationX(string sourceStnName, TrainInfoPerStation* info){
      this->sourceStnName = sourceStnName;
      this->info = info;
    } 
};



// returns true if maxTransitTime allows the traveller to jump from t1 to t2
// this function is called directly if the two trains have different journeyCodes
// for same journeyCode, see assumptions.
bool canMakeStopOver(TrainInfoPerStation* t1, TrainInfoPerStation* t2, int maxTransitTime, int currNoOfStopOvers, int maxStopOvers){
  if (currNoOfStopOvers >= maxStopOvers) return false;
  
  int d1, d2; // days on which t1 arrives and t2 departs from station 2.
  for (int i=0;i<7;i++){
    if(t1->daysOfWeek[i]==1){
      d1 = i;
      break;
    }
  }
  for (int i=0;i<7;i++){
    if(t2->daysOfWeek[i]==1){
      d2 = i;
      break;
    }
  }
  int minsOft1 = 60*( (t2->depTime)/100)  + (t2->depTime)%100; /*minutes*/ 
  int minsOft2 = 60*( (t2->depTime)/100)  + (t2->depTime)%100 /*minutes*/;
  int timeGap = ((d2-d1)%7) * 1440 /*minutes*/;

  if(t2->depTime==-1){
    return false;
  } 
  else if (t1->depTime==-1){
    return false;
  }
  else{
    if(t2->arrTime - t2->depTime > 0){
      timeGap += 1440; // if condition to get rid of day change at a station
    }
    //************** CORE OF THIS FUNCTION ****************
    timeGap += minsOft2 - minsOft1;
    if(timeGap <= maxTransitTime ){
      return true;
    }
    else return false;
    //*****************************************************
  }
}




/****************************************************************************
 A modified DFS, devoid of any "visited" array notion. 

 Algorithm in brief:
  1. Fetch the list of those stations adjacent to the current station.
  2. If one of the adjacent stations is the destStn, we make a list of all those trains within transit time 
     and add it to the list that we intend to return. 
  3. For each of these stations, fetch the list of trains going to these stations.
  4. For each element of this list, if the maxTransitTime clause and the stopOver clause allow you,
     move ahead to the train if its journeyCode differes from currjourneyCode. 
     Recursively explore that path and keep note of the list of lists you get.
  5. If an element of this list is the same train (same journeyCode), you can get into the train
     without checking the maxTransitTime Clause. Recursively explore that path!
  6. Now that we have all paths leading from here to the destination, attach the currenttraininfo at the start of every list
     in the list of lists to be returned. 
  7. Finally, return the list of lists. 

*****************************************************************************/

listOfObjects<listOfObjects<TrainInfoPerStationX*>*>* 
DFS(string currSrcStnName, 
    string prevSrcName,
    string destStnName, 
    TrainInfoPerStation* currTrainInfo, 
    StationAdjacencyList* adjacency, 
    Dictionary<int>* stnNameToIndex,
    int maxTransitTime,
    int currNoOfHopovers,
    int maxStopOvers){
  // ****************************FUNCTION STARTS HERE************************
  listOfObjects<listOfObjects<TrainInfoPerStationX*>*>* returnList = nullptr;

  StationAdjacencyList adjacentStations = adjacency[stnNameToIndex->get(currSrcStnName)->value];

  listOfObjects<StationConnectionInfo*>* adjacentStationUnderConsideration = adjacentStations.toStations;

  while( adjacentStationUnderConsideration != nullptr ){
    
    


    listOfObjects<TrainInfoPerStation*>* TrainUnderConsideration = adjacentStationUnderConsideration->object->trains;
    

    /************************Begin List Expansion***************************/
    listOfObjects<TrainInfoPerStation *> *currList, *expandedList;
    TrainInfoPerStation *currInfo;
    string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    // Expanding information in stnInfoList to get a list of train info
    // in which each element of the list refers to a single day of the
    // week.  This is the list that has to be finally sorted using
    // quicksort.

    currList = TrainUnderConsideration;
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
      newExpandedElement->setDayOfWeek(i);

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
    TrainUnderConsideration = expandedList;

  /***************************List Expansion Complete***********************/
    while(TrainUnderConsideration != nullptr){

      if (adjacentStationUnderConsideration->object->adjacentStnIndex == stnNameToIndex->get(destStnName)->value){
        if(TrainUnderConsideration->object->journeyCode == currTrainInfo->journeyCode){
          TrainInfoPerStationX* dummyinfo = new TrainInfoPerStationX(currSrcStnName, TrainUnderConsideration->object);
          listOfObjects<TrainInfoPerStationX*>* dummy = new listOfObjects<TrainInfoPerStationX*>((dummyinfo)); 
          listOfObjects<listOfObjects<TrainInfoPerStationX*>*>* dummySuperList = new listOfObjects<listOfObjects<TrainInfoPerStationX*>*>(dummy);
          dummySuperList->next = returnList;
          returnList = dummySuperList;
        }
        else{
          if (canMakeStopOver(currTrainInfo,TrainUnderConsideration->object, maxTransitTime, currNoOfHopovers, maxStopOvers)){
            currNoOfHopovers++;
            TrainInfoPerStationX* dummyinfo = new TrainInfoPerStationX(currSrcStnName, TrainUnderConsideration->object);
            listOfObjects<TrainInfoPerStationX*>* dummy = new listOfObjects<TrainInfoPerStationX*>((dummyinfo)); 
            listOfObjects<listOfObjects<TrainInfoPerStationX*>*>* dummySuperList = new listOfObjects<listOfObjects<TrainInfoPerStationX*>*>(dummy);
            dummySuperList->next = returnList;
            returnList = dummySuperList;
            currNoOfHopovers--;

          }
          else{
            ;
          }
        }

      }
      else if (TrainUnderConsideration->object->journeyCode == currTrainInfo->journeyCode){
        listOfObjects<listOfObjects<TrainInfoPerStationX*>*>* movingPtr = returnList;
        if(returnList==nullptr){
          returnList = DFS(stnNameToIndex->getKeyAtIndex( adjacentStationUnderConsideration->object->adjacentStnIndex), 
                           currSrcStnName,
                           destStnName, 
                           TrainUnderConsideration->object, 
                           adjacency, 
                           stnNameToIndex, 
                           maxTransitTime, 
                           currNoOfHopovers, 
                           maxStopOvers);
        }
        else{
          while(movingPtr->next!=nullptr){
            movingPtr = movingPtr->next;
          }
          movingPtr->next = DFS(stnNameToIndex->getKeyAtIndex( adjacentStationUnderConsideration->object->adjacentStnIndex), 
                           currSrcStnName,
                           destStnName, 
                           TrainUnderConsideration->object, 
                           adjacency, 
                           stnNameToIndex, 
                           maxTransitTime, 
                           currNoOfHopovers, 
                           maxStopOvers);
        }
      }
      else if (canMakeStopOver(currTrainInfo, TrainUnderConsideration->object, maxTransitTime, currNoOfHopovers,maxStopOvers )){
        listOfObjects<listOfObjects<TrainInfoPerStationX*>*>* movingPtr = returnList;
        if(returnList==nullptr){
          returnList = DFS(stnNameToIndex->getKeyAtIndex( adjacentStationUnderConsideration->object->adjacentStnIndex), 
                           currSrcStnName,
                           destStnName, 
                           TrainUnderConsideration->object, 
                           adjacency, 
                           stnNameToIndex, 
                           maxTransitTime, 
                           currNoOfHopovers+1, 
                           maxStopOvers);
        }
        else{
          while(movingPtr->next!=nullptr){
            movingPtr = movingPtr->next;
          }
          movingPtr->next = DFS(stnNameToIndex->getKeyAtIndex( adjacentStationUnderConsideration->object->adjacentStnIndex), 
                           currSrcStnName,
                           destStnName, 
                           TrainUnderConsideration->object, 
                           adjacency, 
                           stnNameToIndex, 
                           maxTransitTime, 
                           currNoOfHopovers+1, 
                           maxStopOvers);
        }
      }
      else{
        continue;
      }

      TrainUnderConsideration = TrainUnderConsideration->next;
    }

    adjacentStationUnderConsideration = adjacentStationUnderConsideration->next;
  }
  
  // Here we appennd the current station's info at the top of all infos 
  // obtained and we will simply return it
  listOfObjects<listOfObjects<TrainInfoPerStationX*>*>* moving_ptr = returnList;
  if (returnList != nullptr ){
    while(moving_ptr!=nullptr){
      TrainInfoPerStationX* dummyinfo = new TrainInfoPerStationX(prevSrcName, currTrainInfo);
      listOfObjects<TrainInfoPerStationX*>* dummy = new listOfObjects<TrainInfoPerStationX*>((dummyinfo)); 
      dummy->next = moving_ptr->object;
      moving_ptr->object = dummy;
      moving_ptr = moving_ptr->next;       
    }
  }
  return returnList;

}


void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  StationAdjacencyList v = adjacency[stnNameToIndex.get(srcStnName)->value];
  
  int maxTransitTime1 = 60*(maxTransitTime / 100) + maxTransitTime%100;
  
  listOfObjects<listOfObjects<TrainInfoPerStationX*>*>* returnList = nullptr;

  StationAdjacencyList adjacentStations = adjacency[stnNameToIndex.get(srcStnName)->value];

  listOfObjects<StationConnectionInfo*>* adjacentStationUnderConsideration = adjacentStations.toStations;

  while( adjacentStationUnderConsideration != nullptr ){
  

    listOfObjects<TrainInfoPerStation*>* TrainUnderConsideration = adjacentStationUnderConsideration->object->trains;
    
    /************************Begin List Expansion***************************/
    listOfObjects<TrainInfoPerStation *> *currList, *expandedList;
    TrainInfoPerStation *currInfo;
    string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    // Expanding information in stnInfoList to get a list of train info
    // in which each element of the list refers to a single day of the
    // week.  This is the list that has to be finally sorted using
    // quicksort.

    currList = TrainUnderConsideration;
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
      newExpandedElement->setDayOfWeek(i);

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
    TrainUnderConsideration = expandedList;

  /***************************List Expansion Complete***********************/

    while(TrainUnderConsideration != nullptr){

      
        listOfObjects<listOfObjects<TrainInfoPerStationX*>*>* movingPtr = returnList;
        if(returnList==nullptr){
          returnList = DFS(stnNameToIndex.getKeyAtIndex( adjacentStationUnderConsideration->object->adjacentStnIndex), 
                           srcStnName,
                           destStnName, 
                           TrainUnderConsideration->object, 
                           adjacency, 
                           &stnNameToIndex, 
                           maxTransitTime, 
                           0, 
                           maxStopOvers);
        }
        else{
          while(movingPtr->next!=nullptr){
            movingPtr = movingPtr->next;
          }
          movingPtr->next = DFS(stnNameToIndex.getKeyAtIndex( adjacentStationUnderConsideration->object->adjacentStnIndex), 
                           srcStnName,
                           destStnName, 
                           TrainUnderConsideration->object, 
                           adjacency, 
                           &stnNameToIndex, 
                           maxTransitTime, 
                           0, 
                           maxStopOvers);
        }
      
      

      TrainUnderConsideration = TrainUnderConsideration->next;
    }

    adjacentStationUnderConsideration = adjacentStationUnderConsideration->next;
  }
 
   
  //********************************************************************
  // By this point returnList now contains all relevant data!!!
  if(returnList!=nullptr){
    listOfObjects<listOfObjects<TrainInfoPerStationX*>*>* moving_ptr = returnList;
    while(moving_ptr!=nullptr){    
      listOfObjects<TrainInfoPerStationX*>* currList = moving_ptr->object;
      while (currList != nullptr) {
        TrainInfoPerStationX* currInfo = currList->object;
        if (currInfo != nullptr) {
          cout << GREEN << "Day(s): " << RESET;
          for (int i=0; i<7; i++) {
      if (currInfo->info->daysOfWeek[i]) cout << days[i] << " ";
          }
          cout << endl;
          cout <<"From Station: "<< GREEN << currInfo->sourceStnName;
          cout << BLUE << "JourneyCode: " << currInfo->info->journeyCode << RESET << "\t";
          cout << RED << "Arr: " << RESET;
          if (currInfo->info->arrTime == -1) {
      cout << "Starts";
          }
          else {
      cout << currInfo->info->arrTime;
          }
          cout << RED << " Dep: " << RESET;
          if (currInfo->info->depTime == -1) {
      cout << "Ends";
          }
          else {
      cout << currInfo->info->depTime;
          }
          cout << endl;
        }
        currList = currList->next;
      }
      cout << endl;


      moving_ptr=moving_ptr->next;
    }
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
