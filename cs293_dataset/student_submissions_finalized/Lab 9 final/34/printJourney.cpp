#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

// it updates the list according to parameter provided.
void update_list(TrainInfoPerStation *train, listOfObjects<TrainInfoPerStation *> *list, listOfObjects<TrainInfoPerStation *> *append){
  while(list->next != nullptr){
    list = list->next;
  }
  if(train != nullptr){
    list->next = new listOfObjects<TrainInfoPerStation*>(train);
    list->next->prev = list;
  }
  else{
    list->next = append;
  }
}
// checks if the given jrnycode is present in the list.
bool isPresent(int JrnyCode, listOfObjects<TrainInfoPerStation *> *list){
  while(list != nullptr){
    if(list->object->journeyCode == JrnyCode)return true;
    list = list->next;
  }
  return false;
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  // insert your code here

  // The following two store the index of srcstn amd destStn.
  int src_hash = stnNameToIndex.get(srcStnName)->value;
  int dest_hash = stnNameToIndex.get(destStnName)->value;
  // To apply BFS on object of type StationConnectionInfo,
  // created first elem of BFS srcStn.
  // It contatins the adjacentindex as srchash
  // all the info of trains that depart from src are stored in trains variable of srcStn.
  StationConnectionInfo* srcStn = new StationConnectionInfo(src_hash);
  // all the info of trains that depart from src are stored in trains variable of srcStn.
  srcStn->trains = stationInfo[src_hash];
  // added the first elem in BFS list.
  listOfObjects<StationConnectionInfo *> *BFS_head = new listOfObjects<StationConnectionInfo *>(srcStn);
  // Tail is used to iterate easily.
  listOfObjects<StationConnectionInfo *> *BFS_tail = BFS_head;
  // final_list contains all info of trains from station srcStn which will reach destStn.
  listOfObjects<TrainInfoPerStation *> *final_list = nullptr;
  // applying BFS.
  while(true){
    // if the head is equal to destStn then add the trains info into final_list and remove the elem.
    if(BFS_head->object->adjacentStnIndex == dest_hash){
      if(final_list == nullptr){
        final_list = BFS_head->object->trains;
      }
      else{
        update_list(nullptr, final_list, BFS_head->object->trains);
      }
      // removing head
      BFS_head = BFS_head->next;
      // if BFS list becomes empty, break the while loop.
      if(BFS_head == nullptr){
        break;
      }
      delete BFS_head->prev;
      BFS_head->prev = nullptr;
    }
    // the below code adds new element to the BFS list.
    // temp stores all the trains starting from srcStn and reaching the BFS_head->stn.
    // listOfObjects<StationConnectionInfo *> *temp = nullptr;
    listOfObjects<StationConnectionInfo *> *iter = adjacency[BFS_head->object->adjacentStnIndex].toStations;
    while(iter != nullptr){
      // append is the next elem to be added into the BFS list.
      StationConnectionInfo* append = new StationConnectionInfo(iter->object->adjacentStnIndex);
      listOfObjects<TrainInfoPerStation *> *trains = nullptr;
      listOfObjects<TrainInfoPerStation *> *trn_avail = BFS_head->object->trains;
      // below code removes all the unwanted trains that dont reach BFS_head->stn.
      while(trn_avail != nullptr){
        if(isPresent(trn_avail->object->journeyCode, iter->object->trains)){
          if(trains == nullptr){
            trains = new listOfObjects<TrainInfoPerStation *>(trn_avail->object);
          }
          else{
            update_list(trn_avail->object, trains, nullptr);
          }
        }
        trn_avail = trn_avail->next;
      }
      // adding trains to the stationconnectioninfo to be added in BFS list.
      append->trains = trains;
      BFS_tail->next = new listOfObjects<StationConnectionInfo *>(append);
      BFS_tail->next->prev = BFS_tail;
      BFS_tail = BFS_tail->next;
      iter = iter->next;
    }
    BFS_head = BFS_head->next;
    if(BFS_head == nullptr){
      break;
    }
    delete BFS_head->prev;
    BFS_head->prev = nullptr;
  }
  // if final_list is empty then print accordingly.
  if(final_list == nullptr){
    cout << "No direct journeys available\n";
    return;
  }
  // printig info.
  printStationInfo(final_list);
  return;
}
