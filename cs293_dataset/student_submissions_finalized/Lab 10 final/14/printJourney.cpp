#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

//utility or helper function
bool BFS(int jcode, int srcidx, int destidx, StationAdjacencyList* adjacency)
{
  //declarations
  listOfObjects<StationConnectionInfo *>* src_to = adjacency[srcidx].toStations;
  listOfObjects<StationConnectionInfo *>* d_src = src_to;
  bool ischoice = false;
  int nxt_idx = 0;


  //base cases
  //train reached dest so it is a direct journey
  if(srcidx == destidx) return true;
  //traversed till end but train didn't reach
  if(srcidx == -1) return false;

  
  while(src_to) //until src_to is not null
  {
    bool fnd = false;
    //one station
    listOfObjects<TrainInfoPerStation*>* from_src = src_to->object->trains;
    while(from_src) //one train
    {
      if(from_src->object->journeyCode == jcode)
      {
        nxt_idx = src_to->object->adjacentStnIndex;
        fnd = true;
        break;
      }
      else from_src = from_src->next;
    }
    if(fnd)
    {
      ischoice=true;
      break;
    }
    else src_to = src_to->next;
  }

  //call recursively to each node
  if(ischoice) return BFS(jcode,nxt_idx,destidx,adjacency);
  else return false;

  return false; //never reaches here
}

void Planner::printDirectJourneys(string srcStnName, string destStnName,int maxStopOvers, int maxTransitTime)
{

  // insert your code here

  // get indices
  int srcidx = stnNameToIndex.get(srcStnName)->value;
  int destidx = stnNameToIndex.get(destStnName)->value;

  //declarations
  //list needed to print direct journeys
  TrainInfoPerStation * d_train = new TrainInfoPerStation(0,0,0,0);
  //res points to the strat of the list 
  listOfObjects<TrainInfoPerStation *>* res = new listOfObjects<TrainInfoPerStation *> (d_train);
  //adjacency list of source
  listOfObjects<StationConnectionInfo *>* src_to = adjacency[srcidx].toStations;
  //dummy variable to traverse
  listOfObjects<StationConnectionInfo *>* d_src = src_to;

  //check all stations
  //go to station
  while(d_src) //until d_src is not null
  {
    //one station
    //take a train and check if it goes upto dest bu BST function
    listOfObjects<TrainInfoPerStation*>* from_src = d_src->object->trains;

    //check all trains
    while(from_src)
    {
      //one train
      int j_code = from_src->object->journeyCode;
      //if it reaches end
      int nxt_idx = d_src->object->adjacentStnIndex;
      if(BFS(j_code, nxt_idx, destidx, adjacency))
      {
        //dummy variable to traverse and modify the list 
        listOfObjects<TrainInfoPerStation*>* d_res = res;
        while(true)
        {
          //add trainInfoPerStation to list
          if(!d_res->next)
          {
            listOfObjects<TrainInfoPerStation*>* help = new listOfObjects<TrainInfoPerStation*>(from_src->object);
            d_res->next = help;
            help->prev = d_res;
            break;
          }
          d_res = d_res->next;
        }
      }
      from_src = from_src->next;
    }
    d_src = d_src->next;
  }

  //print
  if(!res->next)
  {
    //result is empty
    cout<<"No direct journeys available\n";
    return;
  }
  printStationInfo(res->next);

  // cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif