#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#define IN_PROGRESS 0
#define INVALID -1
#define VALID 1

using namespace std;

template <typename T> class myList{
  public:
  listOfObjects<T> * journeys;// HEAD of the linked list
  listOfObjects<T> * tail; // TAIL of the linked list
  int size;

  myList(){
    journeys = nullptr; tail = nullptr; size = 0;
  }
  void add(T num){
    listOfObjects<T>* toAdd = new listOfObjects<T>(num);
    if(tail!=nullptr){// non-empty queue
      tail->next = toAdd;
      toAdd->prev = tail;
      tail = tail->next;
    }
    else{// empty queue
      journeys = toAdd;
      tail = toAdd;
    }
    // increase the size of vector by 1
    size++;
  }
  T remove(){
    T last;
    if(size==0){
      return nullptr; // cannot remove anymore
    }
    else if (size==1){
      last = journeys->object;
      journeys = nullptr;
      tail = nullptr;
    }
    else{
      last = tail->object;
      tail = tail->prev;
    }
    size--; // reduce the size of the queue
    return last;
  }
  bool find(T num){ // do not use find for other than T = int 
    listOfObjects<T> * iterator = journeys;
    bool found = false;
    while(iterator!=nullptr){
      if (iterator->object == num){
        found = true;
        break;
      }
      iterator = iterator->next;
    }

    return found;
  }
  void print(){
    listOfObjects<T> * iterator = journeys;
    while(iterator!=nullptr){
      iterator->object->print();
      iterator = iterator->next; 
    }
  }
};

int totalStopOvers = 0;

class printable{
  public:
    string stationName;
    int journeyCode;
    string deptDay, arrDay;
    int deptTime, arrTime;
    int transition;

    printable(string stationName_, int journeyCode_, int deptDay_, int arrDay_, int deptTime_, int arrTime_, int transition_ = 0){
      stationName = stationName_;
      journeyCode = journeyCode_;
      if(deptDay_ == 0){deptDay = "Sun";}
      else if(deptDay_ == 1){deptDay = "Mon";}
      else if(deptDay_ == 2){deptDay = "Tue";}
      else if(deptDay_ == 3){deptDay = "Wed";}
      else if(deptDay_ == 4){deptDay = "Thurs";}
      else if(deptDay_ == 5){deptDay = "Fri";}
      else if(deptDay_ == 6){deptDay = "Sat";}

      if(arrDay_ == 0){arrDay = "Sun";}
      else if(arrDay_ == 1){arrDay = "Mon";}
      else if(arrDay_ == 2){arrDay = "Tue";}
      else if(arrDay_ == 3){arrDay = "Wed";}
      else if(arrDay_ == 4){arrDay = "Thurs";}
      else if(arrDay_ == 5){arrDay = "Fri";}
      else if(arrDay_ == 6){arrDay = "Sat";}

      deptTime = deptTime_;
      arrTime = arrTime_;
      transition = (transition_/60)*100 + (transition_%60) ;
    }

    void print(){
      if(transition==0){cout << BLUE << "Station: " << stationName << RESET << "\n";}
      else{cout << BLUE << "Station: " << stationName << " " << GREEN << "Transit Time (HHMM format): " << transition << RESET <<"\n";totalStopOvers++;}
      cout << GREEN << "Train JourneyCode: " << journeyCode << "\t\t" << RED << "Departs: " << deptDay << ", " << deptTime << "\t" << "Arrives: " << arrDay << ", " << arrTime << RESET << endl;
    }
};
myList<printable *> validJourney;

