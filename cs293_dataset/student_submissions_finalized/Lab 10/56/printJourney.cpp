#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
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

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  return;
}

#endif
