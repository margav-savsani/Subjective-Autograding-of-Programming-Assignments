#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <queue>
using namespace std;

struct stationNodes{
  int index;
  listOfObjects<TrainInfoPerStation*>* trains;
  stationNodes(int i,listOfObjects<TrainInfoPerStation*>* t){
    index=i;
    trains=t;
  }
  bool present_in(int journey_code){
    listOfObjects<TrainInfoPerStation*>*temp=trains;
    while(temp!=nullptr){
      if(temp->object->journeyCode==journey_code){
        return true;
      }
      temp=temp->next;
    }
    return true;
  }
};

// void Planner::printDirectJourneys(string srcStnName, string destStnName)
// {

//   // insert your code here
  
//   cout << "This function is to be implemented by you." << endl;
//   //create a list of journeys.

//   //Find src and dest indices
//   int* srcIndex=stnNameToIndex.get(srcStnName);
//   int* destIndex=stnNameToIndex.get(destStnName);
//   if(srcIndex==nullptr){
//     cout<<"The source station does not exist, check the station and try again. \n";
//     return;
//   }
//   if(destIndex==nullptr){
//     cout<<"The destination station does not exist, check the station and try again. \n";
//     return;
//   }
//   //curr =src
//   Heap<stationNodes> h;
//   h.insert(StationAdjacency(&adjacency[srcIndex]);
//   StationAdjacencyList* curr=nullptr;
//   //store all the stations of src
//   listOfObjects<TrainInfoPerStation *> *a=stationInfo[srcIndex];
//   TrainInfoPerStation *trains_from_src=a->object;
//   listOfObjects<int> *curr_train=trains_from_src;
//   a=a->next;
//   while(a!=nullptr){
//     curr_train->next=new listOfObjects(a->object);
//     curr_train=curr_train->next;
//     a=a->next;
//   }
//   //-----------------------------------
//   while(true){
//     //check if queue is empty
//     if(h.isEmpty()){
//       break;
//     }
//     //store 1st element in queue in curr
//     curr=h.getMax;
//     h.delMax();
//     //if the curr is dest, then add it to the list of journeys.
//     listOfObjects<StationConnectionInfo *>  *curr_neighbour=curr->fromStations;
//     while(curr_neighbour!=nullptr){
//       //check curr list of trains and check if the train is actually in stations of src
//       StationConnectionInfo *neighbour=curr_neighbour->object;
//       listOfObjects<TrainInfoPerStation *> *neighbour_trains=neighbour->trains;
//       while(neighbour_trains!=nullptr){
//         curr_train=trains_from_src;
//         while(curr_train!=nullptr){
//           if(curr_train==neighbour_trains->object->journeyCode){
//             h.add();
//           }
//           curr_train=curr_train->next;
//         }
//         neighbour_trains=neighbour_trains->next;
//       }
//       //add to priority queue
//       curr_neighbour=curr_neighbour->next;
//     }
//     //delete the top element
//   }
//   // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
//   // for the source station and then we can print it out by invoking
//   // printStationInfo that we had used in Lab 7.
//   // printStationInfo is a private member function of the Planner class
//   // It is declared in planner.h and implemented in planner.cpp  
//   return;
// }

