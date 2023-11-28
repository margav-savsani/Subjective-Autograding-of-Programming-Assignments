#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include <queue>
using namespace std;
struct swich{
  int stn_at_switch;
  int prev_journey_code;
  int after_journey_code;
  swich(int stn,int prev,int after){
    stn_at_switch=stn;
    prev_journey_code=prev;
    after_journey_code=after;
  }
};

struct journey{
  TrainInfoPerStation* curr_train;
  listOfObjects<swich*>* switches;
  int number_of_switches=0;
  journey(TrainInfoPerStation* curr,listOfObjects<swich*>* s,int swiches){
    curr_train=curr;
    switches=s;
    number_of_switches=swiches;
  }
  void print(int src,int dest,Dictionary<int> stnNameToIndex){
    listOfObjects<swich*>* temp=switches;
    cout<<"There is a journey from "<<stnNameToIndex.getKeyAtIndex(src);
    if(number_of_switches==0){
      cout<<" to "<<stnNameToIndex.getKeyAtIndex(dest)<<" in train "<<curr_train->journeyCode<<endl;
      return;
    }
    while(temp->next!=nullptr){
      cout<<" to "<<stnNameToIndex.getKeyAtIndex(temp->object->stn_at_switch)<<" in train "<<temp->object->prev_journey_code<<", then from "<<stnNameToIndex.getKeyAtIndex(temp->object->stn_at_switch);
      temp=temp->next;
    }
    cout<<" to "<<stnNameToIndex.getKeyAtIndex(temp->object->stn_at_switch)<<" in train "<<temp->object->prev_journey_code<<", then from "<<stnNameToIndex.getKeyAtIndex(temp->object->stn_at_switch);
    cout<<" to "<<stnNameToIndex.getKeyAtIndex(dest)<<" in train "<<temp->object->after_journey_code<<endl;
  }
};

struct stationNodes{
  int index;
  listOfObjects<journey*>* journeys;
  stationNodes(int i,listOfObjects<journey*>* s){
    index=i;
    journeys=s;
  }
};

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{ 
  int srcIndex=stnNameToIndex.get(srcStnName)->value;
  int destIndex=stnNameToIndex.get(destStnName)->value;
  listOfObjects<StationConnectionInfo *> *src_neighbours=adjacency[srcIndex].toStations;
  queue<stationNodes*> q;
  listOfObjects<journey *> *directjourneys=nullptr;
  listOfObjects<journey *> *directjourneys_dummy=nullptr;
  while(src_neighbours!=nullptr){
    q.push(new stationNodes(src_neighbours->object->adjacentStnIndex,new listOfObjects<journey*>(new journey(src_neighbours->object->trains->object,nullptr,0))));
    src_neighbours=src_neighbours->next;
  }
  while(!q.empty()){
    //take and pop the first element
    stationNodes* curr=q.front();
    q.pop();
    if(adjacency[curr->index].toStations==nullptr){
      continue;
    }
    listOfObjects<StationConnectionInfo *> *curr_neighbours=adjacency[curr->index].toStations;
    listOfObjects<journey*>* trains_leading_to_current=curr->journeys;
    while(curr_neighbours!=nullptr){
      //for a neighbour, search all the adjacency list
      int curr_neighbours_index=curr_neighbours->object->adjacentStnIndex;
      listOfObjects<TrainInfoPerStation*>* curr_neighbours_trains=curr_neighbours->object->trains;
      listOfObjects<journey*>* valid_journeys=nullptr;
      listOfObjects<journey*>* first_valid_journeys=nullptr;
      while(curr_neighbours_trains!=nullptr){
        listOfObjects<journey*>* j=curr->journeys;
        while(j!=nullptr){
          journey* curr_journey=j->object;
          if(curr_neighbours_trains->object->journeyCode==j->object->curr_train->journeyCode){
            if(valid_journeys==nullptr){
              valid_journeys=new listOfObjects<journey*>(new journey((curr_neighbours_trains->object),j->object->switches,j->object->number_of_switches));
              first_valid_journeys=valid_journeys;
            }
            else{
              valid_journeys->next=new listOfObjects<journey*>(new  journey((curr_neighbours_trains->object),j->object->switches,j->object->number_of_switches));
              valid_journeys=valid_journeys->next;
            }
          }
          //------------------------------------------------------------------------------
          else{
            if(j->object->number_of_switches<maxStopOvers && j->object->curr_train->arrTime-curr_neighbours_trains->object->depTime<=maxTransitTime){
              listOfObjects<swich*>* s=(j->object->switches);
              listOfObjects<swich*>* temp=s;
              if(s==nullptr){
                s=new listOfObjects<swich*>(new swich(curr->index,j->object->curr_train->journeyCode,curr_neighbours_trains->object->journeyCode));
                temp=s;
              }
              while(temp->next!=nullptr){
                temp=temp->next;
              }
              temp->next=new listOfObjects<swich*>(new swich(curr->index,j->object->curr_train->journeyCode,curr_neighbours_trains->object->journeyCode));         
              if(valid_journeys==nullptr){
                valid_journeys=new listOfObjects<journey*>(new journey((curr_neighbours_trains->object),s,j->object->number_of_switches+1));
                first_valid_journeys=valid_journeys;              
              }
              else{
                valid_journeys->next=new listOfObjects<journey*>(new journey((curr_neighbours_trains->object),s,j->object->number_of_switches+1));
                valid_journeys=valid_journeys->next;
              }
            }
          }
          j=j->next;
        }
        curr_neighbours_trains=curr_neighbours_trains->next;
      }
      if(valid_journeys!=nullptr){   
        if(curr_neighbours_index==destIndex){
          if(directjourneys==nullptr){
            directjourneys=valid_journeys;
            directjourneys_dummy=directjourneys;
          }
          else{
            directjourneys_dummy->next=valid_journeys;
            directjourneys_dummy=directjourneys_dummy->next;
          }
        }     
        q.push(new stationNodes(curr_neighbours_index,first_valid_journeys));
      }
      curr_neighbours=curr_neighbours->next;
    }
  }
  if(directjourneys==nullptr){
    cout<<"No Journeys Available"<<endl;
  }
  else{
    while(directjourneys!=nullptr){
      directjourneys->object->print(srcIndex,destIndex,stnNameToIndex);
      directjourneys=directjourneys->next;
    }
  }
}
#endif
