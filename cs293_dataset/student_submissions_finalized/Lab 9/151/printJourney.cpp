#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <queue>
#include <set>
#include <tuple>

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  
  // Final list of journeys to be printed
  set<int> direct_jcodes;
  listOfObjects<TrainInfoPerStation *>* direct_journeys = nullptr;

  // Indexes of source and destination stations
  int srcIndex = stnNameToIndex.getIndex(srcStnName);
  int destIndex = stnNameToIndex.getIndex(destStnName);

  // Queue of TrainInfoPerStation*
  queue< tuple< StationConnectionInfo *, int > > Q;

  // variables used for iterating through lists
  listOfObjects<StationConnectionInfo *> *listOfStations = adjacency[srcIndex].toStations;
  listOfObjects<TrainInfoPerStation *> *listOfTrains = nullptr;

  // initial adding of journeys to the queue
  while(listOfStations !=  nullptr){

    listOfTrains = listOfStations->object->trains;

    while(listOfTrains != nullptr){
      Q.push(make_tuple(listOfStations->object, listOfTrains->object->journeyCode));
      listOfTrains = listOfTrains->next;
    }
    
    listOfStations = listOfStations->next;
  }
  
  // processing of the queue
  while(!Q.empty()){
    // front element of queue is taken
    auto currConn = Q.front();
    
    listOfTrains = get<0>(currConn)->trains;
    bool flag = false;

    // if the journey code is found in the to-journeys of the station,
    // then we search the adjacent stations of the current station
    while(listOfTrains != nullptr && !flag){
      if(get<1>(currConn) == (listOfTrains->object->journeyCode)){
        flag = true;
      }
      listOfTrains = listOfTrains->next;
    }
    
    // if journey code wasnt found, then simply remove element from queue
    if(!flag){
      Q.pop();
      continue;
    }

    listOfStations = adjacency[get<0>(currConn)->adjacentStnIndex].toStations;

    while(listOfStations != nullptr){
  
      // if station is the destination, then the journey code is noted
      if(listOfStations->object->adjacentStnIndex == destIndex){
        listOfObjects<StationConnectionInfo *> *finalList =  adjacency[destIndex].fromStations;
        
        while(finalList != nullptr){
          listOfTrains = finalList->object->trains;
          while(listOfTrains != nullptr){
            if(listOfTrains->object->journeyCode == get<1>(currConn)){
              direct_jcodes.insert(get<1>(currConn));
            }
            listOfTrains = listOfTrains->next;
          }
          finalList = finalList->next;
        }
      }

      // else, the adjacent stations are pushed into the queue
      else{
        Q.push(make_tuple(listOfStations->object, get<1>(currConn)));
      }

      listOfStations = listOfStations->next;

    }

    Q.pop();

  }


  // finds the journey, when given journey code,
  // and adds it to the direct_journeys list
  for(auto i = direct_jcodes.begin(); i != direct_jcodes.end(); i++){
    auto currJourney = stationInfo[srcIndex];
    auto curr = direct_journeys;
    while(currJourney != nullptr){
      if(currJourney->object->journeyCode == *i){
        if(curr == nullptr){
          direct_journeys = new listOfObjects<TrainInfoPerStation *>(currJourney->object);
          break;
        } else {
          while(curr->next != nullptr){
            curr = curr->next;
          }
          curr->next = new listOfObjects<TrainInfoPerStation *>(currJourney->object);
        }
      }
      currJourney = currJourney->next;
    }
  }

  printStationInfo(direct_journeys);

  // if no direct journeys available, print error msg
  if(direct_journeys == nullptr){
    cout << "\n\nNo Direct Journeys available" << endl;
  }

}

#endif
