#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;


// class storing train number and station's index number
class Stat_Train{
  public:
    int train_num;
    int station_num;
    Stat_Train* next;

    Stat_Train(int train, int station)
    {
      train_num = train;
      station_num = station;
      next = nullptr;
    }

};

// class which forms a linked-list based queue for BFS algorithm
class BFS_Queue{
  public:
    Stat_Train* head;
    Stat_Train* tail;
    int N;
    BFS_Queue()
    {
      head = nullptr;
      tail = nullptr;
      N = 0;
    }
    
    // Adding an element at the tail of queue
    void Enqueue(Stat_Train* node)
    {
      if(N == 0)
      {
        head = node;
        tail = node;
      }
      else
      {
        tail->next = node;
        tail = node;
      }
      N++;
    }

    // Deleting the head element of queue
    void Dequeue()
    {
      if(N == 0)
        return;
      else if (N == 1)
      {
        tail = nullptr;
        head = nullptr;
      }
      else
        head = head->next;
      N--;
    }
};


// this function is executed at the start of search for journeys
// BFS_Queue is stacked up with outgoing neighbours of the source stations
// If one of its neigbouring element is the destination itself, it is added to journey_list but not the BFS_queue.
listOfObjects<TrainInfoPerStation *> *start_journey(int start_key, int dest_key, listOfObjects<TrainInfoPerStation *> *&journey_list, BFS_Queue &BQ, StationAdjacencyList* adjacency)
{
  listOfObjects<StationConnectionInfo *> *mid_stations =  adjacency[start_key].toStations;
  while(mid_stations != nullptr)
  {
    listOfObjects<TrainInfoPerStation *> *trains_avail = mid_stations->object->trains;
    while(trains_avail != nullptr)
    {
      if(mid_stations->object->adjacentStnIndex == dest_key)
      {
        listOfObjects<TrainInfoPerStation *> *insert_train = new listOfObjects<TrainInfoPerStation *>(*trains_avail);
        (insert_train)->next = journey_list;
        journey_list = insert_train;
        trains_avail = trains_avail->next;
        continue;
      }
      Stat_Train* ST = new Stat_Train(trains_avail->object->journeyCode, mid_stations->object->adjacentStnIndex);
      BQ.Enqueue(ST);
      trains_avail = trains_avail->next;
    }
    mid_stations = mid_stations->next;
  }
  return journey_list;
}


// This function helps in traversing through the required and valid nodes of graph step-by-step.
// After the first step of adding of neighbours of soure station, enqueueing of new valid nodes is performed.
// If match found then true is returned by funtion
bool continue_search(int station_end, BFS_Queue &BQ, StationAdjacencyList* adjacency)
{
  Stat_Train* ST = BQ.head;
  int train_no = ST->train_num;
  listOfObjects<StationConnectionInfo *> *mid_stations =  adjacency[ST->station_num].toStations;
  while(mid_stations != nullptr)
  {
    listOfObjects<TrainInfoPerStation *> *trains_avail = mid_stations->object->trains;
    while(trains_avail != nullptr)
    {
      if(trains_avail->object->journeyCode == train_no)
      {
        if(mid_stations->object->adjacentStnIndex == station_end)
          return true;
        else
        {
          Stat_Train* new_ST = new Stat_Train(trains_avail->object->journeyCode, mid_stations->object->adjacentStnIndex);
          BQ.Enqueue(new_ST);
        }
        return false;
      }
      trains_avail = trains_avail->next;
    }
    mid_stations = mid_stations->next;
  }
  return false;
}


// if continue_search is returned true the the train is added to journey_list
listOfObjects<TrainInfoPerStation *> *add_journey(int start_stat, listOfObjects<TrainInfoPerStation *> *&journey_list, BFS_Queue &BQ, StationAdjacencyList* adjacency)
{
  int train_no = BQ.head->train_num;
  listOfObjects<StationConnectionInfo *> *mid_stations =  adjacency[start_stat].toStations;
  while(mid_stations != nullptr)
  {
    listOfObjects<TrainInfoPerStation *> *trains_avail = mid_stations->object->trains;
    while(trains_avail != nullptr)
    {
      if(trains_avail->object->journeyCode == train_no)
      {
        listOfObjects<TrainInfoPerStation *> *insert_train = new listOfObjects<TrainInfoPerStation *>(*trains_avail);
        insert_train->next = journey_list;
        journey_list = insert_train;
        return journey_list;
      }
      trains_avail = trains_avail->next;
    }
    mid_stations = mid_stations->next;
  }
  return nullptr;
}



void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  listOfObjects<TrainInfoPerStation *> *journey_list = nullptr;

  // Process to extract index value of dictionary from string
  int start_key = stnNameToIndex.get(srcStnName)->value;
  int dest_key = stnNameToIndex.get(destStnName)->value;
  BFS_Queue BQ;

  journey_list = start_journey(start_key, dest_key, journey_list, BQ, adjacency);
  while(BQ.N != 0)
  {
    bool present = continue_search(dest_key, BQ, adjacency);
    if(present)
      journey_list = add_journey(start_key, journey_list, BQ, adjacency);
    BQ.Dequeue();
  }
  printStationInfo(journey_list);

  return;
}

#endif
