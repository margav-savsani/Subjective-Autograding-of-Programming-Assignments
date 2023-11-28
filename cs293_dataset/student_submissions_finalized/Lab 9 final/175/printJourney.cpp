#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <queue>
using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  int src = stnNameToIndex.get(srcStnName)->value, dest = stnNameToIndex.get(destStnName)->value; // getting the index values of the source and destination
  listOfObjects<TrainInfoPerStation *> *S = stationInfo[src]; // helps to print the train info once we arrive at dest
  int found = 0;
  queue<pair<int, int> > bfs; // bfs is the queue which stores station index and journey code as a pair
  bfs.push({src, 0});

  while(bfs.size() != 0){ // the main bfs loop starts
    pair<int, int> stn = bfs.front();
    bfs.pop(); // popping the queue
    listOfObjects<StationConnectionInfo *> *list = adjacency[stn.first].toStations; // looking at the stations connected to the topmost element
    while (list != nullptr){
      if (stn.first != src){ // case 1 -> topmost element not equal to source
        int code[64]; // there can be multiple trains between two stations, so this array stores all such journey codes
        listOfObjects<TrainInfoPerStation *> *tr = list->object->trains;
        int ind = 0;
        while(tr != nullptr){
          int abc = 0;
          for (int i = 0; i < ind; i++){
            if (code[i] == tr->object->journeyCode){ // that array should contain no duplicate journey code
              abc = 1;
              break;
            }
          }
          if (abc == 0){
            code[ind] = tr->object->journeyCode; // populating that array with journey codes
            ind ++;
          }
          tr = tr->next;
        }
        if (list->object->adjacentStnIndex == dest){ // if we have reached the destination
          listOfObjects<TrainInfoPerStation *> *tmp = S;

          while (tmp != nullptr){
            int xyz = 0;
            for (int i = 0; code[i] != 0; i++){
              if (tmp->object->journeyCode == code[i]){ // printStationInfo takes a pointer to a list item and prints all the trains by traversing the list
                TrainInfoPerStation *x = new TrainInfoPerStation(0, 0, 0, 0); // so we need to create a different list object which only contains the desired train and not all
                listOfObjects<TrainInfoPerStation *> *tmp1 = new listOfObjects<TrainInfoPerStation *>(x);
                tmp1->object = tmp->object;
                found = 1;
                printStationInfo(tmp1); // printing the tran's info
                xyz = 1;
                break;
              }
            }
            if (xyz == 1) break;
            tmp = tmp->next;
          }
        }
        for (int i = 0; code[i] != 0; i++){
          if (stn.second == code[i]){ // pushing only if the journey code matches with its parent's journey code
            bfs.push({list->object->adjacentStnIndex, code[i]}); // this step forces me to separate the source and the non-source case
            break; // since for the source, all trains should be pushed into the queue, but not for the non-source case
          }
        }
      }
      else if (stn.first == src){ // case 2 -> topmost element equal to source
        int code[64]; // there can be multiple trains between two stations, so this array stores all such journey codes
        listOfObjects<TrainInfoPerStation *> *tr = list->object->trains;
        int ind = 0;
        while(tr != nullptr){
          int abc = 0;
          for (int i = 0; i < ind; i++){
            if (code[i] == tr->object->journeyCode){ // that array should contain no duplicate journey code
              abc = 1;
              break;
            }
          }
          if (abc == 0){
            code[ind] = tr->object->journeyCode; // populating that array with journey codes
            ind ++;
          }
          tr = tr->next;
        }
        if (list->object->adjacentStnIndex == dest){ // if we have reached the destination
          listOfObjects<TrainInfoPerStation *> *tmp = S;
          
          while (tmp != nullptr){
            for (int i = 0; code[i] != 0; i++){
              if (tmp->object->journeyCode == code[i]){ // printStationInfo takes a pointer to a list item and prints all the trains by traversing the list
                TrainInfoPerStation *x = new TrainInfoPerStation(0, 0, 0, 0); // so we need to create a different list object which only contains the desired train and not all
                listOfObjects<TrainInfoPerStation *> *tmp1 = new listOfObjects<TrainInfoPerStation *>(x);
                tmp1->object = tmp->object;
                found = 1;
                printStationInfo(tmp1); // printing the train's info
              }
            }
            tmp = tmp->next;
          }
        }
        else{
          for (int i = 0; code[i] != 0; i++){
            bfs.push({list->object->adjacentStnIndex, code[i]}); // inserting into the queue
          }
        }
      }
      list = list->next;
    }
  }
  if (found == 0){ // no trains found
    cout << "No direct journeys available" << endl;
  }

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