int DFS(int stationIndex, int destinationIndex, int countStopOvers, int maxStopOvers, int maxTransitTime,int day, TrainInfoPerStation* const &currJourney, StationAdjacencyList* const adjacency,   listOfObjects<TrainInfoPerStation *>* stationInfo[], Dictionary<int> &stnNameToIndex){
  /* 1. stationIndex: the station code of the station on which the user is present now
     2. destinationStationIndex: the station code of the destination station, where the user has to reach
     3. countStopOvers: The number of stopovers, the user has made before reaching the current station
     4. maxStopOvers: Maximum number of stopovers allowed for the user
     5. maxTransitTime: maximum time the user can wait for another train on a station
     6. day: the day on which the train(any) is arriving on the current station
     7. currJourney: The journey using which the user has come to the current station
     8. adjacency: the dictionary of stations maintained in the planner class
     9. Stationinfo: The list of train departing from the current stations along with their departure times (take departure times for a station from here)*/

  // currJourney is the journey by which the person came to the current station
  // check countStopOvers > maxStopOvers as invalid
  if(countStopOvers>maxStopOvers){validJourney.remove(); return INVALID;}
  if(stationIndex == destinationIndex){
    //print the linked list of journeys
    cout<<"Journey:"<<endl;
    validJourney.print();
    cout<< BLUE << "Station: " << stnNameToIndex.getKeyAtIndex(destinationIndex) <<RESET<<endl;
    cout<< GREEN << "Total no. of stopovers: " << totalStopOvers << RESET << endl;
    totalStopOvers = 0;
    cout<<endl;
    validJourney.remove();
    return VALID;
  }
  

  listOfObjects<StationConnectionInfo *> *toList = new listOfObjects<StationConnectionInfo *>(nullptr);
  toList = adjacency[stationIndex].toStations; // to store the linked list of Stations which can be reached from the starting station

  while(toList!=nullptr){
    listOfObjects<TrainInfoPerStation *> *currTrain = stationInfo[toList->object->adjacentStnIndex];
    int transitTime = 0;
    while(currTrain!=nullptr){
        listOfObjects<TrainInfoPerStation *>* deptTrain = stationInfo[stationIndex];
        while(deptTrain!=nullptr){
          if(deptTrain->object->journeyCode == currTrain->object->journeyCode){
            break;
          }
          deptTrain = deptTrain->next;
        }
        if(deptTrain==nullptr){currTrain = currTrain->next;continue;}

        /*
        1. currTrain: stores the info about the train the user will take from current station to adjacent station (info on the adjacent station side like the arrival time ON ADJACENT STATION)
        2. deptTrain: stores the info about te same train, but ON THE CURRENT STATION SIDE - like the departure time from CURRENT STATION
        3. currJourney: stores info about the journey the user took to come at the current station
        */

        // The same journey continues
        if(deptTrain->object->journeyCode == currJourney->journeyCode){
          int transitTime = 0;// in any of the below cases, transit time remains 0 only
          // assumption that the train does not wait for more than 24 hrs on the same station
          // if the dept time of the train from current station is < arrival time on current station then the train leaves on the next day
          int deptDay = 0;
          if(deptTrain->object->depTime < currJourney->arrTime){
            deptDay = (day+1)%7; //stores the departure day from the current station
          }
          // if the dept time of the train from current station is > arrival time on current station then the train leaves on the same day
          else{
            deptDay = (day)%7; //stores the departure day from the current station
          }
           // The train reaches on the next day
          if(currTrain->object->arrTime<deptTrain->object->depTime){
            // STORING INFORMATION ABOUT THE CURRENT STATION
            printable * addObject = new printable(stnNameToIndex.getKeyAtIndex(stationIndex), deptTrain->object->journeyCode, (deptDay)%7, (deptDay+1)%7, deptTrain->object->depTime, currTrain->object->arrTime,0);
            validJourney.add(addObject);
            // Reaches one day after it actually departs
            DFS(toList->object->adjacentStnIndex, destinationIndex, countStopOvers, maxStopOvers, maxTransitTime,(deptDay+1)%7, currTrain->object, adjacency, stationInfo, stnNameToIndex );
          }
          // The train reaches on the same day
          else{
            // STORING INFORMATION ABOUT THE CURRENT STATION
            printable * addObject = new printable(stnNameToIndex.getKeyAtIndex(stationIndex), deptTrain->object->journeyCode, (deptDay)%7, (deptDay)%7, deptTrain->object->depTime, currTrain->object->arrTime,0);
            validJourney.add(addObject);
            DFS(toList->object->adjacentStnIndex, destinationIndex, countStopOvers, maxStopOvers, maxTransitTime,(deptDay)%7, currTrain->object, adjacency, stationInfo, stnNameToIndex);
          }            
        }
        // user changes journeys (trains)
        else{
          // Updating the number of changeover - update while calling the function!!!!
          // if the departure time is less than the arrival time then surely the next train cannot deprt on the same day
          int transitTime = 0;
          int deptArray[7];
          int validDeptArray[7];
          int transiteTimes[7];
          for (int i = 0;i<7;i++){
            deptArray[i] = 0;
            validDeptArray[i] = 0;
            transiteTimes[i] = 0;
          }
          // departure array is made
          for (int i = 0 ; i<7;i++){
            if (deptTrain->object->arrTime > deptTrain->object->depTime){
              deptArray[(i+1)%7] = deptTrain->object->daysOfWeek[i%7];
            }
            else{
              deptArray[(i)%7] = deptTrain->object->daysOfWeek[i%7];
            }
          }
          //valid departure array to check transit times
          for (int i = day ;i < day+ 7;i++){
            if (deptArray[i%7] ==1 ){
            transitTime = ((i-day)%7)*24*60 + (deptTrain->object->depTime/100)*60 + (deptTrain->object->depTime%100)- (currJourney->arrTime/100)*60 - (currJourney->arrTime%100);
            if(transitTime <= maxTransitTime && transitTime >= 0){ 
              validDeptArray[i%7] = 1;
              transiteTimes[i%7] = transitTime;
               }
            else{
                validDeptArray[i%7] = 0;
            }
            }
          }
          for (int i = 0; i<7;i++){
            if (validDeptArray[i]==1){
              // The train reaches on the next day
              if(currTrain->object->arrTime<deptTrain->object->depTime){
                // STORING INFORMATION ABOUT THE CURRENT STATION
                printable * addObject = new printable(stnNameToIndex.getKeyAtIndex(stationIndex), deptTrain->object->journeyCode, (i)%7, (i+1)%7, deptTrain->object->depTime, currTrain->object->arrTime,transiteTimes[i]);
                validJourney.add(addObject);
                // Reaches one day after it actually departs
                DFS(toList->object->adjacentStnIndex, destinationIndex, countStopOvers+1, maxStopOvers, maxTransitTime,(i+1)%7, currTrain->object, adjacency, stationInfo, stnNameToIndex );
              }
              // The train reaches on the same day
              else{
                // STORING INFORMATION ABOUT THE CURRENT STATION
                printable * addObject = new printable(stnNameToIndex.getKeyAtIndex(stationIndex), deptTrain->object->journeyCode, (i)%7, (i)%7, deptTrain->object->depTime, currTrain->object->arrTime,transiteTimes[i]);
                validJourney.add(addObject);                
                DFS(toList->object->adjacentStnIndex, destinationIndex, countStopOvers+1, maxStopOvers, maxTransitTime,(i)%7, currTrain->object, adjacency, stationInfo, stnNameToIndex);
              }
            }
          } 
        }
        currTrain = currTrain->next;
    }
    toList = toList->next;
  }
  validJourney.remove();
  return IN_PROGRESS; // when the node has no adjacent outgoing stations then backtrack and explore next stations
}
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
   // To get the starting station index 
  Entry<int>* startStationEntry = stnNameToIndex.get(srcStnName);
  int startIndex = startStationEntry->value;

  // To getthe index of the end station
  Entry<int>* endStationEntry = stnNameToIndex.get(destStnName);
  int endIndex = endStationEntry->value;
  // convert maxTransitTime to minutes - input was taken in HHMM format - assuming user gives correct 
  maxTransitTime = (maxTransitTime/100)*60 + (maxTransitTime%100);
  // Access the pointer to the out linked list of trains from the start stations to check which nodes to traverse during the DFS
  listOfObjects<StationConnectionInfo *> *toList = new listOfObjects<StationConnectionInfo *>(nullptr);
  toList = adjacency[startIndex].toStations; // to store the linked list of Stations which can be reached from the starting station

  while(toList!=nullptr){
    listOfObjects<TrainInfoPerStation *> *currTrain = stationInfo[toList->object->adjacentStnIndex];
    while(currTrain!=nullptr){
      listOfObjects<TrainInfoPerStation *>* deptTrain = stationInfo[startIndex];
      while(deptTrain!=nullptr){
        if(deptTrain->object->journeyCode == currTrain->object->journeyCode){
          break;
        }
        deptTrain = deptTrain->next;
      }
      if(deptTrain==nullptr){currTrain = currTrain->next; continue;}
        for (int i = 0; i < 7; i++){
          if(deptTrain->object->daysOfWeek[i]){
            // if the arrival time at the next station < departure time at current station then the train must have arrived there at the next day
            if (currTrain->object->arrTime < deptTrain->object->depTime){// assumption that a train takes < 24 hrs on a journey
            // updating the day
              // STORING INFORMATION ABOUT THE CURRENT STATION
              printable * addObject = new printable(srcStnName, deptTrain->object->journeyCode, i,(i+1)%7, deptTrain->object->depTime, currTrain->object->arrTime,0);
              validJourney.add(addObject);
              if (deptTrain->object->journeyCode == 231){cout<<"Calling DFS 1 for 231";}
              DFS(toList->object->adjacentStnIndex, endIndex, 0, maxStopOvers, maxTransitTime,(i+1)%7, currTrain->object, adjacency, stationInfo, stnNameToIndex);
              validJourney.remove();
            }
            else{
              // STORING INFORMATION ABOUT THE CURRENT STATION
              printable * addObject = new printable(srcStnName, deptTrain->object->journeyCode, i,i, deptTrain->object->depTime, currTrain->object->arrTime,0);
              validJourney.add(addObject);
              // the train arriving on the adjacent station on the same day
              if (deptTrain->object->journeyCode == 231){cout<<"Calling DFS 2 for 231"<<endl;}
              DFS(toList->object->adjacentStnIndex, endIndex, 0, maxStopOvers, maxTransitTime,i%7, currTrain->object, adjacency, stationInfo, stnNameToIndex);
              validJourney.remove();
            } 
          }
     }
        currTrain = currTrain->next;
    }
    toList = toList->next;
    }
  return;
}
#endif
