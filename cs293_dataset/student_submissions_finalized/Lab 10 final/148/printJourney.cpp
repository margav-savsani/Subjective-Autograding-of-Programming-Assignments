#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include "dictionary.h"
#include "planner.h"
using namespace std;


bool transitTime(TrainInfoPerStation *train1, TrainInfoPerStation *train2, int maxTransitTime){
    // Returns whether we can make this particular transit
    int day1 = -1, day2 = -1;
    for(int i = 0; i < 7; i++){
        if(train1->daysOfWeek[i]){
            day1 = i;
        } 
        if(train2->daysOfWeek[i]){
            day2 = i;
        } 
    }
    if (train2->depTime == -1 || train1->arrTime == -1) return false;
    int time = 0;
    if ( train2->depTime - train1->arrTime < 0){
        day2 -= 1;
        train2->depTime += 2400;
    }
    time = time +  train2->depTime - train1->arrTime;
    if (day2 >= day1){
        time += (day2-day1)*2400;
    }
    else{
        time += (day2+7 - day1)*2400;
    }
    return time < maxTransitTime;

}

  

struct Journey{
        // Struct to store a particular journey, might have multiple trains
        listOfObjects<TrainInfoPerStation *> *firstTrain; // The trains
        listOfObjects<TrainInfoPerStation *> *lastTrain;
        listOfObjects<int> *stationIDs; // The stations

        listOfObjects<int> *lastStation;
        Journey(TrainInfoPerStation *first, int stat){
                firstTrain = new listOfObjects<TrainInfoPerStation *>(first);
                stationIDs = new listOfObjects<int> (stat);
                firstTrain->object= first;
                lastTrain = firstTrain;
                lastStation = stationIDs;
        }
        bool addStop(TrainInfoPerStation *next, int nextstat){
                    // Add a stop (can include things like staying in the same train)
                    if(lastTrain == nullptr){
                        
                    }
                    this->lastTrain->next = new listOfObjects<TrainInfoPerStation *>(next);
                    this->lastTrain->next->prev = this->lastTrain;
                    this->lastTrain = this->lastTrain->next;

                    this->lastStation->next = new listOfObjects<int>(nextstat);
                    this->lastStation->next->prev = this->lastStation;
                    this->lastStation= this->lastStation->next;
                    /* cout << "Adding a stop"  << endl; */
                    return true;
        }
        void pop(){
                // Remove the last element. Like a stack
                if (lastTrain == firstTrain){
                        // We have emptied the lists
                    listOfObjects<int> *statToDelete = lastStation;
                    lastStation= stationIDs= nullptr;
                    delete statToDelete;
                    listOfObjects<TrainInfoPerStation *> *toDelete = lastTrain;
                    lastTrain = firstTrain = nullptr;
                    delete lastTrain;
                    return;
                }
                lastTrain->prev->next = nullptr;

                listOfObjects<TrainInfoPerStation *> *toDelete = lastTrain;
                lastTrain = lastTrain->prev;

                lastStation->prev->next = nullptr;

                listOfObjects<int> *toDeleteStat = lastStation;
                lastStation = lastStation->prev;
                delete toDeleteStat;
                delete toDelete;
        }

};






void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
        // Uses a dfs approach

    if(maxStopOvers < 0) return;

  
  static Journey *j = nullptr; // A static variable, that holds the amount of journey traversed till now
  if(j != nullptr && j->lastTrain == nullptr){
    j = nullptr;
  }
  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  int startIndex = stnNameToIndex.get(srcStnName)->value, endIndex = stnNameToIndex.get(destStnName)->value; // The indices of the start and end stations
    if(startIndex == endIndex){
            //Finished the journey
        cout << "New Journey"  << endl;
        
        listOfObjects<TrainInfoPerStation *> *currJourney;
        listOfObjects<int> *stations = j->stationIDs;
        currJourney = j->firstTrain;
        while(currJourney != nullptr){

        cout << "Board train number " << currJourney->object->journeyCode  << " at station " << stnNameToIndex.getKeyAtIndex(stations->object)  << endl;
                listOfObjects<TrainInfoPerStation *> *next = currJourney->next;
                currJourney->next = nullptr;
            printStationInfo(currJourney);
            currJourney->next = next;
            currJourney = currJourney->next;
            stations = stations->next;
            while(currJourney != nullptr && currJourney->next == currJourney){
            currJourney = currJourney->next;
            stations = stations->next;
            }
        }
        cout << "Journey End"  << endl;
        cout  << endl;
        return;
    }
  listOfObjects<StationConnectionInfo *> *toStations = adjacency[startIndex].toStations;
  
TrainInfoPerStation * lastTrain;
  if (j != nullptr)
    lastTrain = j->lastTrain->object;
  else
    lastTrain = nullptr;
  while(toStations != nullptr){

  listOfObjects<StationConnectionInfo *> *fromStations = adjacency[startIndex].fromStations;
  

    listOfObjects<TrainInfoPerStation *> *fromTrains = nullptr;
    if (lastTrain != nullptr){
        bool found = false;
        while(!found){
            fromTrains = fromStations->object->trains;
            while(fromTrains != nullptr){
                if (fromTrains->object->journeyCode == lastTrain->journeyCode) {
                    found = true;
                    break;
                }
                fromTrains = fromTrains->next;
            }
            fromStations = fromStations->next;
        }
            for (int i = 0; i < 7; i++) {
                    fromTrains->object->daysOfWeek[i] = lastTrain->daysOfWeek[i];
            }
    }
    else{
        fromTrains = nullptr;
    }
    string stnName = stnNameToIndex.getKeyAtIndex(toStations->object->adjacentStnIndex);

    listOfObjects<TrainInfoPerStation *> *trains =toStations->object->trains;

    // Expanding ========================
    // Using the same code as in the printStation function
      listOfObjects<TrainInfoPerStation *> *currList, *expandedList;
  TrainInfoPerStation *currInfo;
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};


  currList = trains;
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
	    logFile << "Memory allocation failure." << endl;
	    cerr << "Memory allocation failure." << endl;
	    continue;
	  }
	  newExpandedElement->setDayOfWeek(i);

	  listOfObjects<TrainInfoPerStation *> *newExpandedListElement = new listOfObjects<TrainInfoPerStation *> (newExpandedElement);
	  if (newExpandedListElement == nullptr) {
	    logFile << "Memory allocation failure." << endl;
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
    trains = expandedList;
    // Expansion done ======
    while(trains != nullptr){
            if(lastTrain == nullptr){
                j = new Journey(trains->object, startIndex);
                printPlanJourneys(stnName, destStnName, maxStopOvers, maxTransitTime);
                j->pop();
                lastTrain = nullptr;
            }
            else if (trains->object->journeyCode == lastTrain->journeyCode){
                j->addStop(trains->object, startIndex);
                printPlanJourneys(stnName, destStnName, maxStopOvers, maxTransitTime);
                j->pop();
            }
            else{
                /* printStationInfo(new listOfObjects<TrainInfoPerStation *>(fromTrains->object)); */
                if(transitTime(fromTrains->object, trains->object, maxTransitTime)){
                j->addStop(trains->object, startIndex);
                        printPlanJourneys(stnName, destStnName, maxStopOvers-1, maxTransitTime);
                        j->pop();
                }
            }

            trains = trains->next;
    }
    toStations = toStations->next;
  }
  return;
}

#endif
