#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// To print the final journey
struct journeyInfo
{
  string stationName;
  int journeyCode;
  int arrTime;
  int deptTime;
  int day;

  journeyInfo(string sname, int jc, int at, int dt, int d)
  {
    journeyCode = jc;
    arrTime = at;
    deptTime = dt;
    day = d;
    stationName = sname;
  }
};

// Prints journey from linked list
void printJourney(listOfObjects<journeyInfo *> *journeys)
{
  string day[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  while (journeys != nullptr)
  {
    cout << "Station: " << journeys->object->stationName << endl;
    cout << "Train Code: " << journeys->object->journeyCode << endl;
    journeys->object->arrTime == -1 ? cout << "Train Starts from Here" << endl : cout << "Arrival Time: " << journeys->object->arrTime % 2400 << endl;
    cout << "Departure Time: " << journeys->object->deptTime << endl;
    cout << "Day: " << day[journeys->object->day % 7] << endl;
    cout << endl;
    journeys = journeys->next;
  }

  cout << "Happy Journey :)" << endl;

  cout << "==============================" << endl;
}

// Checks if departure of new train is within maximum transit time
bool possibleDeparture(int arrTime, int maxTransitTime, int day, int deptTime)
{
  if (deptTime == -1)
  {
    return false;
  }

  return ((day * 2400 + deptTime - arrTime <= maxTransitTime && day * 2400 + deptTime - arrTime >= 0) || ((day + 7) * 2400 + deptTime - arrTime <= maxTransitTime && (day + 7) * 2400 + deptTime - arrTime >= 0));
}

// Checks if there is offset between departure from station1 and arrival in station2
bool isOffset(bool *days1, bool *days2)
{
  for (int i = 0; i < 7; i++)
  {
    if (days1[i] == days2[i])
    {
      return true;
    }
  }

  return false;
}

// Returns the traininfoperstation for corresponding journey code from linked list
TrainInfoPerStation *getInfo(listOfObjects<TrainInfoPerStation *> *allTrains, int journeyCode)
{
  while (allTrains != nullptr)
  {
    if (allTrains->object->journeyCode == journeyCode)
    {
      return allTrains->object;
    }
    allTrains = allTrains->next;
  }

  return nullptr;
}

// DFS algorithm=>Performs DFS for each day of each train.
void DFS(int currIndex, int arrTime, int train, int maxTime, int maxChange, int endIndex, StationAdjacencyList *adjacency, listOfObjects<TrainInfoPerStation *> **stationInfo, listOfObjects<journeyInfo *> *journeyList, Dictionary<int> *dict)
{
  // If called after changing train more than limit, return
  if (maxChange < 0)
  {
    listOfObjects<journeyInfo *> *temp = journeyList;

    while (temp->next != nullptr)
    {
      temp = temp->next;
    }

    if (temp->prev != nullptr)
    {
      temp->prev->next = nullptr;
    }

    delete temp;
    return;
  }

  // If found, print journey
  if (currIndex == endIndex)
  {
    std::cout << "Journey Found:" << endl;
    // Print Jounrey
    printJourney(journeyList);
    listOfObjects<journeyInfo *> *temp = journeyList;

    while (temp->next != nullptr)
    {
      temp = temp->next;
    }

    if (temp->prev != nullptr)
    {
      temp->prev->next = nullptr;
    }

    delete temp;
    
    return;
  }
  // Iterate through adjacent stations
  listOfObjects<StationConnectionInfo *> *toStations = adjacency[currIndex].toStations;

  while (toStations != nullptr)
  {
    listOfObjects<TrainInfoPerStation *> *trains = toStations->object->trains;
    // Iterate through all trains
    while (trains != nullptr)
    {
      int journeyCode = trains->object->journeyCode;
      // If same train
      if (journeyCode == train)
      {
        int day = arrTime / 2400;
        bool *day1 = getInfo(stationInfo[currIndex], journeyCode)->daysOfWeek;
        bool *day2 = getInfo(stationInfo[toStations->object->adjacentStnIndex], journeyCode)->daysOfWeek;

        if (isOffset(day1, day2))
        {
          journeyInfo *newJourney = new journeyInfo(dict->getKeyAtIndex(currIndex), journeyCode, arrTime, getInfo(stationInfo[toStations->object->adjacentStnIndex], journeyCode)->depTime, day + 1);

          listOfObjects<journeyInfo *> *newJourneyList = new listOfObjects<journeyInfo *>(newJourney);

          listOfObjects<journeyInfo *> *temp = journeyList;

          while (temp->next != nullptr)
          {
            temp = temp->next;
          }

          temp->next = newJourneyList;
          temp->next->prev = temp;

          DFS(toStations->object->adjacentStnIndex, (day + 1) * 2400 + getInfo(stationInfo[toStations->object->adjacentStnIndex], journeyCode)->arrTime, journeyCode, maxTime, maxChange, endIndex, adjacency, stationInfo, journeyList, dict);
        }

        else
        {
          journeyInfo *newJourney = new journeyInfo(dict->getKeyAtIndex(currIndex), journeyCode, arrTime, getInfo(stationInfo[toStations->object->adjacentStnIndex], journeyCode)->depTime, day);

          listOfObjects<journeyInfo *> *newJourneyList = new listOfObjects<journeyInfo *>(newJourney);

          listOfObjects<journeyInfo *> *temp = journeyList;

          while (temp->next != nullptr)
          {
            temp = temp->next;
          }

          temp->next = newJourneyList;
          temp->next->prev = temp;

          DFS(toStations->object->adjacentStnIndex, day * 2400 + getInfo(stationInfo[toStations->object->adjacentStnIndex], journeyCode)->arrTime, journeyCode, maxTime, maxChange, endIndex, adjacency, stationInfo, journeyList, dict);
        }
      }
      // If different tree
      else
      {
        for (int i = 0; i < 7; i++)
        {
          if (getInfo(stationInfo[currIndex], journeyCode)->daysOfWeek[i])
          {
            if (possibleDeparture(arrTime, maxTime, i, getInfo(stationInfo[currIndex], journeyCode)->depTime))
            {
              bool *day1 = getInfo(stationInfo[currIndex], journeyCode)->daysOfWeek;
              bool *day2 = getInfo(stationInfo[toStations->object->adjacentStnIndex], journeyCode)->daysOfWeek;

              if (isOffset(day1, day2))
              {
                journeyInfo *newJourney = new journeyInfo(dict->getKeyAtIndex(currIndex), journeyCode, arrTime, getInfo(stationInfo[toStations->object->adjacentStnIndex], journeyCode)->depTime, i + 1);

                listOfObjects<journeyInfo *> *newJourneyList = new listOfObjects<journeyInfo *>(newJourney);

                listOfObjects<journeyInfo *> *temp = journeyList;

                while (temp->next != nullptr)
                {
                  temp = temp->next;
                }

                temp->next = newJourneyList;
                temp->next->prev = temp;
                DFS(toStations->object->adjacentStnIndex, (i + 1) * 2400 + getInfo(stationInfo[toStations->object->adjacentStnIndex], journeyCode)->arrTime, journeyCode, maxTime, maxChange - 1, endIndex, adjacency, stationInfo, journeyList, dict);
              }

              else
              {
                journeyInfo *newJourney = new journeyInfo(dict->getKeyAtIndex(currIndex), journeyCode, arrTime, getInfo(stationInfo[toStations->object->adjacentStnIndex], journeyCode)->depTime, i);

                listOfObjects<journeyInfo *> *newJourneyList = new listOfObjects<journeyInfo *>(newJourney);

                listOfObjects<journeyInfo *> *temp = journeyList;

                while (temp->next != nullptr)
                {
                  temp = temp->next;
                }

                temp->next = newJourneyList;
                temp->next->prev = temp;

                DFS(toStations->object->adjacentStnIndex, i * 2400 + getInfo(stationInfo[toStations->object->adjacentStnIndex], journeyCode)->arrTime, journeyCode, maxTime, maxChange - 1, endIndex, adjacency, stationInfo, journeyList, dict);
              }
            }
          }
        }
      }
      trains = trains->next;
    }
    toStations = toStations->next;
  }

  listOfObjects<journeyInfo *> *temp = journeyList;

  while (temp->next != nullptr)
  {
    temp = temp->next;
  }

  if (temp->prev != nullptr)
  {
    temp->prev->next = nullptr;
  }

  delete temp;
}

// Calls DFS for each train from source station
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  maxTransitTime = maxTransitTime * 100;
  // insert your code here

  int startIndex = stnNameToIndex.get(srcStnName)->value;
  int endIndex = stnNameToIndex.get(destStnName)->value;

  listOfObjects<StationConnectionInfo *> *toStations = adjacency[startIndex].toStations;

  while (toStations != nullptr)
  {
    listOfObjects<TrainInfoPerStation *> *trains = toStations->object->trains;
    while (trains != nullptr)
    {
      int journeyCode = trains->object->journeyCode;
      for (int i = 0; i < 7; i++)
      {
        if (getInfo(stationInfo[startIndex], journeyCode)->daysOfWeek[i])
        {
          bool *day1 = getInfo(stationInfo[startIndex], journeyCode)->daysOfWeek;
          bool *day2 = getInfo(stationInfo[toStations->object->adjacentStnIndex], journeyCode)->daysOfWeek;

          if (isOffset(day1, day2))
          {
            journeyInfo *newJourney = new journeyInfo(srcStnName, journeyCode, getInfo(stationInfo[startIndex], journeyCode)->arrTime, getInfo(stationInfo[startIndex], journeyCode)->depTime, i + 1);

            listOfObjects<journeyInfo *> *journeyList = new listOfObjects<journeyInfo *>(newJourney);

            DFS(toStations->object->adjacentStnIndex, (i + 1) * 2400 + getInfo(stationInfo[toStations->object->adjacentStnIndex], journeyCode)->arrTime, journeyCode, maxTransitTime, maxStopOvers, endIndex, adjacency, stationInfo, journeyList, &stnNameToIndex);
          }

          else
          {
            journeyInfo *newJourney = new journeyInfo(srcStnName, journeyCode, getInfo(stationInfo[startIndex], journeyCode)->arrTime, getInfo(stationInfo[startIndex], journeyCode)->depTime, i + 1);

            listOfObjects<journeyInfo *> *journeyList = new listOfObjects<journeyInfo *>(newJourney);

            DFS(toStations->object->adjacentStnIndex, i * 2400 + getInfo(stationInfo[toStations->object->adjacentStnIndex], journeyCode)->arrTime, journeyCode, maxTransitTime, maxStopOvers, endIndex, adjacency, stationInfo, journeyList, &stnNameToIndex);
          }
        }
      }
      trains = trains->next;
    }
    toStations = toStations->next;
  }

  return;
}

#endif
