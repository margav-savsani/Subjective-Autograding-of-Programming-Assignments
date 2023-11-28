#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

static listOfObjects<TrainInfoPerStation*> *unbrokenJourneyList;



void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  // retrieve the source station and destination station indices,
  // so that we can extract the adjacency list items
  int src_stn_index = stnNameToIndex.get(srcStnName)->value;
  int dest_stn_index = stnNameToIndex.get(destStnName)->value;
  

  if(srcStnName==destStnName){
    cout<<"Source and Destination same, try again.";
  }
  

  listOfObjects<int>* indexOfNodes=nullptr ;  // The BFS Queue where each discovered element gets added
  listOfObjects<StationConnectionInfo*>* possibleTrains=nullptr;  // Explained below
  
  
  
  // Add at the last element of the Queue
  listOfObjects<int>* moving_index=nullptr;
  listOfObjects<StationConnectionInfo*>* last = adjacency[src_stn_index].toStations, *moving=nullptr;
  while(last!=nullptr){
    if(indexOfNodes==nullptr){
      indexOfNodes=new listOfObjects<int>(last->object->adjacentStnIndex);
      possibleTrains = new listOfObjects<StationConnectionInfo*>(last->object);
      moving_index=indexOfNodes;
      
      moving = possibleTrains;
      last=last->next;
    }
    else{
      moving_index->next=new listOfObjects<int>(last->object->adjacentStnIndex);
      moving->next = new listOfObjects<StationConnectionInfo*>(last->object);
      moving_index=moving_index->next;
      moving = moving->next;
      last=last->next;
    } 
    
  }
  


  
  /* 
    This list contains all thos trains which are potentially solutions to the problem.
    We initiate the list with only those trains which leave from the source.
    For eg, if A is source and it is connected to B and C by trains 12, 13 and 24, 25 respectively,
    then, indexOfNodes Queue becomes:    B     --     C
    the possibleTrains Queue becomes: (12,13)  --  (24,25)

    When BFS begins checking at B, it only matches trains with numbers 12 or 13 and proceeds.
  */


  listOfObjects<TrainInfoPerStation*>* discoveredPathways=nullptr;
  // At the first step we are interested in knowing the next stations
  while(indexOfNodes!=nullptr && possibleTrains!=nullptr){
    
    // Ignore self cycles through source
    if(indexOfNodes->object==src_stn_index){
      indexOfNodes=indexOfNodes->next;
      possibleTrains=possibleTrains->next;
      continue;
    }
    // If destination found
    if (indexOfNodes->object == dest_stn_index){
      if(discoveredPathways==nullptr){
        
        discoveredPathways = possibleTrains->object->trains;
        
        indexOfNodes=indexOfNodes->next;
        possibleTrains=possibleTrains->next;
      }
      else{
        listOfObjects<TrainInfoPerStation*>* moving_ptr = discoveredPathways;
        while(moving_ptr->next!=nullptr){
          moving_ptr=moving_ptr->next;
        }
        moving_ptr->next=possibleTrains->object->trains;
        
        indexOfNodes=indexOfNodes->next;
        possibleTrains=possibleTrains->next;
        
      }

      

      continue;
    }
    listOfObjects<StationConnectionInfo*>* curr = adjacency[indexOfNodes->object].toStations;
    listOfObjects<TrainInfoPerStation*>* stn = possibleTrains->object->trains;
  
    
    
    while(stn!=nullptr){
      
      // For each station, figure out if the potential jouurney Codes are extending
      // further from here.
      // If yes, we will follow them,
      // else, we scrap them from our list of possibleTrains.
      while(curr!=nullptr){
        StationConnectionInfo* revisedPossibilities = new StationConnectionInfo(curr->object->adjacentStnIndex);

        listOfObjects<TrainInfoPerStation*>*h = curr->object->trains, *j=nullptr;
        while(h!=nullptr){
          
          if (h->object->journeyCode==stn->object->journeyCode){
            if(j==nullptr){
              revisedPossibilities->trains = new listOfObjects<TrainInfoPerStation*>(stn->object);
              j = revisedPossibilities->trains;
            }
            else {
              j->next = new listOfObjects<TrainInfoPerStation*>(stn->object);
              j = j->next;
            }
          }
          
          h = h->next;
        }

        // If a journeyCode from the source seems to extend further,
        // we will follow it. This determines the next layer of the BFS Queue.

        if(revisedPossibilities->trains!=nullptr){
            // Add the new station to Queue
            listOfObjects<int>* moving_index=indexOfNodes;
            listOfObjects<StationConnectionInfo*> *moving = possibleTrains;

            while(moving_index->next!=nullptr && moving->next!=nullptr){
              moving=moving->next;
              moving_index=moving_index->next;
            }

            moving_index->next = new listOfObjects<int>( revisedPossibilities->adjacentStnIndex);
            moving->next = new listOfObjects<StationConnectionInfo*>(revisedPossibilities);
            
          }

          curr = curr->next;
      }
      curr = adjacency[indexOfNodes->object].toStations;
      stn = stn->next;
    } 
    

    indexOfNodes=indexOfNodes->next;
    possibleTrains = possibleTrains->next;
  }
  
  
  //  Check if any output was obtained and print list accordingly
  if(discoveredPathways==nullptr){
    cout<<"No Direct Journeys Available"<<endl;
  }
  else{
    cout<<"List Of Available Trains:"<<endl;
    printStationInfo(discoveredPathways);
  }
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