// void Planner::printDirectJourneys(string srcStnName, string destStnName)
// {
//   // insert your code here
//   cout << "This functions is to be implemented by you."<<endl;
//   //create a list of journeys.
//   listOfObjects<int> *all_traversals=nullptr;
//   listOfObjects<int> *temp_all_traversals=nullptr;
//   bool first_filled=false;
//   //Find src and dest indices
//   queue<stationNodes*> h;
//   int srcIndex=stnNameToIndex.get(srcStnName)->value;
//   int destIndex=stnNameToIndex.get(destStnName)->value;
//   //access the source and store the neighbours as neighbour class in a heap, and change the bool matrices
//   StationAdjacencyList source=adjacency[srcIndex];
//   listOfObjects<StationConnectionInfo *> *source_neighbours=source.toStations;
//   while(source_neighbours!=nullptr){  
//     if(source_neighbours->object!=nullptr)
//     {h.push(new stationNodes(source_neighbours->object->adjacentStnIndex,source_neighbours->object->trains));}
//     //traversed[source_neighbours->object->adjacentStnIndex]=true;
//     source_neighbours=source_neighbours->next;
//   }
//   cout<<"hi"<<endl;
//     //iterate
//   while(!h.empty()){
//     //if heap is empty then break
//     //access the top element of heap, and its neighbours through adjascent matrix.
//     stationNodes* curr_station=h.front();
//     h.pop();
//     //iterate through its neighbours
//     listOfObjects<StationConnectionInfo *>* curr_neighbours=adjacency[curr_station->index].toStations;
//     listOfObjects<TrainInfoPerStation *> *curr_neighbour_trains=curr_station->trains;
//     cout<<"hi"<<endl;
//     while(curr_neighbours!=nullptr){
//       int neighbour_index=curr_neighbours->object->adjacentStnIndex;
//       listOfObjects<TrainInfoPerStation *> *neighbour_trains=stationInfo[neighbour_index];
//       listOfObjects<TrainInfoPerStation*>* trains=nullptr;
//       listOfObjects<TrainInfoPerStation*>* trains_stored=nullptr;
//       int index=0;
//       while(neighbour_trains!=nullptr){
//         listOfObjects<TrainInfoPerStation *> *temp_curr_neighbour_trains=neighbour_trains->trains;
//         while(temp_curr_neighbour_trains!=nullptr){
//           if(neighbour_trains->object->journeyCode==temp_curr_neighbour_trains->object->journeyCode&&neighbour_trains->object->stopSeq==temp_curr_neighbour_trains->object->stopSeq+1){
//             if(index==0){
//               trains=new listOfObjects(temp_curr_neighbour_trains->object);
//               trains_stored=trains;
//               trains=trains->next;
//               index++;
//               break;
//             }
//             trains->next=new listOfObjects(temp_curr_neighbour_trains->object);
//             trains=trains->next;
//             break;
//           }
//           temp_curr_neighbour_trains=temp_curr_neighbour_trains->next;
//         }
//         neighbour_trains=neighbour_trains->next;
//       }
//       if(trains_stored==nullptr){
//         break;
//       }
//       if(neighbour_index==destIndex){
//         while(trains_stored!=nullptr){
//           if(!first_filled){
//             temp_all_traversals=new listOfObjects<int>(trains_stored->object->journeyCode);
//             all_traversals=temp_all_traversals;
//             all_traversals=all_traversals->next;
//           }
//           temp_all_traversals->next=new listOfObjects<int>(trains_stored->object->journeyCode);
//           temp_all_traversals=temp_all_traversals->next;
//         }
//         break;
//       }
//       h.push(new stationNodes(neighbour_index,trains_stored));
//       curr_neighbours=curr_neighbours->next;
//       //if the neighbour is destination then add all the journey codes to all traversals and dont add to the heap
//     }
//   } 
//   if(all_traversals==nullptr){
//     cout<<"No Journeys found"<<endl;
//     return;
//   }
//   while(all_traversals!=nullptr){
//     cout<<all_traversals->object<<endl;
//     all_traversals=all_traversals->next;
//   }
//   return;
// }

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  int srcIndex=stnNameToIndex.get(srcStnName)->value;
  int destIndex=stnNameToIndex.get(destStnName)->value;
  listOfObjects<StationConnectionInfo *> *src_neighbours=adjacency[srcIndex].toStations;
  queue<stationNodes*> q;
  listOfObjects<TrainInfoPerStation *> *directjourneys=nullptr;
  listOfObjects<TrainInfoPerStation *> *directjourneys_dummy=nullptr;
  while(src_neighbours!=nullptr){
    q.push(new stationNodes(src_neighbours->object->adjacentStnIndex,src_neighbours->object->trains));
    src_neighbours=src_neighbours->next;
  }
  while(!q.empty()){
    //take and pop the first element
    stationNodes* curr=q.front();
    q.pop();
    listOfObjects<StationConnectionInfo *> *curr_neighbours=adjacency[curr->index].toStations;
    listOfObjects<TrainInfoPerStation*>* trains_leading_to_current=curr->trains;
    while(curr_neighbours!=nullptr){
      //for a neighbour, search all the adjacency list
      int curr_neighbours_index=curr_neighbours->object->adjacentStnIndex;
      listOfObjects<TrainInfoPerStation*>* curr_neighbours_trains=curr_neighbours->object->trains;
      listOfObjects<TrainInfoPerStation*>* valid_trains=nullptr;
      while(curr_neighbours_trains!=nullptr){
        //In a adjacency list check if the journeys are their in the list of paths, and if it is the next station of that train
        if(curr->present_in(curr_neighbours_trains->object->journeyCode)){
          if(valid_trains==nullptr){
            valid_trains=new listOfObjects<TrainInfoPerStation*>(curr_neighbours_trains->object);
          }
          else{
            valid_trains->next=new listOfObjects<TrainInfoPerStation*>(curr_neighbours_trains->object);
            valid_trains=valid_trains->next;
          }
        }
        curr_neighbours_trains=curr_neighbours_trains->next;
      }
      if(valid_trains!=nullptr){   
        if(curr_neighbours_index==destIndex){
          if(directjourneys==nullptr){
            directjourneys=valid_trains;
            directjourneys_dummy=directjourneys;
          }
          else{
            directjourneys_dummy->next=valid_trains;
          }
        }     
        q.push(new stationNodes(curr_neighbours_index,valid_trains));
      }
      curr_neighbours=curr_neighbours->next;
    }
  }
  if(directjourneys==nullptr){
    cout<<"No Journeys Available"<<endl;
  }
  else{
    while(directjourneys!=nullptr){
      printStationInfo(directjourneys);
      cout<<endl;
      directjourneys=directjourneys->next;
    }
  }
}
#endif