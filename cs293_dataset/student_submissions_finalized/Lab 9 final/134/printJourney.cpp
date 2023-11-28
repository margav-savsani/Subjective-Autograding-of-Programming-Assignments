#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// this is having two members, acts like a dictionary entry
template <typename T1, typename T2> class listOfObjects2 {
 public:
  T1 key;
  T2 val;
  listOfObjects2<T1, T2> *next;

  
  // Constructor
  listOfObjects2(T1 a, T2 b) {key = a; val = b;next = nullptr;}
  
  // Destructor
  ~listOfObjects2() {}
};

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  listOfObjects<TrainInfoPerStation *> *finallist = nullptr; // this two are about 
  listOfObjects<TrainInfoPerStation *> *endoflist = nullptr; // linked list of final answer
  
  listOfObjects2<int, int> *head = nullptr; // these are about
  listOfObjects2<int, int> *tail = nullptr; // queue of BFS
  listOfObjects2<int, int> *queue;          // queue(station index, journey code focousing on)

  int source_index = stnNameToIndex.hashValue(srcStnName);
  while(true){ // finding index by probing
    if(srcStnName == stnNameToIndex.getKeyAtIndex(source_index))
      break;
    source_index = (source_index+1)%DICT_SIZE;
  }
  
  int dest_index = stnNameToIndex.hashValue(destStnName);
  while(true){ // finding index by probing
    if(destStnName == stnNameToIndex.getKeyAtIndex(dest_index))
      break;
    dest_index = (dest_index+1)%DICT_SIZE;
  }

  queue = new listOfObjects2<int, int>(source_index, -1); // initialising the queue with 
  head = tail = queue;                                    // source index and -1 which will be updated to journy code

  if(dest_index == source_index){
    cout << "No direct journeys available\n";
    return;
  }

  while(head != nullptr){
    // UNTILL queue is empty

    int jcode = head->val;

    // traversing through all immediate children of current station
    listOfObjects<StationConnectionInfo *> *curr = adjacency[head->key].toStations;
    while(curr != NULL){
  
      int index_of_this_station = curr->object->adjacentStnIndex;
      // if the BFS is still 1st layer, then add all journies to queue
      if(jcode == -1){
        bool check=false;

        // it can be such that 1st layer BFS can itself have dest station, its being done here
        if(curr->object->adjacentStnIndex == dest_index){ 

          // traversing through all children of source_station or all nodes of BFS
          listOfObjects<TrainInfoPerStation *> *curr_train = curr->object->trains;
          while(curr_train != nullptr){
            
            // this block is just updating finallist by adding curr_train journey as we found the dest_list 
            //******
            if(finallist==nullptr){
              finallist = new listOfObjects<TrainInfoPerStation *>(curr_train->object);
              endoflist = finallist;
              curr_train = curr_train->next;
              continue;
            }
            endoflist->next = new listOfObjects<TrainInfoPerStation *>(curr_train->object);
            endoflist = endoflist->next;
            //*******

            curr_train = curr_train->next; // update curr_train for next iteration
          }
          curr = curr->next; // we continue the curr loop here because we don't to do next computions for this case
          continue;    
        }

        // if adjacent station is not dest_station
        listOfObjects<TrainInfoPerStation *> *curr_train = curr->object->trains;
        while(curr_train != NULL){
          // we add every journey to queue because its 1st BFS layer
          tail->next = new listOfObjects2<int, int>(index_of_this_station, curr_train->object->journeyCode);
          tail = tail->next;
          curr_train = curr_train->next;
        }
        curr = curr->next;
        continue; // we coontinue here to make sure to not compute next code
      }

      bool done=false;
      // if its not first BFS layer but the station is final station
      if(curr->object->adjacentStnIndex == dest_index){

        // iterating through all trains in between two considered stations to find a match of journey code
        listOfObjects<TrainInfoPerStation *> *curr_train = curr->object->trains;        
        while(curr_train != nullptr){
          // if found a match of journey code
          if(jcode == curr_train->object->journeyCode){
            // this block is just updating the finallist as we found the complete journey
            //************
            if(finallist==nullptr){
              finallist = new listOfObjects<TrainInfoPerStation *>(curr_train->object);
              endoflist = finallist;
              done = true;
              break;
            }
            
            endoflist->next = new listOfObjects<TrainInfoPerStation *>(curr_train->object);
            endoflist = endoflist->next;
            //**********
            
            done = true;
            break; // we break out of curr_train loop because we don't need to check on other trains in this sation as we already got a match
          }
        curr_train = curr_train->next; 
        }
        if(done){
          curr = curr->next; // if already found a station  we will go to next node
          continue;
        }
                
      }

      // if not BFS 1st layer not dest station we go through trains
      listOfObjects<TrainInfoPerStation *> *curr_train = curr->object->trains;
      while(curr_train != NULL){
        // update queue if jcodes are same
        if(jcode == curr_train->object->journeyCode){
          tail->next = new listOfObjects2<int, int>(index_of_this_station, jcode);
          tail = tail->next;
          done = true;
          break;
        }
        curr_train = curr_train->next;
      }
      if(done)
        break; // break if done
      curr = curr->next;
    }
    head = head->next;
  }
  if(finallist == nullptr){
  // if final list is empty
    cout << "No direct journeys available\n";
    return;
  }

  while(finallist!=nullptr){
      int jcode = finallist->object->journeyCode;
    listOfObjects<TrainInfoPerStation *> *s = stationInfo[source_index];
    while(s!=nullptr){
      if(s->object->journeyCode == jcode){
        listOfObjects<TrainInfoPerStation *> *k = new listOfObjects<TrainInfoPerStation *>(s->object);
        k->next = nullptr;
        k->prev = nullptr;
        printStationInfo(k);
      }
      s = s->next;
    }
    finallist = finallist->next;
  }

}

#endif
