#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  int idx_src = stnNameToIndex.get(srcStnName)->value; // getting the index of both stations
  int idx_dest = stnNameToIndex.get(destStnName)->value;
  int count = 0; // initializing number of queries returned

  listOfObjects<TrainInfoPerStation *> *all_journeys; // will store all valid journeys
  listOfObjects<TrainInfoPerStation *> *currTrain = stationInfo[idx_src]; // stores current train being processed
  

  while(currTrain != nullptr){ // loop over all trains
    
    listOfObjects<TrainInfoPerStation *> *journeys = new listOfObjects<TrainInfoPerStation *>(currTrain->object); // journey currently being processed
    listOfObjects<TrainInfoPerStation *> *currJourneyNode = journeys; // journey node currently being processed
    listOfObjects<StationConnectionInfo *> *currStation = adjacency[idx_src].toStations; // station currently processed
    listOfObjects<TrainInfoPerStation *> *possible_train; // dummy variable to confirm which train leaves from which station
    bool found_journey = false; // checks if valid journey has been found yet
    bool found_start_train=false; // another dummy variable to check which train leaves from which station

    if(currStation == nullptr) break; // no trains leave from source

    while(!found_start_train){ // confirm which station the current train leaves from

      possible_train = currStation->object->trains;

      while(!found_start_train && possible_train != nullptr){

        if(possible_train->object->journeyCode == currTrain->object->journeyCode){
          found_start_train = true;
          break;
        }
        possible_train = possible_train->next;
      }
      if(!found_start_train) currStation = currStation->next;
    }

    currJourneyNode->next = new listOfObjects<TrainInfoPerStation *>(possible_train->object); // add it to journeys
    currJourneyNode = currJourneyNode->next;
  
    while(!found_journey && currStation != nullptr){ // run bfs for each train

      if(currStation->object->adjacentStnIndex == idx_dest){ // if current station is the destination, we are done

        found_journey = true;
        count++;
        journeys->next = currJourneyNode;
        currJourneyNode->prev = journeys;

        if(count == 1){ // add current journey to list of valid journeys
          all_journeys = journeys;
        }
        else{
          all_journeys->prev = currJourneyNode;
          currJourneyNode->next = all_journeys;
          all_journeys = journeys;
        }
        break;
      }
      else{ // checks all adjacent stations and chooses those which the train travels though

        listOfObjects<StationConnectionInfo *> *nextStation = adjacency[currStation->object->adjacentStnIndex].toStations;

        while(nextStation != nullptr){

          listOfObjects<TrainInfoPerStation *> *trains = nextStation->object->trains;
          bool found_train = false;

          while(trains != nullptr){

            if(trains->object->journeyCode == currTrain->object->journeyCode){ // confirm this is the same train as our previoustrain
              found_train = true;
              currJourneyNode->next = new listOfObjects<TrainInfoPerStation *>(trains->object);
              currJourneyNode = currJourneyNode->next;
              break;
            }
            trains = trains->next;
          }
          if(found_train) break;

          nextStation = nextStation->next;
        }
        currStation = nextStation;
      }
    }
    currTrain = currTrain->next;
  }

  if(count == 0){ // no valid journeys detected
    cout<<"No direct journey is possible"<<endl;
  }
  else{ // print all valid journeys, by showing the start and end times, along with the journey codes
    printStationInfo(all_journeys);
  }
}

#endif
