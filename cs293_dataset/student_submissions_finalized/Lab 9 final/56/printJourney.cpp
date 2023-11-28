#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

struct QueueEntry{
  listOfObjects<TrainInfoPerStation*>* journey_infos;  //stores the valid journeys
  int station;    //station id in the dictionary
  QueueEntry(listOfObjects<TrainInfoPerStation*>* journey_infos, int station){
    this->station = station;
    this->journey_infos = journey_infos;
  }
  QueueEntry(){
    journey_infos = nullptr;
  }
};

template <typename T>
class Util_Queue{   //A queue class, used as a utility data structure
  public:
  listOfObjects<T>* queue;   //stores the start of the queue
  int length;   //length of the queue
  listOfObjects<T>* end;   //end pointer of the queue
  Util_Queue(){   //default constructor
    queue = nullptr;  
    length = 0;
    end = nullptr;
  }
  Util_Queue(T entry){
    queue = new listOfObjects<T>(entry);
    length = 1;
    end = queue;
  }
  Util_Queue(listOfObjects<T>* entries){  //construct a queue with a list of entries
    length = 0;
    queue = nullptr;
    end = nullptr;
    if(entries != nullptr){
      listOfObjects<T>* trav = entries;
      while(trav != nullptr){
        this->push(trav->object);
        trav = trav->next;
      }
    }
  }
  void push(T entry){   //the standard push operation on queues
    if(queue != nullptr){
      listOfObjects<T>* elt = new listOfObjects<T>(entry);
      end->next = elt;
      elt->prev = end;
      end = elt;
      length++;
    }
    else{
      queue = new listOfObjects<T>(entry);
      length = 1;
      end = queue;
    }      
  }
  listOfObjects<T>* pop(){   //the standard pop operation on queues
    if(length != 0){
      if(length == 1){
        auto top = queue;
        queue = nullptr;
        length = 0;
        end = nullptr;
        top->prev = nullptr;
        top->next = nullptr;
        return top;
      }
      else{
        auto top = queue;
        listOfObjects<T>* temp = queue->next;         
        queue = temp;
        queue->prev = nullptr;
        length--;
        top->prev = nullptr;
        top->next = nullptr;
        return top;
      }
    }
    else{
      cout << "aborting" << endl;   //something wrong with the program, abort for the meanwhile
      abort();
    }
  }
  bool isEmpty(){   //function to check if the queue is empty
    return (length == 0);
  }
};

bool isEqual(listOfObjects<TrainInfoPerStation*>* t1, listOfObjects<TrainInfoPerStation*>* t2){  //compares two objects by their journey code
  return (t1->object)->journeyCode == (t2->object)->journeyCode;
}

Util_Queue<TrainInfoPerStation*>* intersect(listOfObjects<TrainInfoPerStation*>* infos, listOfObjects<TrainInfoPerStation*>* conn){  //finds the intersection of two lists of train info objects
  Util_Queue<TrainInfoPerStation*>* intersection = new Util_Queue<TrainInfoPerStation*>;
  if(infos == nullptr || conn == nullptr){  //either is null, return null queue
    return intersection;
  }
  //compare elements in one list with the elements of the other list
  listOfObjects<TrainInfoPerStation*>* trav_infos = infos;
  while(trav_infos != nullptr){    
    auto trav_journeys = conn;
    while(trav_journeys != nullptr){
      if(isEqual(trav_infos, trav_journeys)){
        intersection->push(trav_infos->object);        
      }
      trav_journeys = trav_journeys->next;
    }    
    trav_infos = trav_infos->next;
  }
  return intersection;
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)  //iterative BFS like strategy - 
  //Store two quantities per a queue entry - the list of journey codes we should be concerned about and
  //the station id of the station. The list of journey codes will be found by taking intersections over 
  //various parent levels so as to ensure that the journey codes are "valid" journey codes.
{

  // insert your code here

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  int srcIndex = (stnNameToIndex.get(srcStnName))->value;
  Util_Queue<QueueEntry*>* queue = new Util_Queue<QueueEntry*>;   //create the queue
  queue->push(new QueueEntry(nullptr, (stnNameToIndex.get(srcStnName))->value));  //push the src node
  
  Util_Queue<listOfObjects<TrainInfoPerStation*>*>* valid_trains = new Util_Queue<listOfObjects<TrainInfoPerStation*>*>;  //stores all the valid journey codes
  while(!(queue->isEmpty())){
    auto curr_entry = queue->pop();   //pop the top element of the queue
    if(curr_entry->object->station == (stnNameToIndex.get(destStnName))->value){  //the popped entry is the destination
      //cout << "found" << endl;
      valid_trains->push((curr_entry->object)->journey_infos);
    }
    //cout << "at " << stnNameToIndex.getKeyAtIndex((curr_entry->object)->station) << endl;
    QueueEntry* entry = curr_entry->object;
    auto trav = adjacency[entry->station].toStations;  
    
    while(trav != nullptr){      //traverse the toStation list of the current element(popped element)
      //cout << "checking " << stnNameToIndex.getKeyAtIndex((trav->object)->adjacentStnIndex) << endl;
      
      if((curr_entry->object)->station == srcIndex){   //if the current element is the source, all the paths from the source to its
                                                       //adjacent stations are valid
        //cout << "added " << stnNameToIndex.getKeyAtIndex((trav->object)->adjacentStnIndex) << endl;
        queue->push(new QueueEntry(trav->object->trains, (trav->object)->adjacentStnIndex));    
           
      }
      else{  //if it is not the source, then take the intersection of the already existing valid journey codes with
        //the journey codes corresponding to each adjacent node to generate a new set of valid journey codes
        Util_Queue<TrainInfoPerStation*>* intersection = intersect((curr_entry->object)->journey_infos, trav->object->trains);
        if(!(intersection->isEmpty())){
          //cout << "added " << stnNameToIndex.getKeyAtIndex((trav->object)->adjacentStnIndex) << endl;
          queue->push(new QueueEntry(intersection->queue, (trav->object)->adjacentStnIndex));
        }
      }
      
      trav = trav->next;
    }
  }
  auto trav_temp = valid_trains->queue;
  if(trav_temp == nullptr){
    cout << "No direct journeys available" << endl;
  }
  while(trav_temp != nullptr){    //print all the valid journey codes
    auto trav_temp2 = trav_temp->object;
    trav_temp2 = (intersect(stationInfo[srcIndex], trav_temp2))->queue;
    if(trav_temp2 != nullptr){      
      printStationInfo(trav_temp2);
    }
    trav_temp = trav_temp->next;
  }
}


#endif
