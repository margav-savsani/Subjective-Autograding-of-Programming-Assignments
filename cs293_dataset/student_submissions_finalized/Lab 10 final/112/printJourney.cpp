#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void prettyPrint(TrainInfoPerStation *printMe, Planner *myPlanner, int day)
{
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

  // Expanding information in stnInfoList to get a list of train info
  // in which each element of the list refers to a single day of the
  // week.  This is the list that has to be finally sorted using
  // quicksort.
  cout << GREEN << "Day(s): " << RESET;
  cout << days[day];
  cout << endl;
  cout << BLUE << "JourneyCode: " << printMe->journeyCode << RESET << "\t";
  cout << RED << "Arr: " << RESET;
  if (printMe->arrTime == -1)
  {
    cout << "Starts";
  }
  else
  {
    cout << printMe->arrTime;
  }
  cout << RED << " Dep: " << RESET;
  if (printMe->depTime == -1)
  {
    cout << "Ends";
  }
  else
  {
    cout << printMe->depTime;
  }
  cout << endl;
}

struct arrDetails // struct to store the arrival details of a particular ride. will help in printing
{
  int day; // day of arrival at the station
  int arrTime;
  arrDetails() {}
};

// a ride from one station to an adjacent station
struct Hop
{
  int trainIndex;             // lexicographic order of this ride
  TrainInfoPerStation *train; // ride details
  int day;                    // which day the passenger leaves the first station
  int index;                  //  the adjacent station's index is stored
  Hop(TrainInfoPerStation *train, int day, int adj, int trainIndex)
  {
    this->train = train;
    this->day = day;
    this->index = adj;
    this->trainIndex = trainIndex;
  }
};

