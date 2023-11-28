#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define BLUE "\033[34m"

using namespace std;

struct Journey
{
  int journeyCode; // same as train number
  int startStation;
  int endStation;
  int reachTime;
  int boardTime;
  int reachDay;
  int boardDay;
  int currentStops;

  Journey()
  {
    journeyCode = startStation = endStation = reachTime = boardTime = reachDay = boardDay = -999;
    currentStops = 0;
  }
};

int getDayFromOneHot(bool daysOfWeek[7])
{
  for (int i = 0; i < 7; i++)
    if (daysOfWeek[i] == 1)
      return i;
  return -1; // should never reach here. Just for sanity check
}


bool canTakeTrain(TrainInfoPerStation train,
                  listOfObjects<Journey> *journeyList,
                  int maxTransitTime, int maxStopOvers)
{

  Journey lastJourney = journeyList->object;
  float deltaTime = (lastJourney.reachTime / 100.0 - train.arrTime / 100.0 + abs(lastJourney.reachDay - getDayFromOneHot(train.daysOfWeek)) * 24);

  if (deltaTime <= maxTransitTime &&
      (lastJourney.journeyCode == train.journeyCode || lastJourney.currentStops + 1 <= maxStopOvers))
    return true;

  return false;
}

void printJourneys(listOfObjects<Journey> *journeyList, Dictionary<int> stnNameToIndex)
{
  listOfObjects<Journey> *ptr = journeyList;
  while (ptr->prev != nullptr)
    ptr = ptr->prev;

  cout << "_____________________________________________________________________________________________" << endl;
  while (ptr != nullptr)
  {
    cout << RED << "JourneyCode: " << RESET << ptr->object.journeyCode;
    cout << endl;
    cout << BLUE << "Start Station: " << RESET << stnNameToIndex.getKeyAtIndex(ptr->object.startStation) << " ";
    cout << BLUE << "End Station: " << RESET << stnNameToIndex.getKeyAtIndex(ptr->object.endStation);
    cout << endl;
    cout << GREEN << "Start Day: " << RESET << ptr->object.boardDay << " ";
    cout << GREEN << "Start Time: " << RESET << ptr->object.boardTime;
    cout << endl;
    cout << GREEN << "End Day: " << RESET << ptr->object.reachDay << " ";
    cout << GREEN << "End Time: " << RESET << ptr->object.reachTime;
    cout << endl;
    ptr = ptr->next;
  }
  cout << "_____________________________________________________________________________________________" << endl;
}

listOfObjects<TrainInfoPerStation *> *expandTrainsList(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  listOfObjects<TrainInfoPerStation *> *currList, *expandedList;
  TrainInfoPerStation *currInfo;
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

  // Expanding information in stnInfoList to get a list of train info
  // in which each element of the list refers to a single day of the
  // week.

  currList = stnInfoList;
  expandedList = nullptr;
  int listLength = 0;
  while (currList != nullptr)
  {
    currInfo = currList->object;
    if (currInfo != nullptr)
    {
      // Make as many copies of currInfo as the total count of days in the week
      // when this train runs from/to this station
      int jCode = currInfo->journeyCode;
      int stSeq = currInfo->stopSeq;
      int arrTime = currInfo->arrTime;
      int depTime = currInfo->depTime;

      for (int i = 0; i < 7; i++)
      {
        if (currInfo->daysOfWeek[i])
        {
          TrainInfoPerStation *newExpandedElement = new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);
          if (newExpandedElement == nullptr)
          {
            cerr << "Memory allocation failure." << endl;
            continue;
          }
          newExpandedElement->setDayOfWeek(i);

          listOfObjects<TrainInfoPerStation *> *newExpandedListElement = new listOfObjects<TrainInfoPerStation *>(newExpandedElement);
          if (newExpandedListElement == nullptr)
          {
            cerr << "Memory allocation failure." << endl;
            continue;
          }

          if (expandedList == nullptr)
          {
            expandedList = newExpandedListElement;
          }
          else
          {
            newExpandedListElement->next = expandedList;
            expandedList->prev = newExpandedListElement;
            expandedList = newExpandedListElement;
          }
          listLength++;
        }
      }
    }
    currList = currList->next;
  }

  return expandedList;
}

