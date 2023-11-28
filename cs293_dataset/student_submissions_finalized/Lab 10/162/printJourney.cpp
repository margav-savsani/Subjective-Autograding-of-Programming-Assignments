#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP


#include "vector"
#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

bool checkTrain(int journeyCode, listOfObjects<TrainInfoPerStation *> *trainsOutgoing)
{
  while (trainsOutgoing != NULL)
  {
    if (trainsOutgoing->object->journeyCode == journeyCode)
    {
      return true;
    }
    trainsOutgoing = trainsOutgoing->next;
  }
  return false;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  int srcIndex = stnNameToIndex.get(srcStnName)->value;
  int destIndex = stnNameToIndex.get(destStnName)->value;

  listOfObjects<TrainInfoPerStation *> *currentTrainFromSrc = stationInfo[srcIndex];
  listOfObjects<TrainInfoPerStation *> *trains = NULL;
  // printStationInfo()

  while (currentTrainFromSrc != NULL)
  {
    vector<int> Queue;
    int journeyCode = currentTrainFromSrc->object->journeyCode;
    // cout<<"called: "<<journeyCode<<endl;
    Queue.push_back(srcIndex);
    while (!Queue.empty())
    {
      int index = Queue.front();
      // cout<<"curr: "<<stnNameToIndex.getKeyAtIndex(index)<<endl;

      listOfObjects<StationConnectionInfo *> *neighbour = this->adjacency[index].toStations;

      while (neighbour != NULL && neighbour->object != NULL)
      {
        int neighbourIndex = neighbour->object->adjacentStnIndex;
        // cout<<stnNameToIndex.getKeyAtIndex(neighbourIndex)<<endl;
        listOfObjects<TrainInfoPerStation *> *trainsOutgoing = neighbour->object->trains;

        if (checkTrain(journeyCode, trainsOutgoing))
        {

          if (neighbourIndex == destIndex)
          {
            if (trains == NULL)
            {

              trains = new listOfObjects<TrainInfoPerStation *>(currentTrainFromSrc->object);
            }
            else
            {

              trains->next = new listOfObjects<TrainInfoPerStation *>(currentTrainFromSrc->object);
              trains->next->prev = trains;
              trains = trains->next;
            }

            break;
          }
          else
          {

            Queue.push_back(neighbourIndex);
          }
        }

        neighbour = neighbour->next;
      }
      // cout<<"popped: "<<stnNameToIndex.getKeyAtIndex(index)<<endl;
      Queue.erase(Queue.begin(), Queue.begin()+1);
      // visited[index] = 2; //visited
    }
    // cout<<"here"<<endl;
    currentTrainFromSrc = currentTrainFromSrc->next;
  }
  if(trains == NULL)
  {
    cout<<"No direct journeys available."<<endl;
    return;
  }
  
  while (trains->prev != NULL)
  {
    trains = trains->prev;
  }

  printStationInfo(trains);
  // cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

  return;
}

#endif