void myPrint(Dictionary<int> dict, Planner *myPlanner, StationAdjacencyList *adj, Hop *from, int v, int d, bool ***visited, int *order, Hop *path, int &length, int maxStopOvers, float maxTransitTime, arrDetails *arr)
{
  if (maxTransitTime < 0 || maxStopOvers < 0)
  { // we have exhausted the transit bounds
    return;
  }

  // add v to "order"
  if (from != NULL) // v != src
  {
    memcpy(&path[length], from, sizeof(Hop));
    visited[order[length - 1]][from->trainIndex][from->day] = true;
  }
  order[length] = v;
  length++;

  if (v != d)
  {
    if (adj[v].toStations != NULL)
    {
      Hop *reflectedHop; // stores the day of arrival and arrival time of the train that arrrived at v
      if (from != NULL)
      {
        // find the time at which the train arrived at v
        listOfObjects<StationConnectionInfo *> *fromConnection = adj[v].fromStations; //  where the train arrived from
        while (fromConnection != NULL)
        {
          int trainIndex = 0;
          listOfObjects<TrainInfoPerStation *> *train = fromConnection->object->trains;
          while (train != NULL)
          {
            if (train->object->journeyCode == from->train->journeyCode)
            {
              // found it
              if (train->object->arrTime < from->train->depTime)
                reflectedHop = new Hop(train->object, (from->day + 1) % 7, -1, trainIndex); // train arrives a day later
              else
                reflectedHop = new Hop(train->object, from->day, -1, trainIndex); // train arrives the same day that it leaves
              arr[length - 1].day = reflectedHop->day;
              arr[length - 1].arrTime = train->object->arrTime;
              goto doubleBreak;
            }
            train = train->next;
            trainIndex++;
          }
          fromConnection = fromConnection->next;
        }
      }
    doubleBreak:
      listOfObjects<StationConnectionInfo *> *neighbourConnection = adj[v].toStations;
      int trainIndex = 0;
      while (neighbourConnection != NULL)
      {
        listOfObjects<TrainInfoPerStation *> *train = neighbourConnection->object->trains;
        while (train != NULL)
        {
          for (int dayVisited = 0; dayVisited < 7; dayVisited++)
          {
            if (train->object->daysOfWeek[dayVisited])
            {
              if (!visited[v][trainIndex][dayVisited]) // check
              {
                // found a possible way to proceed
                if (from == NULL)
                {
                  if (train->object->depTime < train->object->arrTime)
                    dayVisited = (dayVisited + 1) % 7; // the train leaves the day after arriving
                  Hop myHop(train->object, dayVisited, neighbourConnection->object->adjacentStnIndex, trainIndex);
                  myPrint(dict, myPlanner, adj, &myHop, neighbourConnection->object->adjacentStnIndex, d, visited, order, path, length, maxStopOvers, maxTransitTime, arr);
                  if (train->object->depTime < train->object->arrTime)
                    dayVisited = (dayVisited - 1) % 7; // the train leaves the day after arriving
                }
                else
                {
                  // need to update transit time and max stop overs before the recursive call
                  if (from->train->journeyCode != train->object->journeyCode)
                  {
                    maxStopOvers--;
                    float hoursDeparted = (24 * dayVisited + train->object->depTime / 100) + float(train->object->depTime % 100) / 60;                   // number of hours passed since sunday midnight when the train departs from v
                    float hoursArrived = (24 * reflectedHop->day + reflectedHop->train->arrTime / 100) + float(reflectedHop->train->arrTime % 100) / 60; // number of hours passed since sunday midnight when the train departs from v
                    if (hoursDeparted < hoursArrived || hoursDeparted - hoursArrived > maxTransitTime)
                    {
                      continue;
                    }
                  }
                  if (train->object->depTime < train->object->arrTime)
                    dayVisited = (dayVisited + 1) % 7; // the train leaves the day after arriving
                  Hop myHop(train->object, dayVisited, neighbourConnection->object->adjacentStnIndex, trainIndex);
                  myPrint(dict, myPlanner, adj, &myHop, neighbourConnection->object->adjacentStnIndex, d, visited, order, path, length, maxStopOvers, maxTransitTime, arr);
                  if (train->object->depTime < train->object->arrTime)
                    dayVisited = (dayVisited - 1) % 7; // the train leaves the day after arriving
                }
              }
            }
          }
          train = train->next;
          trainIndex++;
        }
        neighbourConnection = neighbourConnection->next;
      }
      if (from != NULL)
      {
        delete reflectedHop;
      }
    }
  }
  else if (from == NULL)
  {
    cout << "Invalid input: Source and Destination are identical" << endl;
  }
  else
  {
    // print the path
    string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    cout << "Started from source (" << dict.getKeyAtIndex(order[0]) << ')' << endl;
    for (int i = 1; i < length; i++)
    {
      // cout << "Follow day " << path[i].day << endl;
      // listOfObjects<TrainInfoPerStation *> printMe(path[i].train);
      // myPlanner->printStationInfo(&printMe);
      prettyPrint(path[i].train, myPlanner, path[i].day);
      if (i != length - 1)
      {
        // assert(arr[i].day >= 0 && arr[i].day <= 6);
        cout << "Reached station " << dict.getKeyAtIndex(order[i]) << " at " << arr[i].arrTime << " on " << days[arr[i].day] << endl;
      }
      else
      {
        cout << "Reached destination (" << dict.getKeyAtIndex(order[i]) << ')' << endl;
      }
    }
    cout << "==============================================" << endl;
  }
  length--;
  if (from != NULL)
  {
    visited[order[length - 1]][from->trainIndex][from->day] = false;
  }
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  // listOfObjects<TrainInfoPerStation *> *path = NULL; // stores the potential path from source to destination
  // listOfObjects<int> *order = NULL;                  // stores the order of visiting of the stations in this path
  cout << "In case no journeys are displayed, it means that no route exists" << endl;
  cout << "==============================================" << endl;

  int path_length = 0;                                // length of the path covered so far
  Hop *path = (Hop *)malloc(DICT_SIZE * sizeof(Hop)); // stores the potential path from source to destination
  arrDetails *arr = new arrDetails[DICT_SIZE];
  memset(path, 0, DICT_SIZE);
  int *order = new int[DICT_SIZE];          // stores the order of visiting of the stations in this path
  bool ***visited = new bool **[DICT_SIZE]; // whether that node is visited in a partcular way or not
  for (int i = 0; i < DICT_SIZE; i++)
  {
    visited[i] = new bool *[20];
    for (int j = 0; j < 20; j++)
    {
      visited[i][j] = new bool[7];
      for (int k = 0; k < 7; k++)
      {
        visited[i][j][k] = false;
      }
    }
  }
  int srcIndex = stnNameToIndex.get(srcStnName)->value;
  int destIndex = stnNameToIndex.get(destStnName)->value;
  myPrint(this->stnNameToIndex, this, this->adjacency, NULL, srcIndex, destIndex, visited, order, path, path_length, maxStopOvers, maxTransitTime, arr);
  delete[] order;
  delete[] visited;
  delete[] arr;
  free(path);

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  return;
}

#endif
