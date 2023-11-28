#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#include <bits/stdc++.h>
#endif

using namespace std;

class TrainsLeavingEachVertex{//for storing the trains reaching upto my vertex,ie, the current station--a listOgObjects of this class is created to store the trains
  public:
    listOfObjects<TrainInfoPerStation*> *trainsLeaving;
    listOfObjects<TrainInfoPerStation*> *tail_trainsLeaving;
    listOfObjects<listOfObjects<TrainInfoPerStation*>*> *TrainsReachingMe;
    TrainsLeavingEachVertex* prev_vertex;
    int vertexcode;

  TrainsLeavingEachVertex(listOfObjects<TrainInfoPerStation*> *TrainLeavingThisVertex, int vertex,  listOfObjects<listOfObjects<TrainInfoPerStation*>*> *PrevTrainsReachingMe){
    vertexcode = vertex;
    listOfObjects<TrainInfoPerStation *> *temp = TrainLeavingThisVertex;
    while(temp!=nullptr){
      if(trainsLeaving == nullptr){
        trainsLeaving = new listOfObjects<TrainInfoPerStation *>(temp->object);
        tail_trainsLeaving = trainsLeaving;
      }
      else{
        tail_trainsLeaving->next = new listOfObjects<TrainInfoPerStation *>(temp->object);
        tail_trainsLeaving->next->prev = tail_trainsLeaving;
        tail_trainsLeaving = tail_trainsLeaving->next;
      }
      temp = temp->next;
    }
    if(TrainsReachingMe == nullptr){
      TrainsReachingMe = new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(trainsLeaving);
    }
    else{
       listOfObjects<listOfObjects<TrainInfoPerStation*>*> *temp = PrevTrainsReachingMe;
       while(temp!=nullptr){
        listOfObjects<TrainInfoPerStation*> * temp1 = trainsLeaving;
        while(temp1!=nullptr){
            listOfObjects<TrainInfoPerStation*> *temp2 = temp->object;
            while(temp2->next!=nullptr){
              temp2 = temp2->next;
            }
            temp2->next = new listOfObjects<TrainInfoPerStation*>(temp1->object);
            temp2->next->prev = temp2;
            temp2 = temp2->next;
            if(TrainsReachingMe == nullptr){
              TrainsReachingMe = new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(temp2);
            } 
            else{
              TrainsReachingMe->next = new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(temp2);
              TrainsReachingMe->next->prev = TrainsReachingMe;
              TrainsReachingMe = TrainsReachingMe->next;
            }
            temp1 = temp1->next;
        }
        temp = temp->next;
       }
    }

  }
};
vector<TrainInfoPerStation *> find(TrainInfoPerStation *train, TrainInfoPerStation * trainList, int maxTransitTime);
TrainInfoPerStation *convert(TrainInfoPerStation *initialEdges, listOfObjects<TrainInfoPerStation *> *initialStnList, int maxTransitTime);
int interval(TrainInfoPerStation* train1, TrainInfoPerStation* train2);
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{ int counter = maxStopOvers;
  
  if (srcStnName.compare(destStnName) == 0)
  {
    cout << "Source and Destination should be different" << endl;
    return;
  }
  listOfObjects<TrainInfoPerStation *> *journeys = nullptr, *lastElem = nullptr; // will put all journeys in this, and storing the current pointer in it
  vector<int> vertices;                                                          // vertices denote the station indices -- this is also the queue in which pushing and popping occurs
  int index = stnNameToIndex.get(srcStnName)->value;                             // getting index of source station
  int srcStnIndex = index;
  int count = 0;
  vertices.push_back(index); // pushing the source into the queue

  vector<vector<TrainInfoPerStation *>> edges; // egdes denote the trains which connect the two vertices-- it is a list of list of trains as multiple trains can connect two stations


  while (vertices.size() != 0) // while queue is not empty
  { 
    
    if (vertices[0] == stnNameToIndex.get(destStnName)->value) // when head of the queue becomes the destination
    {
      vertices.erase(vertices.begin()); // pop out the first element of the queue ie, pop out destination and continue bfs
      if (index != srcStnIndex)
        edges.erase(edges.begin());
      continue;
    }
    //TrainsLeavingEachVertex *stationVertex = new TrainsLeavingEachVertex(adjacency[index].toStations->object->trains,vertices[0],stationVertex->TrainsReachingMe);
    index = vertices[0];
    listOfObjects<StationConnectionInfo *> *ReachingStations = adjacency[index].toStations;
    listOfObjects<StationConnectionInfo *> *curr = ReachingStations; // cureently holds the first reachingstn
    while (curr != nullptr)
    {
      //cout<<curr->object->trains->object->journeyCode<<endl;
      listOfObjects<TrainInfoPerStation *> *TrainsToCurr = curr->object->trains; // list of trains to each reaching station
      listOfObjects<TrainInfoPerStation *> *temp = TrainsToCurr;
      vector<TrainInfoPerStation *> TrainList;
      while (temp != nullptr) // traversing the entire list of trains
      { 
        
        vector<TrainInfoPerStation *> info;//stores each train which statisfies max transit time
        if (index == srcStnIndex ){//doubt-------------------------------------------------------------how to put this in
          while (TrainsToCurr!=nullptr){
            info.push_back(TrainsToCurr->object);
            TrainsToCurr = TrainsToCurr->next;
          }
        }
        else{
          vector<TrainInfoPerStation*> info1 = find(temp->object, edges[0][edges[0].size()-1], maxTransitTime);
          for(int l = 0;l<info1.size();l++){
            info.push_back(info1[l]);
          }
        }  
        
         // if source station then no checking--push_back every station adjacent to it in the queue,
          // else check whether the train is in the TrainList of the first element of the edge--first element of the edge is the station from which we taking the current train
        for(int i = 0;i<info.size();i++){
          //cout<<info[i]->journeyCode<<endl;
          TrainList.push_back(info[i]);
        }
        
        temp = temp->next;
      }
      
      if (TrainList.size() > 0) // push back elements into queues only if there are trains available
      {
        edges.push_back(TrainList);
        vertices.push_back(curr->object->adjacentStnIndex);
        for(int k =0 ;k<TrainList.size();k++){
          //cout<<TrainList[k]<<endl;
          if(journeys == nullptr){
            journeys = new listOfObjects<TrainInfoPerStation *>(TrainList[k]);
            lastElem = journeys;
          }
          else{
            lastElem->next = new listOfObjects<TrainInfoPerStation *>(TrainList[k]);
            lastElem->next->prev = lastElem;
            lastElem = lastElem->next;
          }
        }

      }
      curr = curr->next;
    }
    vertices.erase(vertices.begin()); // pop first element out of the queue
    if (index != srcStnIndex)
      edges.erase(edges.begin());
  }
  listOfObjects<TrainInfoPerStation *> *mytemp = journeys;
  while(mytemp!=nullptr){
    
    //cout<<mytemp->object->journeyCode<<endl;
    mytemp = mytemp->next;
  }
  if(journeys == nullptr)
  {
    cout << "No direct journeys available" << endl;
    return;
  }

  while(journeys != nullptr)
  {
    printStationInfo(journeys);
    journeys = journeys->next;
  }
  // counter --;
  // if(counter<0)
  //   return;
  
}

