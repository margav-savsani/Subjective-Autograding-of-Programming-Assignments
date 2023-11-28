#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif
#include <queue>
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class stations{
  public:
  int index;
  listOfObjects<TrainInfoPerStation*>* trains;
  stations(int i,listOfObjects<TrainInfoPerStation*>* t){
    index=i;
    trains=t;
  }
  bool Ispresent(int journey_code){
    listOfObjects<TrainInfoPerStation*>* trainscopy=trains;
    while(trainscopy!=nullptr){
      if(trainscopy->object->journeyCode==journey_code){
        return true;
      }
      trainscopy=trainscopy->next;
    }
    return false;
  }
};

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  int src_index=stnNameToIndex.get(srcStnName)->value;
  int dest_index=stnNameToIndex.get(destStnName)->value;
  listOfObjects<StationConnectionInfo *> *adj_src=adjacency[src_index].toStations;
  listOfObjects<stations*>* queue=new listOfObjects<stations*>(new stations(0,nullptr));
  listOfObjects<stations*>* queuecopy=queue;
  listOfObjects<TrainInfoPerStation *> *directjrnys=nullptr;
  listOfObjects<TrainInfoPerStation *> *directjrnys_copy=nullptr;
  listOfObjects<TrainInfoPerStation *>* src_trains=stationInfo[src_index];
  listOfObjects<TrainInfoPerStation *>* dest_trains=stationInfo[dest_index];
  listOfObjects<TrainInfoPerStation *>* srccopy=src_trains;
  listOfObjects<TrainInfoPerStation *>* destcopy=dest_trains;
  int i=0;
  while(adj_src!=nullptr){
    if(adj_src->object->adjacentStnIndex==dest_index){
      while(srccopy!=nullptr){
        destcopy=dest_trains;
        while(destcopy!=nullptr){
          if(srccopy->object->journeyCode==destcopy->object->journeyCode){
            if(directjrnys==nullptr){
              directjrnys=new listOfObjects<TrainInfoPerStation*>(srccopy->object);
              directjrnys_copy=directjrnys;
            }
            else{
              directjrnys_copy->next=new listOfObjects<TrainInfoPerStation*>(srccopy->object);
              directjrnys_copy=directjrnys_copy->next;
            }
          }
          destcopy=destcopy->next;
        }
        srccopy=srccopy->next;
      }
    }
    else{
      if(i==0){queuecopy->object=new stations(adj_src->object->adjacentStnIndex,adj_src->object->trains);}
      else{
        queuecopy->next=new listOfObjects<stations*>(new stations(adj_src->object->adjacentStnIndex,adj_src->object->trains));
        queuecopy=queuecopy->next;
      }
      i++;
    }
    adj_src=adj_src->next;
  }
  while(queue!=nullptr){
    //take and pop the first element
    stations* curr_node=queue->object;
    listOfObjects<StationConnectionInfo *> *adj_currnode=adjacency[curr_node->index].toStations;
    while(adj_currnode!=nullptr){
      //for a neighbour, search all the adjacency list
      int adj_index=adj_currnode->object->adjacentStnIndex;
      listOfObjects<TrainInfoPerStation*>* adj_trains=adj_currnode->object->trains;
      listOfObjects<TrainInfoPerStation*>* valid_trains=nullptr;
      while(adj_trains!=nullptr){
        //In a adjacency list check if the journeys are their in the list of paths, and if it is the next station of that train
        if(curr_node->Ispresent(adj_trains->object->journeyCode)){
          if(valid_trains==nullptr){
            valid_trains=new listOfObjects<TrainInfoPerStation*>(adj_trains->object);
          }
          else{
            valid_trains->next=new listOfObjects<TrainInfoPerStation*>(adj_trains->object);
            valid_trains=valid_trains->next;
          }
        }
        adj_trains=adj_trains->next;
      }
      if(valid_trains!=nullptr){   
        if(adj_index==dest_index){
          if(directjrnys==nullptr){
            directjrnys=valid_trains;
            directjrnys_copy=directjrnys;
          }
          else{
            directjrnys_copy->next=valid_trains;
            directjrnys_copy = directjrnys_copy->next;
          }
        }     
        listOfObjects<stations*>* a=queue;
        while(a->next!=nullptr){
          a=a->next;
        }
        a->next=new listOfObjects< stations*>(new stations(adj_index,valid_trains));
      }
      adj_currnode=adj_currnode->next;
    }
    queue=queue->next;
  }
  if(directjrnys==nullptr){
    cout<<"No Journeys Available"<<endl;
  }
  else{
      printStationInfo(directjrnys);
  }
}
#endif