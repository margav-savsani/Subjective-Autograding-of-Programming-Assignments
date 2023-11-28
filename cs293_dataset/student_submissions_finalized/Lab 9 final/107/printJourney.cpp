#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

typedef listOfObjects<TrainInfoPerStation*> TIPS;
typedef listOfObjects<StationConnectionInfo*> SCI;


void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  // Get entry of source station in Dictionary
  Entry<int>* srcIndex= stnNameToIndex.get(srcStnName);
  // Get entry of destination station in Dictionary
  Entry<int>* destIndex= stnNameToIndex.get(destStnName);

  // Either of the station not in dictionary
  if(srcIndex==nullptr || destIndex==nullptr)
  {
    cout<<"No direct journeys available"<<endl;
    return;
  }

  // Get adjacency List for source station
  SCI *toStns= adjacency[srcIndex->value].toStations;
  // If no trains from source sation
  if(toStns==nullptr)
  {
    cout<<"No direct journeys available"<<endl;
    return;
  }


  // To store list of direct trains from source to destination
  SCI *dirTrainsStart=nullptr;  // Pointer to start
  SCI *dirTrainsEnd=nullptr;  // Pointer to end

  // Queue for BFS
  SCI *queueStart=nullptr;  // Queue Start
  SCI *queueEnd=nullptr;  // Queue End

  // Adding all trains passing through or starting at source station to queue

  // Iterator for adjacent stations
  SCI *adjToSrc= toStns;
  while(adjToSrc!=nullptr)
  {
    // Iterator for all the trains to adjToSrc
    TIPS *trainFromSrc=adjToSrc->object->trains;
    while(trainFromSrc!=nullptr)
    {
      // Add this train with next stop's index in dictionary
      StationConnectionInfo *newEntry=new StationConnectionInfo(adjToSrc->object->adjacentStnIndex);
      newEntry->trains=new TIPS(trainFromSrc->object);
      SCI *listnewEntry=new SCI(newEntry);
      if(queueStart==nullptr) // Queue is empty so add at the start
      {
        queueStart=listnewEntry;
        queueEnd=queueStart;
      }
      else  // Queue is not empty so add next to the end
      {
        queueEnd->next=listnewEntry;
        listnewEntry->prev=queueEnd;
        queueEnd=listnewEntry;
      }
      trainFromSrc=trainFromSrc->next;
    }
    adjToSrc=adjToSrc->next;
  }

  //////////////////////////////////////// Do BFS ////////////////////////////////////////
  // Three cases are possible for head of the queue:
  // Case 1: It's train ends at destination, so put it into list of dirTrains and remove it
  // Case 2: It's train ends at some other location with deptTime=-1, so remove it 
  // Case 3: Else change the adjacentStnIndex to next station and update train's specifications
  while(queueStart!=nullptr)
  {
    /////////////////////// Case 1 ///////////////////////
    if(queueStart->object->adjacentStnIndex==destIndex->value)
    {
      // Add this train to list of dirTrains
      SCI *newEntry= new SCI(queueStart->object);
      if(dirTrainsStart==nullptr) // List is empty so add at the dirTrainsStart
      {
        dirTrainsStart=newEntry;
        dirTrainsEnd=dirTrainsStart;
      }
      else  // List is not empty so add to next of dirTrainsEnd
      {
        dirTrainsEnd->next=newEntry;
        newEntry->prev=dirTrainsEnd;
        dirTrainsEnd=newEntry;
      }
    }
    /////////////////////// Case 3 ///////////////////////
    else if(queueStart->object->trains->object->depTime!=-1)
    {
      // Add updated Train to end of the queue
      StationConnectionInfo *nextStn= new StationConnectionInfo(queueStart->object->adjacentStnIndex);
      SCI *toStns= adjacency[nextStn->adjacentStnIndex].toStations;
      bool notfound=true; // If Train found
      // Find train
      while(toStns!=nullptr)
      {
        TIPS *trainFromStn=toStns->object->trains;
        while(trainFromStn!=nullptr)
        {
          if(trainFromStn->object->journeyCode == queueStart->object->trains->object->journeyCode)
          {
            // Found it, so update information
            notfound=false;
            nextStn->adjacentStnIndex=toStns->object->adjacentStnIndex;
            nextStn->trains=new TIPS(trainFromStn->object);
            break;
          }
          trainFromStn=trainFromStn->next;
        }
        if(!notfound) // Found, so no need to process further
          break;
        toStns=toStns->next;        
      }
      // Add to the end of queue
      SCI *newEntry= new SCI(nextStn);
      queueEnd->next=newEntry;
      newEntry->prev=queueEnd;
      queueEnd=newEntry;
    }
    // Delete head of the queue
    if(queueStart->next!=nullptr)
    {
      // So after deleting element, queue still has atleast one element
      queueStart=queueStart->next;
      delete queueStart->prev;
      queueStart->prev=nullptr;
    }
    else
    {
      // This is last element in the queue
      delete queueStart;
      queueStart=nullptr;
    }
  }


  // Make listOfObjects<TrainInfoPerStation *>
  // for the source station and then print it it out by invoking printStationInfo

  // All trains from source
  TIPS* fromSource= stationInfo[srcIndex->value];

  // Direct trains from Source
  TIPS* directTrainStart= nullptr;  // Start of list
  TIPS* directTrainEnd= nullptr;  // End of list
  SCI* dirTrainsIterator= dirTrainsStart; // Iterator for dirTrains
  while (dirTrainsIterator!=nullptr)
  {
    // Matched Train
    if(fromSource->object->journeyCode==dirTrainsIterator->object->trains->object->journeyCode)
    {
      TIPS *directAdd=new TIPS(fromSource->object);
      if(directTrainStart==nullptr) // List is empty so add at the directTrainStart
      {
        directTrainStart=directAdd;
        directTrainEnd=directTrainStart;
      }
      else  // List is not empty so add to next of the directTrainEnd
      {
        directTrainEnd->next=directAdd;
        directAdd->prev=directTrainEnd;
        directTrainEnd=directAdd;
      }
      dirTrainsIterator=dirTrainsIterator->next;
      fromSource=stationInfo[srcIndex->value];  // Again look through all trains from source
      continue;
    }
  fromSource=fromSource->next;
  }
  
  // If no direct trains possible
  if(directTrainStart==nullptr)
  {
    cout<<"No direct journeys available"<<endl;
    return;
  }
  // Print all direct journeys
  printStationInfo(directTrainStart);

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
