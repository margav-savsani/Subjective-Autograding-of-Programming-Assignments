#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;



void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  int start = stnNameToIndex.get(srcStnName)->value; //index of the start station
  int end = stnNameToIndex.get(destStnName)->value;  //index of the end station
  StationAdjacencyList *from_source = new StationAdjacencyList();
  from_source = &adjacency[start]; //the start source
  listOfObjects<StationConnectionInfo*>* from =  from_source->toStations; //stores the to stations from source
  listOfObjects<TrainInfoPerStation *> *dest = nullptr; //setting dest to nullptr initially which stores the info of the direct trains
  listOfObjects<TrainInfoPerStation *> *dest_copy;      //head of the dest
  listOfObjects<StationConnectionInfo*>* adj_source;    //adjacent source 
  while(from!=nullptr){                         //iterating through the adjacent stations of the source
    if(from->object->adjacentStnIndex == end) { //checking if the adjacent station is the destination
      listOfObjects<TrainInfoPerStation*>* Trains1 = from->object->trains; //trains from the corresponding adjacent station
      while(Trains1!=nullptr){ //iterating through the trains from the adjacent index
        if(dest == nullptr){   //initiating the dest
          dest = new listOfObjects<TrainInfoPerStation *>(Trains1->object);
          dest_copy = dest;    //initialising the head of the dest
          Trains1 = Trains1->next;
        }
        else{
          dest->next = new listOfObjects<TrainInfoPerStation*>(Trains1->object);
          dest->next->prev = dest; //setting the prev element
          dest = dest->next;       //updating the tail
          Trains1 = Trains1->next;
        }
      }
      from = from->next;
    }
    else{
      listOfObjects<TrainInfoPerStation*>* Trains2 = from->object->trains; //trains from the adjacent station
      while(Trains2!=nullptr){ //iterating through the trains
        int code = from->object->adjacentStnIndex;//index of the adjacent station
        int jr_code = Trains2->object->journeyCode;//journey code of the train connecting the path
        listOfObjects<int>*indices = new listOfObjects<int>(code);//queue storing the indices of the connected paths with the jr_code
        listOfObjects<int>*indices_tail = indices; //tail of the indices
        while(true){
          
          if(indices==nullptr){ //if we have reached the end of the connecting paths
            break;
          }
          adj_source =adjacency[indices->object].toStations; //to trains from the adjacent station
          if(adj_source==nullptr){   //if there are not any to stations
            indices = indices->next; //updating the queue of indices
            continue;                //continuing the loop if this is the case
          }
          else{
            while(adj_source!=nullptr){ //iterating through the adjacent sttaions
              listOfObjects<TrainInfoPerStation*>* Trains =adj_source->object->trains; //trains from the adjacent station
              while(Trains!=nullptr){                      //iterating through the trains from the adjacent station
                if(Trains->object->journeyCode==jr_code){  //checking if the path connected has a train of journey code jr_code
                  if(adj_source->object->adjacentStnIndex == end){ //checking if the adjacent station is the destination
                    //if yes add it to the dest 
                    if(dest == nullptr){ 
                      dest = new listOfObjects<TrainInfoPerStation *>(Trains->object);
                      dest_copy = dest;
                    }
                    else{
                      dest->next = new listOfObjects<TrainInfoPerStation*>(Trains->object);
                      dest->next->prev = dest;
                      dest = dest->next;
                    } 
                  }
                  //updating the indices i.e, adding the adjacent stations if such a path exists as defined above
                  indices_tail->next = new listOfObjects<int>(adj_source->object->adjacentStnIndex);
                  indices_tail->next->prev = indices_tail;
                  indices_tail = indices_tail->next;
                }
                Trains = Trains->next;
              }

              adj_source=adj_source->next;
            }
            indices = indices->next;
          }
          
        }
        Trains2 = Trains2->next;  
        
      }
      from = from->next;
    }
  }
  if(dest!=nullptr){ //if there is a direct train 
    printStationInfo(dest_copy);
  }
  else{ //if there is no direct train
    cout<<"No direct journeys available"<<endl;
  }
  
  
  return;
}

#endif
// Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp