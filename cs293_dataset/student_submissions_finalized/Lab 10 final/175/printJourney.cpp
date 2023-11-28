#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include "planner.h"
using namespace std;

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime) // the main idea used is recursion, i.e. dfs, along with many static variables
{
  static int found; // if any train is found
  static int recur = -1; // the recursion level
  static int codes[DICT_SIZE]; // used to store the journey code of the parent train, i.e. through which code the train came to this station
  static pair<string,listOfObjects<TrainInfoPerStation *> *> vec[DICT_SIZE]; // array of pairs containing station name and a list of objects, used to print the entire schedule of the journey
  static int index; // the index of the previous array to determine where to insert or remove
  recur ++;
  if (recur == 0){ // initialising the static variables only for the first time
    found = 0;
    for (int i = 0; i < DICT_SIZE; i++){
      vec[i] = {"", nullptr};
      codes[i] = 0;
    }
    index = 0;
    cout << endl;
  }
  if (maxStopOvers >= 0){ // this condition is obvious
    int src = stnNameToIndex.get(srcStnName)->value, dest = stnNameToIndex.get(destStnName)->value; // getting the index values of the "current" source and destination
    listOfObjects<StationConnectionInfo *> *list = adjacency[src].toStations;
    while (list != nullptr){ // traversing the list
      if (list->object->adjacentStnIndex == dest){ // if destination reached
        if (recur == 0){ // if the "current" source is the "actual" source
          listOfObjects<TrainInfoPerStation *> *tr = list->object->trains;
          while (tr != nullptr){
            found = 1;
            TrainInfoPerStation *x = new TrainInfoPerStation(0, 0, 0, 0); // we need to create a different list object which only contains the desired train and not all
            listOfObjects<TrainInfoPerStation *> *tmp1 = new listOfObjects<TrainInfoPerStation *>(x);
            tmp1->object = tr->object;
            int code = tr->object->journeyCode; // storing the code through which the train came
            cout << srcStnName << endl;
            printStationInfo(tmp1);
            cout << destStnName << endl;
            listOfObjects<TrainInfoPerStation *> *S = stationInfo[stnNameToIndex.get(destStnName)->value]; // getting the trains of the destination
            while (S != nullptr){
              if (code == S->object->journeyCode){
                TrainInfoPerStation *x = new TrainInfoPerStation(0, 0, 0, 0); // we need to create a different list object which only contains the desired train and not all
                listOfObjects<TrainInfoPerStation *> *tmp2 = new listOfObjects<TrainInfoPerStation *>(x);
                tmp2->object = S->object;
                printStationInfo(tmp2);
              }
              S = S->next;
            }
            cout << "=======================" << endl; // demarcating the end of a particular route
            tr = tr->next;
          }
        }
        else{
          listOfObjects<TrainInfoPerStation *> *tr = list->object->trains;
          while (tr != nullptr){
            if (codes[src] == tr->object->journeyCode){
              found = 1;
              TrainInfoPerStation *x = new TrainInfoPerStation(0, 0, 0, 0); // we need to create a different list object which only contains the desired train and not all
              listOfObjects<TrainInfoPerStation *> *tmp1 = new listOfObjects<TrainInfoPerStation *>(x);
              tmp1->object = tr->object;
              int code = tr->object->journeyCode; // storing the code through which the train came
              for (int i = 0; i < index; i++){ // printing whatever is in the list firstly
                cout << vec[i].first << endl;
                printStationInfo(vec[i].second);
              }
              cout << srcStnName << endl; // then adding the current station and that of the destination
              printStationInfo(tmp1);
              cout << destStnName << endl;
              listOfObjects<TrainInfoPerStation *> *S = stationInfo[stnNameToIndex.get(destStnName)->value]; // getting the trains of the destination
              while (S != nullptr){
                if (code == S->object->journeyCode){
                  TrainInfoPerStation *x = new TrainInfoPerStation(0, 0, 0, 0); // we need to create a different list object which only contains the desired train and not all
                  listOfObjects<TrainInfoPerStation *> *tmp2 = new listOfObjects<TrainInfoPerStation *>(x);
                  tmp2->object = S->object;
                  printStationInfo(tmp2);
                }
                S = S->next;
              }
              cout << "=======================" << endl; // demarcating the end of a particular route
            }
            else{
              listOfObjects<TrainInfoPerStation *> *inter = stationInfo[stnNameToIndex.get(srcStnName)->value];
              int reqd = 0;
              while (inter != nullptr){
                if (codes[src] == inter->object->journeyCode){
                  reqd = inter->object->arrTime;
                  break;
                }
                inter = inter->next;
              }
              if (((tr->object->depTime > reqd && tr->object->depTime - reqd <= maxTransitTime) or (tr->object->depTime < reqd && 2400 + tr->object->depTime - reqd <= maxTransitTime)) && maxStopOvers > 0){
                found = 1;
                TrainInfoPerStation *x = new TrainInfoPerStation(0, 0, 0, 0); // we need to create a different list object which only contains the desired train and not all
                listOfObjects<TrainInfoPerStation *> *tmp1 = new listOfObjects<TrainInfoPerStation *>(x);
                tmp1->object = tr->object;
                int code = tr->object->journeyCode; // storing the code through which the train came
                for (int i = 0; i < index; i++){ // printing whatever is in the list firstly
                  cout << vec[i].first << endl;
                  printStationInfo(vec[i].second);
                }
                cout << srcStnName << endl; // then adding the current station and that of the destination
                printStationInfo(tmp1);
                cout << destStnName << endl;
                listOfObjects<TrainInfoPerStation *> *S = stationInfo[stnNameToIndex.get(destStnName)->value]; // getting the trains of the destination
                while (S != nullptr){
                  if (code == S->object->journeyCode){
                    TrainInfoPerStation *x = new TrainInfoPerStation(0, 0, 0, 0); // we need to create a different list object which only contains the desired train and not all
                    listOfObjects<TrainInfoPerStation *> *tmp2 = new listOfObjects<TrainInfoPerStation *>(x);
                    tmp2->object = S->object;
                    printStationInfo(tmp2);
                  }
                  S = S->next;
                }
                cout << "=======================" << endl; // demarcating the end of a particular route
              }
            }
            tr = tr->next;
          }
        }
      }
      else{ // destination not reached yet
        if (recur == 0){ // implies that this train has just left from the source
          listOfObjects<TrainInfoPerStation *> *tr = list->object->trains;
          while (tr != nullptr){
            TrainInfoPerStation *x = new TrainInfoPerStation(0, 0, 0, 0); // we need to create a different list object which only contains the desired train and not all
            listOfObjects<TrainInfoPerStation *> *tmp1 = new listOfObjects<TrainInfoPerStation *>(x);
            tmp1->object = tr->object;
            vec[index] = {srcStnName, tmp1}; // pushing into the list
            index ++; // modifying index
            codes[list->object->adjacentStnIndex] = tr->object->journeyCode; // modifying codes
            printPlanJourneys(stnNameToIndex.getKeyAtIndex(list->object->adjacentStnIndex), destStnName, maxStopOvers, maxTransitTime); // recursive call
            vec[index] = {"", nullptr}; // popping from the list
            index --; // modifying index
            tr = tr->next;
          }
        }
        else{ // the journey is midway
          listOfObjects<TrainInfoPerStation *> *tr = list->object->trains;
          while (tr != nullptr){
            if (codes[src] == tr->object->journeyCode){ // if code matches with the previous train code
              TrainInfoPerStation *x = new TrainInfoPerStation(0, 0, 0, 0); // we need to create a different list object which only contains the desired train and not all
              listOfObjects<TrainInfoPerStation *> *tmp1 = new listOfObjects<TrainInfoPerStation *>(x);
              tmp1->object = tr->object;
              vec[index] = {srcStnName, tmp1}; // pushing into the list
              index ++; // modifying index
              codes[list->object->adjacentStnIndex] = tr->object->journeyCode; // modifying codes
              printPlanJourneys(stnNameToIndex.getKeyAtIndex(list->object->adjacentStnIndex), destStnName, maxStopOvers, maxTransitTime); // recursive call
              vec[index] = {"", nullptr}; // popping from the list
              index --; // modifying index
            }
            else{ // if code does not match with the previous train code
              listOfObjects<TrainInfoPerStation *> *inter = stationInfo[stnNameToIndex.get(srcStnName)->value]; // getting the trains from the current station
              int reqd = 0;
              while (inter != nullptr){
                if (codes[src] == inter->object->journeyCode){
                  reqd = inter->object->arrTime; // getting the arrival time of the train through which we arrived at the "current" source
                  break;
                }
                inter = inter->next;
              }
              // transit time is the difference between the departure time of the 2nd train minus the arrival time of the 1st
              if ((tr->object->depTime >= reqd && tr->object->depTime - reqd <= maxTransitTime) or (tr->object->depTime <= reqd && 2400 + tr->object->depTime - reqd <= maxTransitTime)){
                TrainInfoPerStation *x = new TrainInfoPerStation(0, 0, 0, 0); // we need to create a different list object which only contains the desired train and not all
                listOfObjects<TrainInfoPerStation *> *tmp1 = new listOfObjects<TrainInfoPerStation *>(x);
                tmp1->object = tr->object;
                vec[index] = {srcStnName, tmp1}; // pushing into the list
                index ++; // modifying index
                codes[list->object->adjacentStnIndex] = tr->object->journeyCode; // modifying codes
                printPlanJourneys(stnNameToIndex.getKeyAtIndex(list->object->adjacentStnIndex), destStnName, maxStopOvers - 1, maxTransitTime); // recursive call, but 1 subtracted from stop overs since code changed
                vec[index] = {"", nullptr}; // popping from the list
                index --; // modifying index
              }
            }
            tr = tr->next;
          }
        }
      }
      list = list->next;
    }
  }
  if (recur == 0 && found == 0){ // no trains found
    cout << "No trains available" << endl;
  }
  recur --;
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
