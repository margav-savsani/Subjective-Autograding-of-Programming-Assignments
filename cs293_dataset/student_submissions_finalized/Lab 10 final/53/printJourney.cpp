#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP


#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// The unit to be printed

struct journeyinfo
{
  int journeyCode;
  int depTime;
  int depDay;
  int arrTime;
  int arrDay;
  int adjacent_stn_index;
  int transit_time; // Transit time from previous journey

  //constructor
  journeyinfo(int journeyCode, int depTime, int depDay, int arrTime, int arrDay, int adjacent_stn_index, int transit_time)
  {
    this->journeyCode = journeyCode;
    this->depTime = depTime;
    this->depDay = depDay;
    this->arrTime = arrTime;
    this->arrDay = arrDay;
    this->adjacent_stn_index = adjacent_stn_index;
    this->transit_time = transit_time;
  }
};

// Function to generate expanded list of trains 

listOfObjects<TrainInfoPerStation *> *expanded_trains(listOfObjects<TrainInfoPerStation *> *trains)
{
  listOfObjects<TrainInfoPerStation *> *currList, *expandedList, *tailexpandedList;
  TrainInfoPerStation *currInfo;
  // string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

  // Expanding information in stnInfoList to get a list of train info
  // in which each element of the list refers to a single day of the
  // week.  This is the list that has to be finally sorted using
  // quicksort.

  currList = trains;
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
            tailexpandedList = expandedList;
          }
          else
          {
            tailexpandedList->next = newExpandedListElement;
            newExpandedListElement->prev = tailexpandedList;
            tailexpandedList = tailexpandedList->next;
          }
          listLength++;
        }
      }
    }
    currList = currList->next;
  }
  return expandedList;
}

// function to find arrival time

int arrivalTime(TrainInfoPerStation *currentTrain, int next_stn, StationAdjacencyList *adjacency)
{
  listOfObjects<StationConnectionInfo *> *currentNode = adjacency[next_stn].toStations;
  while (currentNode != nullptr)
  {
    listOfObjects<TrainInfoPerStation *> *fromTrain = currentNode->object->trains;
    while (fromTrain != nullptr)
    {
      if (fromTrain->object->journeyCode == currentTrain->journeyCode)
        return fromTrain->object->arrTime;
      fromTrain = fromTrain->next;
    }
    currentNode = currentNode->next;
  }
  return -2;
}

//Insert node in the printing list

void insert_node(listOfObjects<journeyinfo *> *&printingInfo, listOfObjects<journeyinfo *> *&tail_printingInfo, int journeycode, int transit_time, int depDay, int depTime, int arrDay, int arrTime, int adjacentStn)
{
  journeyinfo *new_journey = new journeyinfo(journeycode, depTime, depDay, arrTime, arrDay, adjacentStn, transit_time);
  listOfObjects<journeyinfo *> *new_node = new listOfObjects<journeyinfo *>(new_journey);
  if (printingInfo == nullptr)
  {
    printingInfo = new_node;
    tail_printingInfo = new_node;
  }
  else
  {
    tail_printingInfo->next = new_node;
    new_node->prev = tail_printingInfo;
    tail_printingInfo = tail_printingInfo->next;
  }
}

//Removing the last node in the printing list 

void remove_last_node(listOfObjects<journeyinfo *> *&printingInfo, listOfObjects<journeyinfo *> *&tail_printingInfo)
{
  if (tail_printingInfo->prev == nullptr)
  {
    // see how to completely delete the memory allocated to the deleted node
    printingInfo = nullptr;
    tail_printingInfo = nullptr;
  }
  else
  {
    tail_printingInfo = tail_printingInfo->prev;
    tail_printingInfo->next = nullptr;
  }
}

//Printing the list when destination is reached

void print_journey(int source_stn, listOfObjects<journeyinfo *> *&printingInfo, listOfObjects<journeyinfo *> *&tail_printingInfo)
{
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  listOfObjects<journeyinfo *> *current_node = printingInfo;
  cout << "Journey:" << endl;
  cout << "Station: " << source_stn;
  while (current_node != nullptr)
  {
    if (current_node->object->transit_time != 0)
    {
      cout << GREEN << "Transit time: " << current_node->object->transit_time << RESET << endl;
    }
    cout << "Train Journey Code: " << current_node->object->journeyCode << endl;
    cout << "Dep : " << days[current_node->object->depDay] << " " << current_node->object->depTime << endl;
    cout << "Arr : " << days[current_node->object->arrDay] << " " << current_node->object->arrTime << endl;
    cout << "Station: " << current_node->object->adjacent_stn_index << endl;
  }
  remove_last_node(printingInfo,tail_printingInfo);
}

// running the primary DFS function

