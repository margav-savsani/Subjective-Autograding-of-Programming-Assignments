#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

template <typename T1, typename T2> class tuples{
  public:

    T1 stnindex;
    T2 traininfo;
  
  tuples(T1 a, T2 b){
    stnindex = a;
    traininfo = b;
  }
  tuples(){
    stnindex = -1;
    traininfo = nullptr;
  }

  // friend T1 get0();
  // friend T2 get1();

};

// template<typename T1> get0( <typename T1, typename T2> my_tuple ){
//   return my_tuple.stnindex;
// }

// T2 get1( tuples<T1, T2> my_tuple ){
//   return my_tuple.traininfo;
// }

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  listOfObjects<TrainInfoPerStation*>* list = nullptr;
  int srcIndex = stnNameToIndex.get(srcStnName)->value;
  int destIndex= stnNameToIndex.get(destStnName)->value;
  
  listOfObjects<StationConnectionInfo*>* neighbors = adjacency[srcIndex].toStations;
  listOfObjects<StationConnectionInfo*>* currSt = neighbors;
  

  listOfObjects<tuples<int, TrainInfoPerStation*>>* queue_head = nullptr;
  listOfObjects<tuples<int, TrainInfoPerStation*>>* queue_tail = nullptr;
  int queue_size = 0;

  //add neighbors to queue  
  while(currSt != nullptr ){
    listOfObjects<TrainInfoPerStation*>* currjrny = currSt->object->trains;
    
    while(currjrny != nullptr){
      if(queue_head == nullptr){
        tuples<int, TrainInfoPerStation*> * new_tuple = new tuples<int, TrainInfoPerStation*>(currSt->object->adjacentStnIndex,currjrny->object); 
        queue_head = new listOfObjects<tuples<int, TrainInfoPerStation*>>(*new_tuple);
        queue_tail = queue_head;
      }
      else{
        tuples<int, TrainInfoPerStation*>* new_tuple = new tuples<int, TrainInfoPerStation*>(currSt->object->adjacentStnIndex,currjrny->object);
        queue_tail->next = new listOfObjects<tuples<int, TrainInfoPerStation*>>(*new_tuple);
        queue_tail->next->prev = queue_tail;
        queue_tail = queue_tail->next;
      }
      queue_size++;      
    
      currjrny = currjrny->next;
    }

    currSt = currSt->next;
  }

  //do a bfs traversal for determining paths, using the multigraph of journeycodes
  // add them to the final print list
  while(queue_size > 0){
    if(queue_head->next == nullptr){
      if(queue_head->object.stnindex == destIndex){
        listOfObjects<TrainInfoPerStation*>* new_node = new listOfObjects<TrainInfoPerStation*>((queue_head->object).traininfo);
        new_node->next = list;
        new_node->prev = nullptr;
        list = new_node;
        queue_head = nullptr;
        queue_tail = nullptr;
        queue_size--;
        break;
      }
      else{
        currSt = adjacency[(queue_head->object).stnindex].toStations;
        while(currSt != nullptr ){
          listOfObjects<TrainInfoPerStation*>* currjrny = currSt->object->trains;
          bool found =false;
          while(currjrny != nullptr){
            if(currjrny->object->journeyCode == ((queue_head->object).traininfo)->journeyCode){
              tuples<int, TrainInfoPerStation*>* new_tuple = new tuples<int, TrainInfoPerStation*>(currSt->object->adjacentStnIndex,(queue_head->object).traininfo);
            
              queue_tail->next = new listOfObjects<tuples<int, TrainInfoPerStation*>>(*new_tuple);
              queue_tail->next->prev = queue_tail;
              queue_tail = queue_tail->next;
              queue_size++;
              found = true;     
              break;
            }
            currjrny = currjrny->next;
          }
          if(found){break;}
          currSt = currSt->next;
        }
      }

    }  


    else if( (queue_head->object).stnindex == destIndex ){
        listOfObjects<TrainInfoPerStation*>* new_node = new listOfObjects<TrainInfoPerStation*>((queue_head->object).traininfo);
        new_node->next = list;
        new_node->prev = nullptr;
        list = new_node;
        
    }

    else{
      currSt = adjacency[(queue_head->object).stnindex].toStations;
      while(currSt != nullptr ){
        listOfObjects<TrainInfoPerStation*>* currjrny = currSt->object->trains;
        bool found =false;
        while(currjrny != nullptr){
          if(currjrny->object->journeyCode == ((queue_head->object).traininfo)->journeyCode){
            tuples<int, TrainInfoPerStation*>* new_tuple = new tuples<int, TrainInfoPerStation*>(currSt->object->adjacentStnIndex,(queue_head->object).traininfo);
            
            queue_tail->next = new listOfObjects<tuples<int, TrainInfoPerStation*>>(*new_tuple);
            queue_tail->next->prev = queue_tail;
            queue_tail = queue_tail->next;
            queue_size++;
            found = true;     
            break;
          }
          currjrny = currjrny->next;
        }

        if(found){break;}

        currSt = currSt->next;
      }
    }

    queue_head = queue_head->next;
    queue_size--;
    if(queue_size == 0){queue_tail = nullptr;}
  }

  // print the list
  printStationInfo(list);
  
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
