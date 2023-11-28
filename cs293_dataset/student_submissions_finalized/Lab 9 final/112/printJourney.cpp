#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <vector>

using namespace std;

// void Planner::printDirectJourneys(string srcStnName, string destStnName)
// {

//   // insert your code here
//   Entry<int> *srcIndex = stnNameToIndex.get(srcStnName);
//   Entry<int> *destIndex = stnNameToIndex.get(destStnName);
//   // identify possible journey codes based on destn
//   listOfObjects<StationConnectionInfo *> *destFrom = adjacency[destIndex->value].fromStations;
//   vector<int> potJC; // potential JCs
//   while (destFrom != NULL)
//   {
//     listOfObjects<TrainInfoPerStation *> *currTrain = destFrom->object->trains;
//     while (currTrain != NULL)
//     {
//       potJC.push_back(currTrain->object->journeyCode);
//       currTrain = currTrain->next;
//     }
//     destFrom = destFrom->next;
//   }
//   // now we have all the potential JC's
//   // conduct BFS while storing an
//   vector<int> indexQueue; // BFS Queue
//   // bool visited[DICT_SIZE]; // true iff that node is visited
//   // for (int i = 0; i < DICT_SIZE; i++)
//   // {
//   //   visited[i] = false;
//   // }
//   indexQueue.push_back(srcIndex->value);
//   // visited[srcIndex->value] = true;
//   while (!indexQueue.empty())
//   {
//     listOfObjects<StationConnectionInfo *> *addMe = adjacency[indexQueue[0]].toStations; // additions to the queue
//   }

//   cout << "This function is to be implemented by you." << endl;

//   // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
//   // for the source station and then we can print it out by invoking
//   // printStationInfo that we had used in Lab 7.
//   // printStationInfo is a private member function of the Planner class
//   // It is declared in planner.h and implemented in planner.cpp

//   return;
// }

// stores the JC of that train and whether it manages to reach the dest
struct trainData
{
  int JC;
  bool reached;
  trainData(int JC, bool reached)
  {
    this->JC = JC;
    this->reached = reached;
  }
};

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  int srcIndex = stnNameToIndex.get(srcStnName)->value;
  int destIndex = stnNameToIndex.get(destStnName)->value;
  vector<TrainInfoPerStation *> BFSQueue;
  vector<int> BFSIndicesQueue;
  listOfObjects<StationConnectionInfo *> *stationIterator = adjacency[srcIndex].toStations;
  while (stationIterator != NULL)
  {
    listOfObjects<TrainInfoPerStation *> *currTrain = stationIterator->object->trains;
    int currIndex = stationIterator->object->adjacentStnIndex;
    while (currTrain != NULL)
    {
      BFSQueue.push_back(currTrain->object);
      BFSIndicesQueue.push_back(currIndex);
      currTrain = currTrain->next;
    }
    stationIterator = stationIterator->next;
  }
  // now BFSQueue has all the TrainInfoPerStations from source to adjacent vertices
  vector<TrainInfoPerStation *> returnMe = BFSQueue;
  vector<trainData> reachedDest;
  for (int i = 0; i < returnMe.size(); i++)
  {
    if (BFSIndicesQueue[i] == destIndex)
    {
      trainData entry(BFSQueue[i]->journeyCode, true);
      reachedDest.push_back(entry);
    }
    else
    {
      trainData entry(BFSQueue[i]->journeyCode, false);
      reachedDest.push_back(entry);
    }
  }
  while (!BFSQueue.empty()) // main BFS loop
  {
    listOfObjects<StationConnectionInfo *> *stationIterator = adjacency[BFSIndicesQueue[0]].toStations;
    while (stationIterator != NULL)
    {
      listOfObjects<TrainInfoPerStation *> *currTrain = stationIterator->object->trains;
      int currIndex = stationIterator->object->adjacentStnIndex;
      while (currTrain != NULL)
      {
        BFSQueue.push_back(currTrain->object);
        BFSIndicesQueue.push_back(currIndex);
        currTrain = currTrain->next;
      }
      stationIterator = stationIterator->next;
    }
    // update reachedDest in case we have reached dest
    if (BFSIndicesQueue[0] == destIndex)
    {
      for (int i = 0; i < reachedDest.size(); i++)
      {
        if (BFSQueue[0]->journeyCode == reachedDest[i].JC)
        {
          reachedDest[i].reached = true;
        }
      }
    }
    BFSIndicesQueue.erase(BFSIndicesQueue.begin());
    BFSQueue.erase(BFSQueue.begin());
  }
  listOfObjects<TrainInfoPerStation *> *printMe = NULL; // final list to be printed
  for (int i = 0; i < reachedDest.size(); i++)
  {
    if (reachedDest[i].reached)
    {
      if (printMe == NULL)
      {
        printMe = new listOfObjects<TrainInfoPerStation *>(returnMe[i]);
      }
      else
      {
        printMe->prev = new listOfObjects<TrainInfoPerStation *>(returnMe[i]);
        printMe->prev->next = printMe;
        printMe = printMe->prev;
      }
    }
  }
  if (printMe == NULL)
  {
    cout << "No direct Journeys Exist" << endl;
  }
  else
  {
    printStationInfo(printMe);
  }
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

  return;
}

#endif