int getArrivalTime(int journeyCode, int stationFrom, 
int currentDay, int boardTime ,int neighbourIndex, 
StationAdjacencyList adjacency[DICT_SIZE], int &reachDay)
{
  listOfObjects<StationConnectionInfo *> *StationsIncoming = adjacency[neighbourIndex].fromStations;
  while (StationsIncoming->object->adjacentStnIndex != stationFrom)
    StationsIncoming = StationsIncoming->next;

  listOfObjects<TrainInfoPerStation *> *trainsIncoming = StationsIncoming->object->trains;
  while (trainsIncoming != nullptr &&
         trainsIncoming->object->journeyCode != journeyCode)
    trainsIncoming = trainsIncoming->next;
  if (trainsIncoming == nullptr)  return -1;
  
  trainsIncoming = expandTrainsList(trainsIncoming);

  while (trainsIncoming != nullptr)
  {

    if ((abs(getDayFromOneHot(trainsIncoming->object->daysOfWeek) - currentDay) >= 0) || (getDayFromOneHot(trainsIncoming->object->daysOfWeek) == 0 && currentDay == 6))
    {
      if (getDayFromOneHot(trainsIncoming->object->daysOfWeek) == currentDay && trainsIncoming->object->arrTime > boardTime)
      {
        reachDay = getDayFromOneHot(trainsIncoming->object->daysOfWeek);
        return trainsIncoming->object->arrTime;

      }
      else if ((getDayFromOneHot(trainsIncoming->object->daysOfWeek) == currentDay + 1 || (getDayFromOneHot(trainsIncoming->object->daysOfWeek) == 0 && currentDay == 6)) && trainsIncoming->object->arrTime < boardTime)
      { 
        reachDay = getDayFromOneHot(trainsIncoming->object->daysOfWeek);
        return trainsIncoming->object->arrTime;
      }
    }
    trainsIncoming = trainsIncoming->next;
  }
  return -1;
}

void DFS(int srcIndex, int destIndex,
         listOfObjects<Journey> *&journeyList, bool *visited,
         StationAdjacencyList *adjacency,
         Dictionary<int> stnNameToIndex,
         int maxStopOvers,
         int maxTransitTime)
{
  visited[srcIndex] = 1;
  listOfObjects<StationConnectionInfo *> *neighbours = adjacency[srcIndex].toStations;

  //if destination reached print all the journeys
  if (srcIndex == destIndex)
  {
    printJourneys(journeyList, stnNameToIndex);
  }
  else
  {
    //Explore adjacent nodes
    while (neighbours != nullptr)
    {
      listOfObjects<TrainInfoPerStation *> *train = expandTrainsList(neighbours->object->trains);

      Journey journey;
      int neighbourIndex = neighbours->object->adjacentStnIndex;
      //Use all the available trains to explore adjacent nodes
      while (train != nullptr)
      {

        if (visited[neighbourIndex] == 0)
        {
          //if the journeylist is empty add the first journey
          //else check if the person can actually take the train
          if (journeyList == nullptr || canTakeTrain(*train->object, journeyList, maxTransitTime, maxStopOvers))
          {
            //dont' execute when boarding the first train
            if (journeyList != nullptr)
            {
              if (train->object->journeyCode != journeyList->object.journeyCode)
              {
                journey.currentStops = journeyList->object.currentStops + 1;
              }
              else
              {
                journey.currentStops = journeyList->object.currentStops;
              }
            }
            journey.journeyCode = train->object->journeyCode;
            journey.startStation = srcIndex;
            journey.endStation = neighbourIndex;
            journey.boardDay = getDayFromOneHot(train->object->daysOfWeek);

            journey.boardTime = train->object->depTime;
            journey.reachTime = getArrivalTime(train->object->journeyCode, srcIndex, journey.boardDay, journey.boardTime, neighbourIndex, adjacency , journey.reachDay);
            if (journey.reachTime  == -1) // cant use this train
            {
              train = train->next;
              continue;
            }
           
          }
          if (0 <= journey.startStation && journey.startStation < 512 && 0 <= journey.endStation && journey.endStation < 512)
          {
            if (journeyList == nullptr)
            {
              journeyList = new listOfObjects<Journey>(journey);
            }
            else
            {
              listOfObjects<Journey> *temp = journeyList;
              journeyList->next = new listOfObjects<Journey>(journey);
              journeyList = journeyList->next;
              journeyList->prev = temp;
            }
            DFS(neighbourIndex, destIndex, journeyList, visited, adjacency, stnNameToIndex, maxStopOvers, maxTransitTime);
            journey.startStation = journey.endStation = -9999; // reset the values, such that this block isn't entered
          }
        }

        train = train->next;
      }
      neighbours = neighbours->next;
    }
  }
  // upon exiting from a recursion stack, remove the latest added journey from the journey list
  // mark the currently visited node as unvisited
  visited[srcIndex] = 0;

  if (journeyList != nullptr)
  {
    if (journeyList->prev == nullptr)
    {
      delete journeyList;
      journeyList = nullptr;
    }
    else
    {
      listOfObjects<Journey> *deleted = journeyList;
      journeyList = journeyList->prev;
      journeyList->next = nullptr;
      deleted->prev = nullptr;
      delete deleted;
    }
  }
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  bool visited[DICT_SIZE] = {0};
  int srcIndex = stnNameToIndex.get(srcStnName)->value;
  int destIndex = stnNameToIndex.get(destStnName)->value;
  listOfObjects<Journey> *journeysList = nullptr;

  DFS(srcIndex, destIndex, journeysList, visited,
      this->adjacency, this->stnNameToIndex, maxStopOvers, maxTransitTime);

  return;
}

#endif
