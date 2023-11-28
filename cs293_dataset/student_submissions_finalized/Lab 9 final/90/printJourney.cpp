#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// Created a new struct, Trainlist
// As an alternate to queue, as we weren't
// allowed to use STL queue/vectors
// In this we shall store trains
// and do BFS on them, instead of stations
struct TrainList{
public:
  int index, jCode; //index to store the source_index of the train, jCode for its journey Code
  TrainList *next; //pointer to the next element in this linked list
  
  // Constructor
  TrainList(int index, int jCode)  {
    this->index = index;
    this->jCode = jCode;
    next = nullptr;
  }
};

//Returns common trains in lists list1 and list2
//O(mn) where m is number of trains in list1
// and n is number of trains in list2
listOfObjects<TrainInfoPerStation *> *intersections(listOfObjects<TrainInfoPerStation *> *list1,listOfObjects<TrainInfoPerStation *> *list2){
  listOfObjects<TrainInfoPerStation *> *final_list = nullptr; //final list which has all the intersected/common trains
  listOfObjects<TrainInfoPerStation *> *curr; // pointer variable to iterate over list1
  while(list1 != nullptr){
    listOfObjects<TrainInfoPerStation *> *dummy = list2; //pointer variable to iterate over list2
    while(dummy != nullptr){
      if(list1->object->journeyCode == dummy->object->journeyCode){
        if(final_list != nullptr){
          curr->next = new listOfObjects<TrainInfoPerStation *>(list1->object);
          curr=curr->next;
        }
        else{
          final_list = new listOfObjects<TrainInfoPerStation *>(list1->object);
          curr = final_list;
        }
      }
      dummy = dummy->next;
    }
    list1 = list1->next;
  }
  return final_list;
}

// Adds a TrainInfoPerStation* object into the list
void add(listOfObjects<TrainInfoPerStation *> *list, TrainInfoPerStation* object){
    listOfObjects<TrainInfoPerStation *> *last = list;
    while (last->next != nullptr)//Iterate over the list to find the last element
      last = last->next;
    //Insert new element at the next position to the last element
    last->next = new listOfObjects<TrainInfoPerStation *>(object);
}

//Prints direct journeys between srcstn and deststn
void Planner::printDirectJourneys(string srcStnName, string destStnName){
  listOfObjects<TrainInfoPerStation *> *final_list = nullptr; //final list, careful! this is not exactly what has to be finally displayed
  int src_index = stnNameToIndex.get(srcStnName)->value; //Source index extracted from the dictionary
  int dest_index = stnNameToIndex.get(destStnName)->value; //Destination index extracted from the dictionary

  // TrainList to maintain a queue, with initial journey code as 0, assuming
  // no trains have 0 as their journey code
  TrainList *queue = new TrainList(src_index, 0);
  while (queue != nullptr){
    int index = queue->index; //index of first front element of queue
    int jCode = queue->jCode; //journey code of first front element of queue

    if (jCode != 0){ //When source station is not BFS'ed
      listOfObjects<StationConnectionInfo *> *to_station = adjacency[index].toStations; //List of stations which index goes to
      while (to_station != nullptr){ //Iterating over to_station
        int adjacent_index = to_station->object->adjacentStnIndex; //index of adjacent station
        listOfObjects<TrainInfoPerStation *> *train_at_stn = to_station->object->trains; //list of trains between the two stations
        while (train_at_stn != nullptr){ //Iterating over list of trains
          if (adjacent_index == dest_index && train_at_stn->object->journeyCode == jCode){
            //When adjacent index is the destination, and the train code matches
            if (final_list == nullptr)
              final_list = new listOfObjects<TrainInfoPerStation *>(train_at_stn->object);
            else{
              add(final_list, train_at_stn->object);
            }
          }
          else if (train_at_stn->object->journeyCode == jCode){
            //When adjacent index is not the destination but the train code still matches
            TrainList *adjstn = new TrainList(adjacent_index, train_at_stn->object->journeyCode);
            TrainList *last = queue;
            while (last->next != nullptr)
              last = last->next;
            last->next = adjstn;
          }
          train_at_stn = train_at_stn->next;
        }
        to_station = to_station->next;
      }
      // Popping the front element in queue
      if (queue->next == nullptr) queue = nullptr;
      else queue = queue->next;
    }
    else{ //When source station is BFS'ed
      listOfObjects<StationConnectionInfo *> *to_station = adjacency[index].toStations;
      while (to_station != nullptr){
        int adjacent_index = to_station->object->adjacentStnIndex; // index of adjacent station
        listOfObjects<TrainInfoPerStation *> *train = to_station->object->trains;
        while (train != nullptr){
          if (adjacent_index == dest_index){
            if(final_list == nullptr)
              final_list = new listOfObjects<TrainInfoPerStation *>(train->object);
            else{
              add(final_list, train->object);
            }
          }
          else{
            TrainList *adjacent_station = new TrainList(adjacent_index, train->object->journeyCode);
            TrainList *curr = queue;
            while (curr->next != nullptr)
              curr = curr->next;
            curr->next = adjacent_station;
          }
          train = train->next;
        }
        to_station = to_station->next;
      }
      if (queue->next == nullptr)
        queue = nullptr;
      else{
        queue = queue->next;
      }
    }
  }

  //When no direct trains found
  if (final_list == nullptr){
    cout << "No direct journeys available" << endl;
    return;
  }

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  listOfObjects<TrainInfoPerStation *>* trains_at_stn1 = stationInfo[src_index];

  //We have to print information of direct trains at the source station
  //Hence take the intersection
  final_list = intersections(trains_at_stn1, final_list);
  printStationInfo(final_list);
}