void DFS(StationAdjacencyList *expanded_adjacency, StationAdjacencyList *adjacency, int source_stn, int current_stn, int dest_stn, int remainingStopOvers, int maxTransitTime, TrainInfoPerStation *train_ongoing, listOfObjects<journeyinfo *> *printingInfo, listOfObjects<journeyinfo *> *tail_printingInfo, int dfs_arr_day, int dfs_arr_time)
{ // If destination is reached
  if (current_stn == dest_stn)
  {
    // print the journey
    print_journey(source_stn, printingInfo, tail_printingInfo);
    return;
  }
  // If no remainingstopOvers left
  if (remainingStopOvers == 0)
  {
    remove_last_node(printingInfo, tail_printingInfo);
    return;
  }

  // Creating the expanded adjacency list
  // Unexpected behaviour of code here
  if (expanded_adjacency[current_stn].toStations == nullptr)
  {
    listOfObjects<StationConnectionInfo *> *tail_expanded_adjacency = nullptr;
    listOfObjects<StationConnectionInfo *> *currNode = adjacency[current_stn].toStations;
    while (currNode != nullptr){
      // {cout << "not null pointer" << endl;
      //     cout << " not null" << endl;
    StationConnectionInfo toInsertStation = *currNode->object;
    toInsertStation.trains = expanded_trains(currNode->object->trains);
    listOfObjects<StationConnectionInfo *> *toinsertNode = new listOfObjects<StationConnectionInfo *>(&toInsertStation);
    if (expanded_adjacency[current_stn].toStations == nullptr)
    {
      expanded_adjacency[current_stn].toStations = toinsertNode;
      tail_expanded_adjacency = toinsertNode;
    }
    else
    {
      tail_expanded_adjacency->next = toinsertNode;
      tail_expanded_adjacency = tail_expanded_adjacency->next;
    }
    currNode = currNode->next;
    }
  }

// Running the next step of DFS from the expanded list created
listOfObjects<StationConnectionInfo *> *currentNode = expanded_adjacency[current_stn].toStations;
while (currentNode != nullptr)
{
  listOfObjects<TrainInfoPerStation *> *currentTrain = currentNode->object->trains;
  while (currentTrain != nullptr)
  { // Finding the arrival time and day of the ongoing journey to the current station
    int arrival_time_next_stn = arrivalTime(currentTrain->object, currentNode->object->adjacentStnIndex, adjacency);
    if (arrival_time_next_stn == -2)
      cout << "got -2" << endl;
    int depDay = 0;
    int arrDay;
    while (true)
    {
      if (currentTrain->object->daysOfWeek[depDay] == 1)
        break;
      depDay++;
    }
    if (arrival_time_next_stn > currentTrain->object->depTime)
      arrDay = depDay;
    else
      arrDay = (depDay + 1) % 7;

    int calculated_transit_time = 0;
    if (train_ongoing == nullptr)
    {
      insert_node(printingInfo, tail_printingInfo, currentTrain->object->journeyCode, calculated_transit_time, depDay, currentTrain->object->depTime, arrDay, arrival_time_next_stn, currentNode->object->adjacentStnIndex);
      DFS(expanded_adjacency, adjacency, source_stn, currentNode->object->adjacentStnIndex, dest_stn, remainingStopOvers, maxTransitTime, currentTrain->object, printingInfo, tail_printingInfo, arrDay, arrival_time_next_stn);
    }
    else
    {
      if (currentTrain->object->journeyCode == train_ongoing->journeyCode)
      {
        insert_node(printingInfo, tail_printingInfo, currentTrain->object->journeyCode, calculated_transit_time, depDay, currentTrain->object->depTime, arrDay, arrival_time_next_stn, currentNode->object->adjacentStnIndex);
        DFS(expanded_adjacency, adjacency, source_stn, currentNode->object->adjacentStnIndex, dest_stn, remainingStopOvers, maxTransitTime, currentTrain->object, printingInfo, tail_printingInfo, arrDay, arrival_time_next_stn);
      }
      else
      {
        calculated_transit_time = ((depDay - dfs_arr_day) % 7) * 2400 + currentTrain->object->depTime - dfs_arr_time;
        if (calculated_transit_time > maxTransitTime)
        {
          remove_last_node(printingInfo, tail_printingInfo);
          return;
        }
        else
        {
          insert_node(printingInfo, tail_printingInfo, currentTrain->object->journeyCode, calculated_transit_time, depDay, currentTrain->object->depTime, arrDay, arrival_time_next_stn, currentNode->object->adjacentStnIndex);
          DFS(expanded_adjacency, adjacency, source_stn, currentNode->object->adjacentStnIndex, dest_stn, remainingStopOvers - 1, maxTransitTime, currentTrain->object, printingInfo, tail_printingInfo, arrDay, arrival_time_next_stn);
        }
      }
    }
    currentTrain = currentTrain->next;
  }
  currentNode = currentNode->next;
}
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  StationAdjacencyList expanded_adjacency[DICT_SIZE];
  listOfObjects<journeyinfo *> *printingInfo;
  listOfObjects<journeyinfo *> *tail_printingInfo;

  // saving the indices of source and destination station
  int source_stn = stnNameToIndex.get(srcStnName)->value;
  int dest_stn = stnNameToIndex.get(destStnName)->value;

  DFS(expanded_adjacency, adjacency, source_stn, source_stn, dest_stn, maxStopOvers, maxTransitTime, nullptr, printingInfo, tail_printingInfo, 3, 5); // last 2 parameters do not parameter. Any random value can be passed
}

#endif
