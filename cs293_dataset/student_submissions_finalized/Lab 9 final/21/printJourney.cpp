#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#include <queue>

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  listOfObjects<TrainInfoPerStation*> *finaltrains =nullptr; // list of final journies from src to dest

  int scrindex = this->stnNameToIndex.get(srcStnName)->value;
  int destindex = this->stnNameToIndex.get(destStnName)->value;

  // dqueue of stations and train used to reach the station
  deque<int> q_stn;
  deque<TrainInfoPerStation *> q_train;
  q_stn.push_back(scrindex);
  q_train.push_back(nullptr);

  // dqueue of already visited station train pair to handle loops
  deque<int> q_stn_visited;
  deque<TrainInfoPerStation *> q_train_visited;

  while(q_stn.size() > 0){
    
    // getting current station and train
    int recent_stn = q_stn.front();
    q_stn.pop_front();
    TrainInfoPerStation * recent_train = q_train.front();
    q_train.pop_front();
    
    // going through all the adjacent stations
    listOfObjects<StationConnectionInfo *> *temp_stnptr =  this->adjacency[recent_stn].toStations; 
    while(temp_stnptr != nullptr){
      
      // going through all trains to an adjacent station from current station
      listOfObjects<TrainInfoPerStation*> *temp_trainptr = temp_stnptr->object->trains;
      while(temp_trainptr != nullptr){

        // when in source station add all the adjacent station, train pairs
        if (recent_train == nullptr){
          q_stn.push_back(temp_stnptr->object->adjacentStnIndex);
          q_train.push_back(temp_trainptr->object);
        }

        // else add a station train pair only if the train is same as current train
        else if (temp_trainptr->object->journeyCode == recent_train->journeyCode  ){

          // don't add if pair already present to avoid loops
          bool push = true;
          for(int i=0; i<q_stn_visited.size(); i++){
            if ( q_train_visited[i] != nullptr && q_stn_visited[i] == temp_stnptr->object->adjacentStnIndex && q_train_visited[i]->journeyCode == temp_trainptr->object->journeyCode ){push=false; break;}
          }
          if (push){
            q_stn.push_back(temp_stnptr->object->adjacentStnIndex);
            q_train.push_back(temp_trainptr->object);
          }

        }
        temp_trainptr = temp_trainptr->next;
      }
      temp_stnptr = temp_stnptr->next;
    }
    // add the current station train pair to visited if not present
    bool push = true;
    for(int i=0; i<q_stn_visited.size(); i++){
      if (q_train_visited[i] != nullptr && q_stn_visited[i] == recent_stn && q_train_visited[i]->journeyCode == recent_train->journeyCode ){push=false;break;}
      }
    if (push){
      q_stn_visited.push_back(recent_stn);
      q_train_visited.push_back(recent_train);
    }
    // add the train/journey to list everytime destination station is reached
    if(recent_stn == destindex && recent_train != nullptr) {
      if (finaltrains == nullptr) finaltrains = new listOfObjects<TrainInfoPerStation*>(recent_train);
      else{
        listOfObjects<TrainInfoPerStation*>* temp = finaltrains;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = new listOfObjects<TrainInfoPerStation*>(recent_train);
        temp->next->prev = temp; 
      }
    }
   }

  //printing the journies between source and destination
  cout<<"Journies from " <<srcStnName<<" to "<<destStnName<<endl<<endl ;
  printStationInfo(finaltrains);
  
  return;
}

#endif
