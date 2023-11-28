#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#define dll_train listOfObjects<TrainInfoPerStation*>
#define dll_connect listOfObjects<StationConnectionInfo*>

using namespace std;

template<typename T> class Node{
  public:
    T* object;
    Node* next = nullptr;

    Node(T* ob) {object = ob;}
};

template<typename T> class Queue{
  public:
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    int size = 0;
    
    void push(T* val){
      if(size == 0) {head = tail = new Node<T>(val);}
      else {tail -> next = new Node<T>(val); tail = tail -> next;}
      size++;
    }

    void dequeue(){
      if(size == 0) {return;}
      else {
        if (size == 1) {tail = nullptr; head = nullptr;}
        else head = head -> next;
      }
      size--;
    }
};

class TS_Pair{
  public:
    int train_number;
    int station_index;

    TS_Pair(int t_num, int s_in) {train_number = t_num; station_index = s_in;}
};

template<typename T> void insert_in_list(T* to_insert, T* &head_of_list){
  to_insert -> next = head_of_list;
  head_of_list = to_insert;
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  dll_train* journey_list = nullptr;
  Queue<TS_Pair> train_queue;
  int start_index = stnNameToIndex.get(srcStnName)->value;
  int end_index = stnNameToIndex.get(destStnName)->value;

  dll_connect* starting_stations =  adjacency[start_index].toStations;
  while(starting_stations != nullptr){
    dll_train* trains_available = starting_stations -> object -> trains;
    while(trains_available != nullptr){
      if(starting_stations -> object -> adjacentStnIndex == end_index) insert_in_list<dll_train>(new dll_train(*trains_available), journey_list);
      else train_queue.push(new TS_Pair(trains_available -> object -> journeyCode, starting_stations -> object -> adjacentStnIndex));
      trains_available = trains_available -> next;
    }
    starting_stations = starting_stations->next;
  }

  while(train_queue.size != 0){
    dll_connect* intermediate_stations = adjacency[train_queue.head -> object -> station_index].toStations;
    while(intermediate_stations != nullptr){
      dll_train* trains_available = intermediate_stations -> object -> trains;
      while(trains_available != nullptr){
        if(trains_available -> object -> journeyCode == train_queue.head -> object -> train_number){
          if(intermediate_stations -> object -> adjacentStnIndex == end_index) {
            dll_connect* intermediate_stations =  adjacency[start_index].toStations;
            while(intermediate_stations != nullptr){
              dll_train* trains_available = intermediate_stations -> object -> trains;
              while(trains_available != nullptr){
                if(trains_available -> object -> journeyCode == train_queue.head -> object -> train_number) insert_in_list<dll_train>(new dll_train(*trains_available), journey_list);
                trains_available = trains_available -> next;
              }
              intermediate_stations = intermediate_stations -> next;
            }
          }
          else train_queue.push(new TS_Pair(trains_available -> object -> journeyCode, intermediate_stations -> object -> adjacentStnIndex));
          break;
        }
        trains_available = trains_available -> next;
      }
      intermediate_stations = intermediate_stations -> next;
    }
    train_queue.dequeue();
  }
  printStationInfo(journey_list);
}

#endif
