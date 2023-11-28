#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class Train{
  public:
  int stat, train, number;
  Train* next_train;
  Train(){stat = train = number = 0; next_train = nullptr;}
  Train(int, int, int);
};
Train::Train(int t, int s, int num){
  stat = s; train = t;
  number = num;
  next_train = nullptr;
}

class BFS{
  public:
  Train* head;
  int total_number = 0;
  Train* tail;
  BFS(){head = tail = nullptr;}
  void en_queue(Train* passed_n){
    if(head == nullptr && tail == nullptr){head = tail = passed_n; total_number = 1;}
    else{
      tail->next_train = passed_n;
      tail = passed_n;
      total_number = total_number + 1;
    }
  }
  void de_queue(){
    if(head == nullptr && tail == nullptr) return;
    if(head->next_train == nullptr) head = tail = nullptr;
    else head = head->next_train;
  }
};

bool search_journey(int srcStnIndex, int destStnIndex, StationAdjacencyList* adjacency, BFS &Queue)
{
  int num_t = Queue.head->train, num_st = Queue.head->stat, num_num = Queue.head->number;
  listOfObjects<StationConnectionInfo *> *stat_m =  nullptr;
  listOfObjects<TrainInfoPerStation *> *stat_a;
  stat_m = adjacency[num_st].toStations;
  
  for(int i = 0; stat_m != nullptr; stat_m = stat_m->next){
    if(stat_m != nullptr){
      stat_a = nullptr;
      stat_a = stat_m->object->trains;
    }
    for(int i = 0; stat_a != nullptr; stat_a = stat_a->next){
      int a = stat_a->object->journeyCode, b = stat_m->object->adjacentStnIndex;
      if(a == num_t && b != destStnIndex){
        Train* new_train_data = new Train(a, b, num_num + 10000);
        Queue.en_queue(new_train_data);
      }
      if(a == num_t && b == destStnIndex) return false;
      if(a == num_t) return true;
    }
  }
  return true;
}

listOfObjects<TrainInfoPerStation *> *train_add_journey(int station_s, listOfObjects<TrainInfoPerStation *> *&returned_journey_list, BFS &Queue, StationAdjacencyList* adjacency)
{
  int num_t = Queue.head->train, num_st = Queue.head->stat, num_num = Queue.head->number;
  listOfObjects<StationConnectionInfo *> *stat_m;
  listOfObjects<TrainInfoPerStation *> *stat_a;
  listOfObjects<TrainInfoPerStation *> *train_ins;
  stat_m = adjacency[station_s].toStations;

  for(int i = 0; stat_m != nullptr; stat_m = stat_m->next){
    if(stat_m != nullptr){
      stat_a = nullptr;
      stat_a = stat_m->object->trains;
    }
    for(int i = 0; stat_a != nullptr; stat_a = stat_a->next){
      int a = stat_a->object->journeyCode;
      if(a==num_t)
      {
        train_ins = nullptr;
        train_ins = new listOfObjects<TrainInfoPerStation *>(*stat_a);
        train_ins->next = returned_journey_list; returned_journey_list = train_ins;
        return returned_journey_list;
      }
    }
  }
  return nullptr;
}


void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  Entry<int> *srcStnIndexEntry = stnNameToIndex.get(srcStnName);
  Entry<int> *destStnIndexEntry = stnNameToIndex.get(destStnName);

  if(srcStnIndexEntry == nullptr && destStnIndexEntry == nullptr) return;
  int srcStnIndex = srcStnIndexEntry->value;
  int destStnIndex = destStnIndexEntry->value;

  listOfObjects<TrainInfoPerStation *> *returned_journey_list;
  returned_journey_list = nullptr;

  BFS Queue;
  int store_src_index = srcStnIndex, store_dest_index = destStnIndex;
  
  listOfObjects<StationConnectionInfo *> *stat_m =  adjacency[store_src_index].toStations;
  listOfObjects<TrainInfoPerStation *> *stat_a;
  listOfObjects<TrainInfoPerStation *> *train_ins;
  for(int i = 0; stat_m != nullptr; stat_m = stat_m->next){
    if(stat_m != nullptr){
      stat_a = nullptr;
      stat_a = stat_m->object->trains;
    }
    for(int i = 0; stat_a != nullptr; stat_a = stat_a->next){
      if(stat_m->object->adjacentStnIndex != store_dest_index){
        int a = stat_a->object->journeyCode, b = stat_m->object->adjacentStnIndex;
        Train* new_train_data = new Train(a, b, 10000);
        Queue.en_queue(new_train_data);
      }
      else{
        train_ins = nullptr;
        train_ins = new listOfObjects<TrainInfoPerStation *>(*stat_a);
        train_ins->next = returned_journey_list;
        returned_journey_list = train_ins;
        continue;
      }
    }
  }

  while(Queue.total_number != 0){
    if(search_journey(srcStnIndex, destStnIndex, adjacency, Queue) == false){
      returned_journey_list = train_add_journey(srcStnIndex, returned_journey_list, Queue, adjacency);
    }
    Queue.de_queue();
    Queue.total_number--;
  }
  printStationInfo(returned_journey_list);
  return;
}

#endif