vector<TrainInfoPerStation*> find(TrainInfoPerStation *train, TrainInfoPerStation* trainList, int maxTransitTime) // this checks whether train is in trainList
{
  vector<TrainInfoPerStation *> info;
  // for (int i = 0; i < trainList.size(); i++)
  // {

    if (interval(train, trainList) <= maxTransitTime)
      info.push_back(train);

  
  return info;
}

TrainInfoPerStation *convert(TrainInfoPerStation *initialEdges, listOfObjects<TrainInfoPerStation *> *initialStnList, int maxTransitTime)
{ // I initially had trainlist whose arrival and departure
  // were wrt the destination, now it has the arrival and departure times of the source station as was required.
  listOfObjects<TrainInfoPerStation *> *stations = initialStnList;
  while (stations != nullptr)
  {
    if(interval(stations->object, initialEdges) <= maxTransitTime)//pehle ka departure dusre ka arrival
    {
      return stations->object;
    }
    stations = stations->next;
  }
}

int interval(TrainInfoPerStation* train1, TrainInfoPerStation* train2){
  return train1->depTime - train2->arrTime;
}
// Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
// for the source station and then we can print it out by invoking
// printStationInfo that we had used in Lab 7.
// printStationInfo is a private member function of the Planner class
// It is declared in planner.h and implemented in planner.cpp

#endif
