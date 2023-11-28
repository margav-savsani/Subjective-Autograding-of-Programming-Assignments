#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include<vector>
#include<string>
using namespace std;

int *arr = new int[DICT_SIZE]; // stores the id's of the stations are grey
int in,fin = 0;  // array indexing
listOfObjects<TrainInfoPerStation*> *list; // storing the trains
bool found = false; // if the destination is found
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  // insert your code here
  static int recursive_lvl = -1;
  int srcindex = stnNameToIndex.get(srcStnName)->value; // obtaining the indices 
  int destindex = stnNameToIndex.get(destStnName)->value;

  StationAdjacencyList from_src = adjacency[srcindex]; // obtaining the adjacent stations
  listOfObjects<StationConnectionInfo *> * src_to_list = from_src.toStations;
  
  if(recursive_lvl == -1){
    recursive_lvl++;
    listOfObjects<StationConnectionInfo *> * p = src_to_list; // iteration on this list
    while(p!=nullptr) {
      StationConnectionInfo* obj = p->object;
      int stn_index = obj->adjacentStnIndex;
      arr[fin] = stn_index; // adding to the array
      fin++;
      string stn_name = stnNameToIndex.getKeyAtIndex(stn_index); // getting name from dictionary
      listOfObjects<TrainInfoPerStation*> *trains = obj->trains;
      listOfObjects<TrainInfoPerStation*> *l = list;
      while(trains!=nullptr){
        if(l==nullptr){ // if there is no train in list
          l = trains;
        }
        else {         // adding trains to the list
          l->next=trains;
          l = l->next;
        }
        trains = trains->next; // iteration
      }
      list = l;
      if(stn_index == destindex){ // if the destination is found
        found = true;
      }
      printDirectJourneys(stn_name,destStnName); // recursion
      in++;
      if(found == true) {
        printStationInfo(list); // printing the list 
      }
      p = p->next; // iteration
    }
    if(found!=true){ // if there is no direct journey
      cout << "No direct journeys available" <<endl;
    }
    return;
  }

  // second part of recursion

  listOfObjects<StationConnectionInfo *> * p = src_to_list;
  while(p!=nullptr){
  StationConnectionInfo* obj = p->object;
  int stn_index = obj->adjacentStnIndex;
  bool ispresent = false; // for checking
  for (int i=in;i<=fin;i++){
    if(arr[i]==stn_index) {
      ispresent = true; // if it is already visited
      break;
    }
  }
  if(ispresent == false){
      arr[fin] = stn_index;
      fin++; 
      string stn_name = stnNameToIndex.getKeyAtIndex(stn_index);
      listOfObjects<TrainInfoPerStation*> *trains = obj->trains;// new list for storing trains
      printStationInfo(trains); // for debugging 
      listOfObjects<TrainInfoPerStation*> *head = list;
      listOfObjects<TrainInfoPerStation*> *intersect = nullptr;
      // listOfObjects<TrainInfoPerStation*> *head = intersect;
      while(trains!=nullptr){ // finding the intersection of two list of trains
        while(head!=nullptr){
          if(trains->object->journeyCode==head->object->journeyCode) {
            if(intersect==nullptr) { // no common element till now
              intersect = trains;
              printStationInfo(intersect);
            }
            if(intersect!=nullptr) { // adding the common elements
              intersect->next=trains;
            }
          }
          head = head->next; // iteration
        }
        trains=trains->next; // iteration
      }
      head = intersect;
      list = head; // changing the list to intersection 
  }
  p = p->next; // iteration on p
  }
  recursive_lvl--; 
  return;
}

#endif
