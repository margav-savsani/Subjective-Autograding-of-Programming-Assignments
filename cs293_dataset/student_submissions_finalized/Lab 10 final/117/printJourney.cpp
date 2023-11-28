#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;




class Journey
{
public:
  int stopOvers;
  listOfObjects<TrainInfoPerStation *> *trainsInorder, *endpointer;
  listOfObjects<string> *stationOrder, *stringEndPointer;
  Journey()
  {
    trainsInorder = NULL;
    stopOvers = 0;
  }
  Journey(TrainInfoPerStation *firstTrain, string source)
  {
    trainsInorder = new listOfObjects<TrainInfoPerStation *>(firstTrain);
    endpointer = trainsInorder;
    stationOrder = new listOfObjects<string>(source);
    stringEndPointer = stationOrder;
    stopOvers = 0;
  }
  void addTrain(TrainInfoPerStation *train, string source)
  {
    if (train == nullptr)
      return;
    if (trainsInorder == nullptr)
    {
      trainsInorder = new listOfObjects<TrainInfoPerStation *>(train);
      endpointer = trainsInorder;
      stationOrder = new listOfObjects<string>(source);
      stringEndPointer = stationOrder;
    }
    else
    {
      endpointer->next = new listOfObjects<TrainInfoPerStation *>(train);
      endpointer->next->prev = endpointer;
      endpointer = endpointer->next;
      stringEndPointer->next = new listOfObjects<string>(source);
      stringEndPointer->next->prev = stringEndPointer;
      stringEndPointer = stringEndPointer->next;
      stopOvers++;
    }
  }
};

class PossibleJourneys
{
public:
  string station;
  listOfObjects<Journey *> *journeysTillStation, *endpointer; // Change to class Journeys later on
  PossibleJourneys(string s)
  {
    station = s;
    journeysTillStation = NULL;
  }
  PossibleJourneys() {}
  void addJourney(Journey *journey)
  {
    if (journey == nullptr)
      return;
    if (journeysTillStation == nullptr)
    {
      journeysTillStation = new listOfObjects<Journey *>(journey);
      endpointer = journeysTillStation;
    }
    else
    {
      endpointer->next = new listOfObjects<Journey *>(journey);
      endpointer->next->prev = endpointer;
      endpointer = endpointer->next;
    }
  }
};

bool mynull(bool* days){
  return !(days[0] || days[1] || days[2] || days[3] || days[4] || days[5] || days[6]);
}

void equate(bool* days1, bool* days2){
  for(int i = 0; i < 7; i++){
    days1[i] = days2[i];
  }
}

int shift(bool* days1, bool* days2){// days2 shifted by how many from days1
  for(int i = 0; i < 6; i++){
    bool same = true;
    for(int j = 0; j < 6; j++){
      same = same && (days1[j] == days2[(j+i)%7]);
    }
    if(same) return i;
  }
  return -1;
}

bool* shifti(bool*days, int shift){// shift backward
  bool* shiftedDays = new bool[7];
  for(int i = 0; i < 7; i++){
    shiftedDays[i] = days[(i+shift)%7];
  }
  return shiftedDays;
}

bool myprintStationInfo(listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<string> *stops, string destStnName){
  bool days[7] = {1,1,1,1,1,1,1};
  listOfObjects<TrainInfoPerStation*> *mylist = stnInfoList;
  while(mylist!= nullptr){
    bool possibledays[7];
    int shift;
    for(int i = 0; i < 6; i++){
      days[i] = days[i] && possibledays[i];
    }
  }
  return mynull(days);
}


void printStationOrder(listOfObjects<string> *stations, string destination)
{
  listOfObjects<string> *iterate = stations;
  while (iterate != nullptr)
  {
    cout << iterate->object << "->";
    iterate = iterate->prev;
  }
  cout << destination << endl;
}

