#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
template <typename T1, typename T2>
class store_pairs
{
public:
  T1 stnindex;
  T2 traininfo;

  store_pairs(T1 a, T2 b)
  {
    stnindex = a;
    traininfo = b;
  }
  store_pairs()
  {
    stnindex = -1;
    traininfo = nullptr;
  }
};

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{


//////////////////////////  FOR DIRECT JOURNEYS (start)  //////////////////////////
listOfObjects<TrainInfoPerStation *> *final_list = nullptr;
  int srcIndex = stnNameToIndex.get(srcStnName)->value;
  int destIndex = stnNameToIndex.get(destStnName)->value;
  listOfObjects<StationConnectionInfo *> *adjacents = adjacency[srcIndex].toStations;
  listOfObjects<StationConnectionInfo *> *CurrentStation = adjacents;
  listOfObjects<StationConnectionInfo *> *CurrentJourneyStation = adjacents;
  // Queue construction
  listOfObjects<store_pairs<int, TrainInfoPerStation *>> *q_head = nullptr;
  listOfObjects<store_pairs<int, TrainInfoPerStation *>> *q_tail = nullptr;
  int q_sz = 0;

  // add adjacents to q
  while(true){
  while (CurrentStation != nullptr)
  {
    listOfObjects<TrainInfoPerStation *> *CurrentJourney = CurrentStation->object->trains;

    while (CurrentJourney != nullptr)
    {
      if (q_head == nullptr)
      {
        store_pairs<int, TrainInfoPerStation *> *new_store_pairs = new store_pairs<int, TrainInfoPerStation *>(CurrentStation->object->adjacentStnIndex, CurrentJourney->object);
        listOfObjects<store_pairs<int, TrainInfoPerStation *>>* elem=new listOfObjects<store_pairs<int, TrainInfoPerStation *>>(*new_store_pairs);
        q_head = elem;
        q_tail = q_head;
      }
      else
      {
        store_pairs<int, TrainInfoPerStation *> *new_store_pairs = new store_pairs<int, TrainInfoPerStation *>(CurrentStation->object->adjacentStnIndex, CurrentJourney->object);
        listOfObjects<store_pairs<int, TrainInfoPerStation *>>* elem=new listOfObjects<store_pairs<int, TrainInfoPerStation *>>(*new_store_pairs);
        q_tail->next = elem;
        q_tail->next->prev = q_tail;
        q_tail = q_tail->next;
      }
      q_sz++;

      CurrentJourney = CurrentJourney->next;
    }

    CurrentStation = CurrentStation->next;
  }
  break;
}
  // BFS travel
while(true){
  while (q_sz > 0)
  {
    // If queue q has only 1 element
    if (q_head->next == nullptr)
    {
      // If q head is destination
      if (q_head->object.stnindex == destIndex)
      {
        bool check1=false;
        listOfObjects<TrainInfoPerStation *> *new_node = new listOfObjects<TrainInfoPerStation *>((q_head->object).traininfo);
        new_node->next = final_list;
        new_node->prev = nullptr;
        check1=true;
        final_list = new_node;
        q_head = nullptr;
        q_tail = nullptr;
        q_sz--;
        if(check1){
           break;
        }
       
      }
      // If q head is not destination
      else
      {
        CurrentStation = adjacency[(q_head->object).stnindex].toStations;
        while (CurrentStation != nullptr)
        {
          listOfObjects<TrainInfoPerStation *> *CurrentJourney = CurrentStation->object->trains;
          bool searched = false;
          while (CurrentJourney != nullptr)
          {
            if (CurrentJourney->object->journeyCode == ((q_head->object).traininfo)->journeyCode)
            {
              bool check2=false;
              store_pairs<int, TrainInfoPerStation *> *new_store_pairs = new store_pairs<int, TrainInfoPerStation *>(CurrentStation->object->adjacentStnIndex, (q_head->object).traininfo);
              listOfObjects<store_pairs<int, TrainInfoPerStation *>>* elem=new listOfObjects<store_pairs<int, TrainInfoPerStation *>>(*new_store_pairs);
              q_tail->next = elem;
              q_tail->next->prev = q_tail;
              q_tail = q_tail->next;
              check2=true;
              q_sz++;
              searched = true;
              if(check2){
                break;
              }
              
            }
            CurrentJourney = CurrentJourney->next;
          }
          if (searched)
          {
            break;
          }
          if(! searched){
            //
          }
          CurrentStation = CurrentStation->next;
          
        }
      }
    }
    // If q is not having 1 element (more than 1 element)
    else if ((q_head->object).stnindex == destIndex)
    {
      listOfObjects<TrainInfoPerStation *> *new_node = new listOfObjects<TrainInfoPerStation *>((q_head->object).traininfo);
      new_node->next = final_list;
      new_node->prev = nullptr;
      final_list = new_node;
    }
    else
    {
      CurrentStation = adjacency[(q_head->object).stnindex].toStations;
      while (CurrentStation != nullptr)
      {
        listOfObjects<TrainInfoPerStation *> *CurrentJourney = CurrentStation->object->trains;
        bool got= false;
        while (CurrentJourney != nullptr)
        {
          if (CurrentJourney->object->journeyCode == ((q_head->object).traininfo)->journeyCode)
          {
            bool check3=false;
            store_pairs<int, TrainInfoPerStation *> *new_store_pairs = new store_pairs<int, TrainInfoPerStation *>(CurrentStation->object->adjacentStnIndex, (q_head->object).traininfo);
            listOfObjects<store_pairs<int, TrainInfoPerStation *>>* elem=new listOfObjects<store_pairs<int, TrainInfoPerStation *>>(*new_store_pairs);
            q_tail->next = elem;
            q_tail->next->prev = q_tail;
            q_tail = q_tail->next;
            check3=true;
            q_sz++;
            got = true;
            if(check3){
              break;
            }
            
          }
          CurrentJourney = CurrentJourney->next;
        }
        if (got)
        {
          break;
        }
        if(! got){
            //
        }
        CurrentStation = CurrentStation->next;
      }
    }
    q_head = q_head->next;
    q_sz--;
    if (q_sz == 0)
    {
      //
    }
  }
  break;
}
if(final_list==NULL){
  cout<<"No direct journeys available"<<endl;
}
else{
  printStationInfo(final_list);
}

//////////////////////////  FOR DIRECT JOURNEYS (finish) //////////////////////////
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
