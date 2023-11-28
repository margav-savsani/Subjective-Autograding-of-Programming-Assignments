#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

struct List
{
public:
  int index;
  int code;
  List *next;
  List *prev;
  
  //  Constructor
  List(int indValue, int codeValue)
  {
    index = indValue;
    code = codeValue;
    next = prev = nullptr;
    
  }

  // Destructor
  ~List() { ; }
};

listOfObjects<TrainInfoPerStation *> *intersection(listOfObjects<TrainInfoPerStation *> *train1,listOfObjects<TrainInfoPerStation *> *train2){
  listOfObjects<TrainInfoPerStation *> *final=nullptr,*curr=final;
  
  while(train1!=nullptr){
    listOfObjects<TrainInfoPerStation *> *temp=train2;
    while(temp!=nullptr){
      if(train1->object->journeyCode==temp->object->journeyCode){
        
        if(final==nullptr){
          final=new listOfObjects<TrainInfoPerStation *>(train1->object);
          curr=final;
        }
        else{
          curr->next=new listOfObjects<TrainInfoPerStation *>(train1->object);
          curr=curr->next;
        }
      }
      temp=temp->next;
    }
    train1=train1->next;
  }
  return final;
}
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  listOfObjects<TrainInfoPerStation *> *final_list=nullptr;
  int source_index = stnNameToIndex.get(srcStnName)->value;

  int dest_index = stnNameToIndex.get(destStnName)->value;

  //list to maintain queue
  List *list = new List(source_index, -1);
  while (list != nullptr){
    int idx = list->index;
    int jcode = list->code;

    if (jcode == -1){ // when the adjacent stations of source are added
    // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
    // for the source station and then we can print it out by invoking
      listOfObjects<StationConnectionInfo *> *to_stn = adjacency[idx].toStations;
      while (to_stn != nullptr){
        int adj = to_stn->object->adjacentStnIndex;
        listOfObjects<TrainInfoPerStation *> *each_stn = to_stn->object->trains;
        while (each_stn != nullptr){
          if (adj == dest_index){
            if (final_list==nullptr)
              final_list = new listOfObjects<TrainInfoPerStation *>(each_stn->object);
            else{
              listOfObjects<TrainInfoPerStation *> *last1 = final_list;
              while (last1->next != nullptr)
                last1 = last1->next;
              listOfObjects<TrainInfoPerStation *> *add = new listOfObjects<TrainInfoPerStation *>(each_stn->object);
              last1->next = add;
            }
          }
        }
      }
    }
  }  
  printStationInfo(final_list);
  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  return;
}


#endif
