#ifndef PLANNER_H
#include "planner.h"
#endif

#ifnded STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  Entry *temp;
  int source,destination,check=0;
  temp=stnNameToIndex.get(srcStnName);
  if(temp==nullptr){
    cout<<"Invalid Source Station"<<endl;
    return;
  }
  source=temp->value;
  temp=stnNameToIndex.get(destStnName);
  if(temp==nullptr){
    cout<<"Invalid Destination Station"<<endl;
    return;
  }
  destination=temp->value;
  listOfObjects<StationConnectionInfo *> *stn=adjacency[source]->toStations;

  //while loop to cycle through all the stations adjacent to the source station
  while(stn!=nullptr){
    listOfObjects<TrainInfoPerStation *> *trains=stn->object->trains;
    if(stn->object->adjacentStnIndex==destination){
      while(trains!=nullptr){
        check++;
        cout<<"Journey code - "<<trains->object->journeyCode<<endl;
        trains=trains->next;
      }
    }
    else{
      //while loop to cycle through all the trains going from the source station to the adjacent stations
      while(trains!=nullptr){
        int jc=trains->object->journeyCode;
        listOfObjects<int> *stn_ind_visited=new listOfObjects<int>(-1);
        stn_ind_visited->next=stn_ind_visited;
        listOfObjects<int> *stn_ind_to_be_visited=new listOfObjects<int>(-1);
        stn_ind_to_be_visited->next=stn_ind_to_be_visited;
        listOfObjects<StationConnectionInfo *> *stn_at;
        stn_at=stn;
        do{
          while(stn_at!=nullptr){
            
            stn_at=stn_at->next;
          }
        }while(stn_ind_to_be_visited->next==stn_ind_to_be_visited);

        trains=trains->next;
      }
    }
    stn=stn->next;
  }

}
