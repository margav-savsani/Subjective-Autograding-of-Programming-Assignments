#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  //My algorithm is as follows
  //According to each train number leaving from srcStn, there will be a graph
  //If the destStn exists in that graph, then running BFS type algorithm will find it
  //If no trains found, print “No direct journeys available”

  // insert your code here
  
  //*************************PSEUDOCODE*************************

  //BFS tyoe algorithm

  //************************MYCODE******************************
  
  //some global type variables
  listOfObjects<TrainInfoPerStation *> *direct_journeys = nullptr;
  int source_index = stnNameToIndex.get(srcStnName)->value;
  int destination_index = stnNameToIndex.get(destStnName)->value;
  bool journey_found = false;

  //Put all the trains leaving from source station in trains_from_source doubly linked list
  listOfObjects<StationConnectionInfo *> *first_level_stations  = adjacency[source_index].toStations;
  listOfObjects<TrainInfoPerStation *> *trains_from_source = nullptr;
  while( first_level_stations != nullptr ){
    listOfObjects<TrainInfoPerStation *> *t_iterator = first_level_stations->object->trains;
    while(t_iterator!=nullptr){
      //add t_iterator to trains_from_source
      if ( trains_from_source == nullptr ){
        trains_from_source = new listOfObjects<TrainInfoPerStation *> (new class TrainInfoPerStation(0,0,0,0));
        *trains_from_source = *t_iterator;
      }
      else{
        trains_from_source->next = new listOfObjects<TrainInfoPerStation *> (new class TrainInfoPerStation(0,0,0,0));
        *(trains_from_source->next) = *t_iterator;
        trains_from_source->next->prev = trains_from_source;
        trains_from_source = trains_from_source->next;
      }
      t_iterator = t_iterator->next;
    }
    first_level_stations = first_level_stations->next;
  }
  if(trains_from_source==nullptr){
    cout << "No direct journeys available" << endl;
    return;
  }
  else{
    while(trains_from_source->prev!=nullptr){
      trains_from_source = trains_from_source->prev;
    }
  }
  //trains_from_source should be containing all the trains leaving from source to first level stations

  //Let's conduct BFS type of algorithm on each of trains_from_source
  while(trains_from_source!=nullptr){

    //0->white, 1->grey, 2->black
    int *color = new int[DICT_SIZE];
    for ( int i = 0 ; i < DICT_SIZE ; i++ ){
      color[i] = 0;
    }
    color[source_index] = 1;
    //Define a queue, initialize it with the source
    listOfObjects<int> *Q = new listOfObjects<int>(source_index);
    listOfObjects<int> *start = Q;
    listOfObjects<int> *end = Q;
    
    //run the loop 
    //Till u find the destination station or
    //Run out of stations

    bool exit_condition_1 = false;
    bool exit_condition_2 = false;
    while(true){
      //check if end element is nullptr, return with exit condition 1
      // check if the end element is destination station, if it is, return with exit condition 2
      // end element in queue, iterate all the to stations in adjacency list
      // add a new grey station, IF it has matching train code and it was white before
      // shift end by one
      if ( start==nullptr){
        exit_condition_1 = true;
        break;
      }

      if ( start->object==destination_index ){
        exit_condition_2 = true;
        break;
      }
      color[start->object]=2;
      //while loop to get all tostations
      listOfObjects<StationConnectionInfo *> *i_stations = adjacency[start->object].toStations;
      while(i_stations!=nullptr){ 
         //while loop to find the matching train
        int adj_index = i_stations->object->adjacentStnIndex;
        listOfObjects<TrainInfoPerStation*> *i_trains = i_stations->object->trains;
        if(color[adj_index]==0){
          while(i_trains!=nullptr){
            if ( (i_trains->object->journeyCode) == (trains_from_source->object->journeyCode)   &&  color[adj_index]==0 ){
              //add this station id to queue
              color[adj_index]=1;
              end->next = new listOfObjects<int>(adj_index);
              end->next->prev = end;
              end = end->next;
            }
            i_trains = i_trains->next;
          }
        }
        i_stations = i_stations->next;
      } 
      start = start->next;
    }


    if(exit_condition_2){
      journey_found = true;
      if (direct_journeys == nullptr ){
        direct_journeys = new listOfObjects<TrainInfoPerStation *>(trains_from_source->object);
        direct_journeys->object = trains_from_source->object;
        direct_journeys->prev = nullptr;
        direct_journeys->next = nullptr;
      }
      else{
        direct_journeys->next = new listOfObjects<TrainInfoPerStation *>(trains_from_source->object);
        direct_journeys->next->prev = direct_journeys;
        direct_journeys = direct_journeys->next;
        direct_journeys->object=trains_from_source->object;
      }
      cout << (direct_journeys->object->journeyCode);
    }
    trains_from_source = trains_from_source->next;
  }

  if (journey_found){
    cout << direct_journeys->object->journeyCode;
  }
  if(journey_found){
    while(direct_journeys->prev!=nullptr){
      direct_journeys = direct_journeys->prev;
    }
    printStationInfo(direct_journeys);
  }
  else{
    cout << "No direct journeys available" << endl;
  }
  //***********************END************************************

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