Journey *returnElem(Journey *givenJourney, TrainInfoPerStation *train, int maxStopovers, int maxTransitTime, string Station, listOfObjects<TrainInfoPerStation *> *trainsAtStation)
{
  if (givenJourney->trainsInorder->object->journeyCode == train->journeyCode)
    return givenJourney;
  else if (givenJourney->stopOvers < maxStopovers)
  {
    listOfObjects<TrainInfoPerStation *> *currStationn = trainsAtStation;
    int arrTime;
    // bool days[7];
    // bool departureDays[7];
    while (currStationn != nullptr)
    {
      if (currStationn->object->journeyCode == givenJourney->trainsInorder->object->journeyCode)
      {
        arrTime = currStationn->object->arrTime;
        // for (int i = 0; i < 6; i++)
        // {
        //   days[i] = currStationn->object->daysOfWeek[i];
        // }
        cout << endl;
        break;
      }
      currStationn = currStationn->next;
    } // noe check for days
    // if( (train->depTime < arrTime) || (train->depTime-arrTime)==100*maxTransitTime) return nullptr;
    //cout << arrTime << " " << train->depTime << endl;
    // for (int i = 0; i < 6; i++)
    // {
    //   if(train->depTime<train->arrTime){
    //     departureDays[i] = train->daysOfWeek[(i-1)%7];
    //   }
    //   else{
    //     departureDays[i] = train->daysOfWeek[i];
    //   }
    // }// Now I have arrival days in days and departure days in departureDays
    bool allowedDays[7];// Allowed days for arriving train
    if(arrTime < train->depTime){
      if(train->depTime-arrTime>100*maxTransitTime) return nullptr;
      // for(int a = 0; a < 7; a++){
      //   allowedDays[a] = days[a] && departureDays[a];
      //   departureDays[a] = allowedDays[a];
      // }
    }
    else{
      if(train->depTime+2400-arrTime >100*maxTransitTime) return nullptr;
      // for(int b = 0; b < 7; b++){
      //   allowedDays[b] = days[b] && departureDays[(b+1)%7];
      //   departureDays[(b+1)%7] = allowedDays[b];
      // }
    }
    // if(mynull(departureDays)) return nullptr;
    Journey *journey = new Journey(train, Station);
    // equate(journey->trainsInorder->object->daysOfWeek,allowedDays);

    listOfObjects<TrainInfoPerStation *> *iterate = givenJourney->trainsInorder;
    listOfObjects<string> *iterateString = givenJourney->stationOrder;

    while (iterate != nullptr)
    {
      // int myshift = shift(iterate->object->daysOfWeek, train->daysOfWeek);
      // bool* newDays;
      // newDays = new bool[7];
      // newDays = shifti(allowedDays, myshift);
      // for(int i = 0; i < 7; i++){
      //   newDays[i] = newDays[i] && iterate->object->daysOfWeek[i];
      // }
      // if(mynull(newDays)) return nullptr;
      journey->addTrain(iterate->object, iterateString->object);
      iterate = iterate->next;
      iterateString = iterateString->next;
    }
    return journey;
  }
  return nullptr;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  if (srcStnName.compare(destStnName) == 0)
  {
    cout << "Source and Destination Station must be different\n";
    return;
  }
  if(maxTransitTime>24){
    cout << "Please give a maximum waiting time of less than a day. Otherwise perform multiple searches exactly for your stops.";
  }

  bool journeyPossible = false;
  int destIndex = stnNameToIndex.get(destStnName)->value;                                    // destination index
  listOfObjects<PossibleJourneys *> *possibleJourneysReachingStation, *endpointer = nullptr; // queue of station
  int sourceIndex = stnNameToIndex.get(srcStnName)->value;
  PossibleJourneys *source;
  source = new PossibleJourneys(srcStnName);
  possibleJourneysReachingStation = new listOfObjects<PossibleJourneys *>(source);
  endpointer = possibleJourneysReachingStation;

  while (possibleJourneysReachingStation != nullptr)
  {
    string currStation = possibleJourneysReachingStation->object->station;   // store the element in queue in which we are present
    int currStationDictionaryindex = stnNameToIndex.get(currStation)->value; // index of that element
    if (currStationDictionaryindex == destIndex)                             // We reach destination in the queue, no BFS here, just store the trains in out list
    {
      journeyPossible = true;
      listOfObjects<Journey *> *journeysReachingDest = possibleJourneysReachingStation->object->journeysTillStation;
      while (journeysReachingDest != nullptr)
      {
        cout << "Journey Start:\n\n";
        printStationOrder(journeysReachingDest->object->stringEndPointer,destStnName);
        printStationInfo(journeysReachingDest->object->trainsInorder);
        //journeyPossible = journeyPossible || myprintStationInfo(journeysReachingDest->object->trainsInorder,journeysReachingDest->object->stringEndPointer, destStnName);
        cout << "Journey End\n\n";
        journeysReachingDest = journeysReachingDest->next;
      }
      possibleJourneysReachingStation = possibleJourneysReachingStation->next;
    }
    else // Any other station than destination
    {
      listOfObjects<StationConnectionInfo *> *toAdjacentStations = adjacency[currStationDictionaryindex].toStations; // stores the list of all stations which can be reached from our element
      while (toAdjacentStations != NULL)                                                                             // BFS at the node
      {
        PossibleJourneys *reachingQueuedStation;
        reachingQueuedStation = new PossibleJourneys(stnNameToIndex.getKeyAtIndex(toAdjacentStations->object->adjacentStnIndex));

        if (currStation.compare(srcStnName) == 0) // currstation is source station
        {
          listOfObjects<TrainInfoPerStation *> *trains = toAdjacentStations->object->trains; // trains of adjacent stations
          while (trains != NULL)
          {
            Journey *journey = new Journey(trains->object, currStation);
            reachingQueuedStation->addJourney(journey);
            trains = trains->next;
          }
          endpointer->next = new listOfObjects<PossibleJourneys *>(reachingQueuedStation);
          endpointer->next->prev = endpointer;
          endpointer = endpointer->next;
        }
        else // currStation is not source, will have a list of edges that are allowed, i.e ones that have come from source, done everything else similarly
        {

          listOfObjects<TrainInfoPerStation *> *trains = toAdjacentStations->object->trains;
          while (trains != NULL)
          {
            listOfObjects<Journey *> *journeysReaching = possibleJourneysReachingStation->object->journeysTillStation;
            while (journeysReaching != NULL)
            { // check for direct atm

              reachingQueuedStation->addJourney(returnElem(journeysReaching->object, trains->object, maxStopOvers, maxTransitTime, currStation, stationInfo[currStationDictionaryindex]));

              journeysReaching = journeysReaching->next;
            }
            trains = trains->next;
          }
          if (reachingQueuedStation->journeysTillStation != nullptr)
          {
            endpointer->next = new listOfObjects<PossibleJourneys *>(reachingQueuedStation);
            endpointer->next->prev = endpointer;
            endpointer = endpointer->next;
          }
        }

        toAdjacentStations = toAdjacentStations->next;
      }
      possibleJourneysReachingStation = possibleJourneysReachingStation->next;
    }
  }

  if (!journeyPossible)
  {
    cout << "No direct journeys available\n";
  }

  return;
}

// #endif

#endif
