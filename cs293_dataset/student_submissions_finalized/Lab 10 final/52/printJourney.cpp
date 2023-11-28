#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

// Class for storing stopover information
class journey_data{
public:
  int stn_index;
  int arr_jc;
  int arr_day;
  int arr_time;
  int dep_jc;
  int dep_day;
  int dep_time;
  int transitTime;

  journey_data(int si, int ajc, int ad, int at, int djc, int dd, int dt, int tt)
    :stn_index(si), arr_jc(ajc), arr_day(ad), arr_time(at), dep_jc(djc), dep_day(dd), dep_time(dt), transitTime(tt)
  {}
};

// Stack implementation using listOfObjects linked list
class journey_stack{
  listOfObjects<journey_data*>* stk;
  Dictionary<int> stnNameToIndex;
  public:
    bool printCalled; // Is print called atleast once
    
    journey_stack(Dictionary<int> snti)
      : stk(nullptr) , stnNameToIndex(snti), printCalled(0)
    {}

    void push(journey_data* jd){
      listOfObjects<journey_data*>* temp = stk;
      stk = new listOfObjects<journey_data*>(jd);
      stk->next = temp;
    }

    void pop(){
      listOfObjects<journey_data*>* temp = stk->next;
      delete stk->object;
      delete stk;
      stk = temp;
    }

    void reverse(){
        listOfObjects<journey_data*>* current = stk;
        listOfObjects<journey_data*>* prev = nullptr;
        listOfObjects<journey_data*>* next = nullptr;
 
        while(current != nullptr){
          next = current->next;
          current->next = prev;
          prev = current;
          current = next;
        }
        stk = prev;
    }

    void print(){
      if(stk == nullptr){
        cout << "No Journeys Possible" << endl;
        return;
      }

      printCalled = 1;
      string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
      reverse();

      listOfObjects<journey_data*>* curr = stk;
      cout << "==== POSSIBLE JOURNEY ====" << endl;
      while(curr != nullptr){
        cout << "=Station: " << stnNameToIndex.getKeyAtIndex(curr->object->stn_index) <<"=" << endl;
        if(curr->object->arr_jc == -1){ // Start info
          cout << GREEN << "Journey Code: " << curr->object->dep_jc << " Start on: " << days[curr->object->dep_day] << " " << curr->object->dep_time << RESET << endl;
        }
        else if(curr->object->dep_jc == -1){  // End info
          cout << RED << "Journey Code: " << curr->object->arr_jc << " reaches here on: " << days[curr->object->arr_day] << " " << curr->object->arr_time << RESET << endl;
        }
        else{ // Stopover info
          cout << RED << "Journey Code: " << curr->object->arr_jc << " reaches here on: " << days[curr->object->arr_day] << " " << curr->object->arr_time << RESET << endl;
          cout << BLUE << "STOPOVER! Transit Time: " << curr->object->transitTime << RESET << endl;
          cout << GREEN << "Journey Code: " << curr->object->dep_jc << " departs on: " << days[curr->object->dep_day] << " " << curr->object->dep_time << RESET << endl;
        }
        curr = curr->next;
      }
      cout << endl;
      reverse();
    }
};


/**
 * @brief Recursive dfs function
 * 
 * @param arr_jc Journey code of train used to arrive at current station
 * @param currStnIndex Index of current Station
 * @param stopovers Stopovers allowed from current station onwards
 * @param prevDeptDay Day of departure from the previous station
 * @param prevDeptTime Time of departure from the previous station
 * @param maxTransitTime maxTransitTime allowed by passenger
 * @param destIndex Index of destination station
 * @param adjacency adjacency array
 * @param jStk Journey Stack
 */
void dfs(int arr_jc, int currStnIndex, int stopovers, int prevDeptDay, int prevDeptTime, int maxTransitTime, int destIndex, StationAdjacencyList* adjacency, journey_stack& jStk){
  /** */
  int arr_time = -1;
  int arr_day = -1;
  
  // arr_jc = -1 means beginning stn
  if(arr_jc != -1){ // If curr station is not beginning station
    // Calculate the arrival time and day of arrival at current station of arr_jc using from stations
    listOfObjects<StationConnectionInfo *> * stns = adjacency[currStnIndex].fromStations;
    while(stns != nullptr){
      listOfObjects<TrainInfoPerStation *> *train = stns->object->trains;
      bool found = 0;
      while(train != nullptr){
        if(train->object->journeyCode == arr_jc){
          arr_time = train->object->arrTime;
          arr_day = (prevDeptDay + (prevDeptTime > arr_time)) % 7;
          found = 1;
          break;
        }
        train = train->next;
      }
      if(found) break;
      stns = stns->next;
    }
  }

  if(currStnIndex == destIndex){  // If current station is the destination
    journey_data* jd = new journey_data(currStnIndex, arr_jc, arr_day, arr_time, -1,-1,-1, -1);
    jStk.push(jd);
    jStk.print(); // Print this possible journey
    jStk.pop();
    return;
  }

  // Apply dfs on all children
  listOfObjects<StationConnectionInfo *> * stns = adjacency[currStnIndex].toStations;
  while(stns != nullptr){
    listOfObjects<TrainInfoPerStation *> *train = stns->object->trains;
    while(train != nullptr){

      if(train->object->journeyCode == arr_jc){ // Using same Journeycode => No Stopover
        int dep_time = train->object->depTime;
        int dep_day = (arr_day + (dep_time < arr_time)) % 7;
        if(dep_time != -1){
          dfs(arr_jc, stns->object->adjacentStnIndex, stopovers, dep_day, dep_time, maxTransitTime, destIndex, adjacency, jStk);
        }
      }
      else if(stopovers>0){   // Using different Journeycode => Stopover
        int dep_time = train->object->depTime;
        bool deptNextDay = dep_time < train->object->arrTime;
        if(dep_time != -1){
          for(int i=0; i<7; i++){
            if(train->object->daysOfWeek[i]){
              int dep_day = (i+deptNextDay)%7;
              int diff = 2400*dep_day + dep_time - (2400*arr_day + arr_time);
              if(diff<0) diff += 2400*7;

              if(diff <= maxTransitTime || arr_jc == -1){ 
                journey_data* jd = new journey_data(currStnIndex, arr_jc, arr_day, arr_time, train->object->journeyCode, dep_day, dep_time, diff);
                jStk.push(jd);
                dfs(train->object->journeyCode, stns->object->adjacentStnIndex, stopovers-1, dep_day, dep_time, maxTransitTime, destIndex, adjacency, jStk);
                jStk.pop();
              }
            }
          }
        }
      }


      train = train->next;
    }
    stns = stns->next;
  }

  
}



void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  if(maxStopOvers<0){
    cout << "Invalid stopovers" << endl;
    return;
  }
  if(maxTransitTime<0){
    cout << "Invalid Transit time" << endl;
    return;
  }
  
  int srcIndex = stnNameToIndex.get(srcStnName)->value;
  int destIndex = stnNameToIndex.get(destStnName)->value;

  journey_stack jStk(stnNameToIndex);
  cout << endl;

  // Main dfs call on root
  dfs(-1, srcIndex, maxStopOvers+1, -1, -1, maxTransitTime, destIndex, adjacency, jStk);

  // If no journeys found
  if(!jStk.printCalled){
    cout << "No Journeys Possible" << endl;
  }

  return;
}

#endif
