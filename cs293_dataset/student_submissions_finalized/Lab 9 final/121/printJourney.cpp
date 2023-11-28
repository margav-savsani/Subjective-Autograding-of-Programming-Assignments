#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

//gives the linked list of common trains of the trains list a and b
listOfObjects<TrainInfoPerStation *> * commonTrains(listOfObjects<TrainInfoPerStation *> *a, listOfObjects<TrainInfoPerStation *> *b){
  //current train of a
  listOfObjects<TrainInfoPerStation *> *curr = a;
  listOfObjects<TrainInfoPerStation *> *common = nullptr;
  listOfObjects<TrainInfoPerStation *> *tailCommon = nullptr;
  while(curr!=nullptr){ //going through every element of a 
    listOfObjects<TrainInfoPerStation *> *currcomp = b;
    while(currcomp != nullptr){  //going through b list for every element of a 
      if(currcomp->object->journeyCode == curr->object->journeyCode){ //found a match for this element of a in b
        if(common == nullptr){ //common list is empty yet
          common = new listOfObjects<TrainInfoPerStation *>(curr->object) ; //create the linked list
          tailCommon = common;
        }
        else{ //linked list is not empty
          tailCommon->next = new listOfObjects<TrainInfoPerStation *>(curr->object); //else just add to the tail
          tailCommon->next->prev = tailCommon;  //and shift the tail
          tailCommon = tailCommon->next;
        }
        //finally this inner while loop can be broken
        break;
      }
      currcomp = currcomp->next;
    }
    curr = curr->next;
  }
  return common;
}
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  
  // cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

  int srcindex = stnNameToIndex.get(srcStnName)->value;   //index of given source station
  int destIndex = stnNameToIndex.get(destStnName)->value; //index of given destination station
  // StationAdjacencyList srcAdjList = adjacency[srcindex];    //stations adjacent to the source station
  listOfObjects<StationConnectionInfo*> * srcConnected = adjacency[srcindex].toStations;  //stations info connected to source
  listOfObjects<StationConnectionInfo*> * currentCon = srcConnected;    //directly connected station that we are currently searching a path from
  if(srcConnected==nullptr) {
    cout<<"No direct journeys available"<<endl;
    return;
  }
  //we need a queue for bfs, can be done using a linked list
  listOfObjects<StationConnectionInfo*> * queue = nullptr;  
  queue = new listOfObjects<StationConnectionInfo*> (currentCon->object); //adding first neighboring station to queue
  listOfObjects<StationConnectionInfo*> *tailqueue = queue;   //rest will be added in the next while loop
  
  //now trains which depart from srcStation are the only useful trains which can be used, hence we should use linked list of that as well
  listOfObjects<TrainInfoPerStation *> *routeTrains = nullptr;
  routeTrains = new listOfObjects<TrainInfoPerStation *> (currentCon->object->trains->object);
  listOfObjects<TrainInfoPerStation *> *tailRoute = routeTrains;
  listOfObjects<TrainInfoPerStation *> *currtrain = currentCon->object->trains->next;
  while(currtrain!=nullptr){
    tailRoute->next = new listOfObjects<TrainInfoPerStation *> (currtrain->object);
    tailRoute->next->prev = tailRoute;
    tailRoute = tailRoute->next;
    
    currtrain = currtrain->next;
  }
  currentCon = currentCon->next;

  while(currentCon!=nullptr){ //adding rest of all the neighbouring stations to the queue
    tailqueue->next = new listOfObjects<StationConnectionInfo*> (currentCon->object);
    tailqueue->next->prev = tailqueue;
    tailqueue = tailqueue->next;
    
    //adding trains to the routeTrains
    listOfObjects<TrainInfoPerStation *> *currtrain = currentCon->object->trains;
    while(currtrain!=nullptr){
      tailRoute->next = new listOfObjects<TrainInfoPerStation *> (currtrain->object);
      tailRoute->next->prev = tailRoute;
      tailRoute = tailRoute->next;
      
      currtrain = currtrain->next;
    }
    // tailRoute->next = new listOfObjects<TrainInfoPerStation *> (currentCon->object->trains->object);
    // tailRoute->next->prev = tailRoute;
    // tailRoute = tailRoute->next;

    currentCon = currentCon->next;
  }
  listOfObjects<TrainInfoPerStation*> * availableTrains = nullptr;
  listOfObjects<TrainInfoPerStation*> * tailAvail= nullptr;
  while(queue!=nullptr){
    //pick the first element and pop from the queue
    //check if it is destination, if yes then see the possible journey codes and add them to available trains
    //if it is not a destination, add it's tostations to the list which have train common with routeTrains
    listOfObjects<StationConnectionInfo*> *currStn = queue; //taking head value
    if(currStn->object->adjacentStnIndex == destIndex){ //if it is destination
      listOfObjects<TrainInfoPerStation*>* possibleTrains = commonTrains(routeTrains, currStn->object->trains);
      listOfObjects<TrainInfoPerStation*> *itr = possibleTrains;
      while(itr!=nullptr){ //adding the trains to available trains
        if(availableTrains==nullptr){ //if it is uninitialized
          availableTrains = new listOfObjects<TrainInfoPerStation*> (possibleTrains->object);
          tailAvail = availableTrains;
        }
        else{ //add this train only if the journey code does not match with existing trains in available list
          listOfObjects<TrainInfoPerStation*>* itrAv = availableTrains;
          bool ispresent= false;
          while(itrAv!=nullptr){ //going through all the available trains
            if(itrAv->object->journeyCode == itr->object->journeyCode){
              ispresent = true;
              break;
            }
            itrAv = itrAv->next;
          }
          if(!ispresent){ //if not present in list, add it to available trains
            tailAvail->next = new listOfObjects<TrainInfoPerStation*> (itr->object);
            tailAvail->next->prev = tailAvail;
            tailAvail = tailAvail->next;
          }
        }
        itr = itr->next;
      }
    }
    else{ 
      //now if the station is not destination, we should add it's adjacent stations with a common train with routeTrains to queue
      listOfObjects<StationConnectionInfo*> * adjStns = adjacency[currStn->object->adjacentStnIndex].toStations;
      listOfObjects<StationConnectionInfo*> * itr = adjStns;
      while(itr!=nullptr){
        listOfObjects<TrainInfoPerStation*> * comTrains = commonTrains(routeTrains, itr->object->trains);
        if(comTrains!=nullptr){
          tailqueue->next = new listOfObjects<StationConnectionInfo*> (itr->object);
          tailqueue->next->prev = tailqueue;
          tailqueue = tailqueue->next;
          comTrains = comTrains->next;
        }
        itr = itr->next;
      }
    }
    queue = queue->next;  //removing head from linked list
    if (queue!=nullptr) queue->prev = nullptr;
  }
  availableTrains = commonTrains(stationInfo[srcindex], availableTrains); 
  if(availableTrains==nullptr){
    cout<<"No direct journeys available"<<endl;
    return;
  }
  printStationInfo(availableTrains);
  return;

}



#endif
