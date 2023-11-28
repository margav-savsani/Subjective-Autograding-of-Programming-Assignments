#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

struct BFS_Node{
  int stn_index;
  int j_code;
  // int arrTime = 0;
  // int depTime = 0;
  // bool valid_days[7] = {0};
  BFS_Node(int x = 0, int y = 0){
    stn_index = x;
    j_code = y;
  }
};

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  //stores the valid j_codes
  listOfObjects<int> *valid_j_codes = nullptr;
  
  //values of the stations indices
  int dest_idx = stnNameToIndex.get(destStnName)->value;
  int src_idx = stnNameToIndex.get(srcStnName)->value;
  //source
  BFS_Node src_node(src_idx, -1);
  //queue for nodes to visit
  listOfObjects<BFS_Node> *BFS_queue = new listOfObjects<BFS_Node>(src_node);
  //queue's end
  listOfObjects<BFS_Node> *q_end = BFS_queue;

  while(BFS_queue != nullptr){
    BFS_Node curr = BFS_queue->object; //pick the head
    //traverse the adjacent stations of the current one
    listOfObjects<StationConnectionInfo *> *to_list = adjacency[curr.stn_index].toStations;
    bool found = false; //found a journey with the same code
    while(to_list != nullptr && !found){
      //curr station being checked
      int adj_stn_idx = to_list->object->adjacentStnIndex;
      //trains to that one
      listOfObjects<TrainInfoPerStation *> *trains = to_list->object->trains;
      while(trains != nullptr){
        //for source, add all trains
        if(curr.j_code == -1){
          BFS_Node to_add(adj_stn_idx, trains->object->journeyCode);
          //if the adjacent station is the destination, don't add to queue
          if(adj_stn_idx == dest_idx){
            //add to valid
            listOfObjects<int> *valid_code = new listOfObjects<int>(trains->object->journeyCode);
            valid_code->next = valid_j_codes;
            valid_j_codes = valid_code;
          }
          else{
            //add to the queue
            q_end->next = new listOfObjects<BFS_Node>(to_add);
            q_end = q_end->next;
          }
        }
        else if(trains->object->journeyCode == curr.j_code){
          //if destination found
          if(adj_stn_idx == dest_idx){
            //add to valid
            listOfObjects<int> *valid_code = new listOfObjects<int>(curr.j_code);
            valid_code->next = valid_j_codes;
            valid_j_codes = valid_code;
            found = true;
            break;
          }
          //else, add the curr station and the j_code to the queue
          BFS_Node to_add(adj_stn_idx, curr.j_code);
          q_end->next = new listOfObjects<BFS_Node>(to_add);
          q_end = q_end->next;
          found = true; 
          break;
        }
        trains = trains->next;
      } 
      to_list = to_list->next;
    }
    //remove the examined head node
    BFS_queue = BFS_queue->next;
  }
  listOfObjects<TrainInfoPerStation *> *valids = nullptr;
  //fetch all trains at the source
  listOfObjects<TrainInfoPerStation *> *all = stationInfo[src_idx];
  while(all != nullptr){
    listOfObjects<int> *temp = valid_j_codes;
    while(valid_j_codes != nullptr){
      //if any match with the curr valid j_code, add to print list
      if(all->object->journeyCode == valid_j_codes->object){
        listOfObjects<TrainInfoPerStation *> *to_add = new listOfObjects<TrainInfoPerStation *>(all->object);
        to_add->next = valids;
        valids = to_add;
      }
      valid_j_codes = valid_j_codes->next;
    } 
    valid_j_codes = temp;
    all = all->next;
  }
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  //print the valid object infos
  printStationInfo(valids);
  return;
}

#endif
