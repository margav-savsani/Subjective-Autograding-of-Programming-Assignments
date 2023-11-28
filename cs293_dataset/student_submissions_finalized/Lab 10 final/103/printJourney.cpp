#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

// Structure to store day and time
struct DayTime{
  int day;
  int time;
};

// Function to convert DayTime to an integer
int convertToSTDTime(DayTime time){
  return time.day*24*60 + (time.time/100)*60 + (time.time%100);
}

// Function to calculate time difference (in minutes)
int calcTimeDifference(DayTime startTime, DayTime endTime){
  int st = convertToSTDTime(startTime);
  int et = convertToSTDTime(endTime);

  if(et < st){
    et += 7*24*60;
  }

  return et - st;
}

// Function to check if transit time is within maxTransitTime
bool doesTimingsCheckout(DayTime startTime, DayTime endTime, int maxTransitTime){
  return calcTimeDifference(startTime, endTime) <= maxTransitTime*60;
}


void dfs(StationAdjacencyList adjacency[], listOfObjects<TrainInfoPerStation*> *stationInfo[], Dictionary<int> stnNameToIndex, int JourneyCode, int currStnIdx, DayTime arrivalTimeAtThisStation, int dstStnIdx, int maxStopOvers, int maxTransitTime, string output){
  if(currStnIdx == dstStnIdx){ // If destination station reached
    output += "!!!!!!!!!!!!!!!!!!!!!!\n";
    output += "FINAL STATION REACHED!\n";
    output += "!!!!!!!!!!!!!!!!!!!!!!\n";
    output += "\n\n";
    cout << output;
    return;
  }

  

  listOfObjects<StationConnectionInfo*>* nextStation = adjacency[currStnIdx].toStations; // Look at the adjacent stations for currStation
  while(nextStation != nullptr){ // Traverse the list of adjacent stations
    int nextStationIdx = nextStation->object->adjacentStnIndex; // The station index of the adjacent station under consideration

    listOfObjects<TrainInfoPerStation*>* nextTrain = nextStation->object->trains; // Look at all the trains going to adjacent station under consideration
    while(nextTrain != nullptr){ // Traverse the list of trains going to adjacent station
      TrainInfoPerStation* train = nextTrain->object; // Get the actual train info



      for(int day = 0; day < 7; day++){ // Check which days of the week the train is available on
        if(train->daysOfWeek[day]){ // If train commutes on given day
          DayTime departureTimeFromThisStation = {day, train->depTime}; // Departure time of train from this station
          DayTime arrivalTimeAtNextStation; // Arrival time of train at the adjacent station
          listOfObjects<TrainInfoPerStation*>* trainsHere = stationInfo[nextStationIdx]; // Trains from this station
          while(trainsHere != nullptr){ // Traverse the train
            if(trainsHere->object->journeyCode == train->journeyCode){ // If train is the correct one under consideration
              arrivalTimeAtNextStation.time = trainsHere->object->arrTime;
              break;
            }
            trainsHere = trainsHere->next;
          }
          if(arrivalTimeAtNextStation.time < departureTimeFromThisStation.time){ // Set arrival day at next station
            arrivalTimeAtNextStation.day = departureTimeFromThisStation.day + 1;
          } else{
            arrivalTimeAtNextStation.day = departureTimeFromThisStation.day;
          }
          
          if(train->journeyCode == JourneyCode){ // If continuing on same train
            string newOutput = output;
            newOutput += "----------------------\n";
            newOutput += "Journey Code: " + to_string(train->journeyCode) + "\n";
            newOutput += "Source Station: " + stnNameToIndex.getKeyAtIndex(currStnIdx) + "\n";
            newOutput += "Destination Station: " + stnNameToIndex.getKeyAtIndex(nextStationIdx) + "\n";
            newOutput += "Leaving Source At: " + days[departureTimeFromThisStation.day] + "-" + to_string(departureTimeFromThisStation.time) + "\n";
            newOutput += "Reaching Destination At: " + days[arrivalTimeAtNextStation.day] + "-" + to_string(arrivalTimeAtNextStation.time) + "\n";
            // Continue DFS
            dfs(adjacency, stationInfo, stnNameToIndex, train->journeyCode, nextStationIdx, arrivalTimeAtNextStation, dstStnIdx, maxStopOvers, maxTransitTime, newOutput);
          } else{ // If switching toa different train
            if(maxStopOvers > 0 && doesTimingsCheckout(arrivalTimeAtThisStation, departureTimeFromThisStation, maxTransitTime)){ // If transit permitted
              string newOutput = output;
              newOutput += "++++++++++++++++++++++\n";
              newOutput += "CHANGING TRAINS!\n";
              newOutput += "++++++++++++++++++++++\n";
              newOutput += "----------------------\n";
              newOutput += "Journey Code: " + to_string(train->journeyCode) + "\n";
              newOutput += "Source Station: " + stnNameToIndex.getKeyAtIndex(currStnIdx) + "\n";
              newOutput += "Destination Station: " + stnNameToIndex.getKeyAtIndex(nextStationIdx) + "\n";
              newOutput += "Leaving Source At: " + days[departureTimeFromThisStation.day] + "-" + to_string(departureTimeFromThisStation.time) + "\n";
              newOutput += "Reaching Destination At: " + days[arrivalTimeAtNextStation.day] + "-" + to_string(arrivalTimeAtNextStation.time) + "\n";
              // Continue DFS
              dfs(adjacency, stationInfo, stnNameToIndex, train->journeyCode, nextStationIdx, arrivalTimeAtNextStation, dstStnIdx, maxStopOvers-1, maxTransitTime, newOutput);
            }
          }
        }
      }

      nextTrain = nextTrain->next;
    }

    nextStation = nextStation->next;
  }
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  // Obtain the source station index
  int srcStnIdx = stnNameToIndex.get(srcStnName)->value;
  // Obtain the destination station index
  int dstStnIdx = stnNameToIndex.get(destStnName)->value;

  listOfObjects<StationConnectionInfo*>* nextStation = adjacency[srcStnIdx].toStations; // Look at the nextStationIdxs from source
  while(nextStation != nullptr){  // Traverse the list of adjacent stations
    int nextStationIdx = nextStation->object->adjacentStnIndex; // The station index of the adjancet station under consideration

    listOfObjects<TrainInfoPerStation*>* nextTrain = nextStation->object->trains; // Look at all the trains going to adjacent station under consideration
    while(nextTrain != nullptr){ // Traverse the list of trains going to adjacent station
      TrainInfoPerStation* train = nextTrain->object; // Get the actual train info
      for(int day = 0; day < 7; day++){ // Check which day the train is available in
        if(train->daysOfWeek[day]){ // If train commutes on the given day
          DayTime departureTimeFromThisStation = {day, train->depTime}; // Time when train departs from this station
          DayTime arrivalTimeAtNextStation; // Time when train arrives at adjacent station
          listOfObjects<TrainInfoPerStation*>* trainsHere = stationInfo[nextStationIdx]; // Trains from here
          while(trainsHere != nullptr){ // Traverse the trains
            if(trainsHere->object->journeyCode == train->journeyCode){ // If train is the correct one under consideration
              arrivalTimeAtNextStation.time = trainsHere->object->arrTime;
              break;
            }
            trainsHere = trainsHere->next;
          }
          if(arrivalTimeAtNextStation.time < departureTimeFromThisStation.time){ // Set arrival day at adjacent station
            arrivalTimeAtNextStation.day = departureTimeFromThisStation.day + 1;
          } else{
            arrivalTimeAtNextStation.day = departureTimeFromThisStation.day;
          }

          string output = "----------------------\n";
          output += "Journey Code: " + to_string(train->journeyCode) + "\n";
          output += "Source Station: " + stnNameToIndex.getKeyAtIndex(srcStnIdx) + "\n";
          output += "Destination Station: " + stnNameToIndex.getKeyAtIndex(nextStationIdx) + "\n";
          output += "Leaving Source At: " + days[departureTimeFromThisStation.day] + "-" + to_string(departureTimeFromThisStation.time) + "\n";
          output += "Reaching Destination At: " + days[arrivalTimeAtNextStation.day] + "-" + to_string(arrivalTimeAtNextStation.time) + "\n";
          // Perform DFS
          dfs(adjacency, stationInfo, stnNameToIndex, train->journeyCode, nextStationIdx, arrivalTimeAtNextStation, dstStnIdx, maxStopOvers, maxTransitTime, output); // Go and dfs!
        }
      }

      nextTrain = nextTrain->next;
    }

    nextStation = nextStation->next;
  }
  
  return;
}

#endif
