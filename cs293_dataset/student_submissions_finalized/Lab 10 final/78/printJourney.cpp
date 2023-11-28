#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;


// this class is for storing the entire journey from source station to destination station
// entire journey means only one traversal, this may contain various trains in between.
// this class also maintains the transittime and the total number of halts during the journey
class Journey{
  public:
    // this list stores all the individual journeys in between the net journey from source to destination
    listOfObjects<TrainInfoPerStation *> *alljrnys;
    int transittime;  // stores the total transit time
    int halts;  // stores number of halts between src and dest during this journey

    // constructor without parameters
    Journey(){
      transittime = 0;
      halts = 0;
      alljrnys = nullptr;
    }
    // constructor with parameters
    Journey(listOfObjects<TrainInfoPerStation *> *given, int ttime, int halt){
      transittime = ttime;
      halts = halt;
      alljrnys = given;
    }
    // destructor
    ~Journey(){
      listOfObjects<TrainInfoPerStation *> *currjrny = alljrnys;
      while(currjrny != nullptr){
        listOfObjects<TrainInfoPerStation *> *deleteJrny = currjrny;
        currjrny = currjrny->next;
        delete deleteJrny;
      }
    }
    // updates and returns the transit time 
    int get_transit_time(){
      int total_time = 0;
      while (alljrnys != nullptr){
        total_time += (alljrnys->object->depTime - alljrnys->object->arrTime);
        alljrnys = alljrnys->next;
      }
      this->transittime = total_time;
      return total_time;
    }
    // updates and returns the number of halts
    int get_halts(){
      int total_halts = 0;
      alljrnys = alljrnys->next;
      while (alljrnys->next != nullptr){
        total_halts += 1;
        alljrnys = alljrnys->next;
      }
      this->halts = total_halts;
      return total_halts;
    }
};


// Performing bfs and storing all the possible journeys into a list and 
// then filtering that list according to the given transit time and number of halts constraints to get the required journeys
// planner.h and planner.cpp have been modified (mentioned in assumptions.txt)
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime){
  // insert your code here
  
  // indices of dest and src station found 
  int srcind = stnNameToIndex.get(srcStnName)->value;
  int destind = stnNameToIndex.get(srcStnName)->value;
  Journey * j = new Journey(nullptr, 0, 0);
  // this list - jrnys stores all the journeys from source station yto the destination station
  listOfObjects<Journey *> *jrnys = new listOfObjects<Journey *> (j);
  // stores the adjacent stations of the source station
  listOfObjects<StationConnectionInfo *>* src_to = adjacency[srcind].toStations;
  // dummy list to traverse the entire railway routes
  listOfObjects<StationConnectionInfo *>* dummy_src = src_to;
  // this stores the individual paths collection from src to dest for one way of traversal
  listOfObjects<TrainInfoPerStation*>* path = dummy_src->object->trains;
  path->next = nullptr;
  // a temporary queue/ list maintained to perform bfs
  listOfObjects<TrainInfoPerStation*>* que = path;
  while(que){
    path->object = que->object;
    que->object = que->next->object;
    que->next->prev = nullptr;
    int index = src_to->object->adjacentStnIndex;
    // if the codes of the destination matches with that of the current station then we add that path to the alljrnys of the current journey object 
    if (index == destind){
      jrnys->object->alljrnys = path;
    }
    // traversing all the neighbours of the current station
    while(dummy_src){
      int visited = 0;
      listOfObjects<StationConnectionInfo* >* temp = dummy_src;
      while(temp){
        if (temp == src_to){
          visited = 1;
          break;
        }
        temp = temp->next;
      }
      if (visited == 0){
        listOfObjects<TrainInfoPerStation*>* newpath = path;
        newpath->next->object = dummy_src->object->trains->object;
        que->next = newpath;
      }
      dummy_src = dummy_src->next;
    }
  }
  Journey * j1 = new Journey(nullptr, 0, 0);
  // this list stores the final journeys with given transit time and number of maximum halts constraints 
  listOfObjects<Journey *> *res = new listOfObjects<Journey *> (j1);
  // traversing through the jrnys list and if the transit time of any journey is less than the maxTransitTime 
  // and the number of halts in the journey is less than maxStopOvers then we add that journey to the res list 
  while (jrnys){
    Journey* tempjrny = jrnys->object;
    if(tempjrny->get_transit_time() <= maxTransitTime && tempjrny->get_halts() <= maxStopOvers){
      res->object = tempjrny;
      res = res->next;
    }
    jrnys = jrnys->next;
  }
  // if res list is empty then no such journey possible from src to dest with given constraints
  if(res->object == nullptr){
    cout<<"No direct journeys available\n";
    return;
  }
  // calling the printJourneyInfo station declared in the planner.h file and defined in planner.cpp (by me and mentioned in assumptions.txt) 
  // to print the journeys 
  printJourneyInfo(res);

  //cout << "This function is to be implemented by you." << endl;  
  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp
  return;
}

#endif
