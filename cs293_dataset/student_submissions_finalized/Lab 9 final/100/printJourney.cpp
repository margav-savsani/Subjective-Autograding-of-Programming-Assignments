#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
//#include <queue>
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

//takes intersection of two lists of trains on the basis of their journey codes
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

//prints all directs trains from station to destination station 
//if there is no such train, prints "No direct journeys available"
void Planner::printDirectJourneys(string srcStnName, string destStnName){
  //stores all direct trains between source station and dest station
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
          else{
            List *adjstn = new List(adj, each_stn->object->journeyCode);
            List *last = list;
            while (last->next != nullptr)
              last = last->next;
            last->next = adjstn;
          }
          each_stn = each_stn->next;
        }
        to_stn = to_stn->next;
      }
      if (list->next == nullptr){ // checking if queue has only one element
        list = nullptr;
      }
      else{ // queue having more than one element
        list = list->next;
        list->prev = nullptr;
      }
    }

    else{ // remaining cases
      listOfObjects<StationConnectionInfo *> *to_stn = adjacency[idx].toStations;
      while (to_stn != nullptr){
        int adj = to_stn->object->adjacentStnIndex;
        listOfObjects<TrainInfoPerStation *> *each_stn = to_stn->object->trains;
        while (each_stn != nullptr){
          if (adj == dest_index && each_stn->object->journeyCode == jcode){
            if (final_list==nullptr)
              final_list = new listOfObjects<TrainInfoPerStation *>(each_stn->object);
            else{
              listOfObjects<TrainInfoPerStation *> *last1 = final_list;
              while (last1->next != nullptr)
                last1 = last1->next;
              last1->next = each_stn;
            }
          }
          else if (each_stn->object->journeyCode == jcode){
            List *adjstn = new List(adj, each_stn->object->journeyCode);
            List *last = list;
            while (last->next != nullptr)
              last = last->next;
            last->next = adjstn;
            // queue->tail->next = adjstn;
            // queue->tail = queue->tail->next;
          }
          each_stn = each_stn->next;
        }
        to_stn = to_stn->next;
      }

      if (list->next == nullptr){
        list = nullptr;
      }
      else{
        list = list->next;
        list->prev = nullptr;
      }
    }
  }

  //if there is no direct train
  if (final_list==nullptr)
    cout << "No direct journeys available" << endl;
  else{
    //taking intersection with all trains that leave from source station so,
    //we get train info at source station
    listOfObjects<TrainInfoPerStation *> *all_src_trains = stationInfo[source_index];
    final_list=intersection(all_src_trains,final_list);
    printStationInfo(final_list);

  }
  return;
}
// printStationInfo that we had used in Lab 7.
// printStationInfo is a private member function of the Planner class
// It is declared in planner.h and implemented in planner.cpp_stn