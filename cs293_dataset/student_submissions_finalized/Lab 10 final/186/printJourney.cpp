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

class TrainStnInfo
{
public:
  int journeyCode;        // same as train number
  unsigned short stopSeq; // sequence of this station's stop in
                          // itinerary of train, i.e. 1st stop in journey
                          // or 2nd stop in journey or ...
  bool daysOfWeek[7];     // Days of week when this train travels
                          // to/from this station
  int arrTime;            // Arrival time at station; -1 if train starts from here
  int depTime;            // Departure time from station; -1 if train ends here
  string departureStn;    // Station Name from which this train departs
  string arrivalStn;      // Station Name at which this train arrives
  int depIndex;           // Departure Station Index
  int arrIndex;           // Arrival Station Index

public:
  TrainStnInfo(int jCode, unsigned short stpSq, int aTm, int dTm, string dStn, string arrStn, int depID, int arrID)
  {
    journeyCode = jCode;
    stopSeq = stpSq;
    arrTime = aTm;
    depTime = dTm;
    departureStn = dStn;
    arrivalStn = arrStn;
    depIndex = depID;
    arrIndex = arrID;
    for (int i = 0; i < 7; i++)
    {
      daysOfWeek[i] = false;
    }
  }

  ~TrainStnInfo() { ; }

  void setDayOfWeek(int i)
  {
    if ((0 <= i) && (i < 7))
      daysOfWeek[i] = true;
  }
  void resetDayOfWeek(int i)
  {
    if ((0 <= i) && (i < 7))
      daysOfWeek[i] = false;
  }
};

TrainStnInfo *findTrain(int jrnyCode, listOfObjects<TrainStnInfo *> *listOfTrains)
{
  while (listOfTrains != nullptr)
  {
    if (listOfTrains->object->journeyCode == jrnyCode)
      return listOfTrains->object;
    listOfTrains = listOfTrains->next;
  }
  return nullptr;
}

TrainInfoPerStation *findTrain2(int jrnyCode, listOfObjects<TrainInfoPerStation *> *listOfTrains)
{
  while (listOfTrains != nullptr)
  {
    if (listOfTrains->object->journeyCode == jrnyCode)
      return listOfTrains->object;
    listOfTrains = listOfTrains->next;
  }
  return nullptr;
}

listOfObjects<TrainStnInfo *> *expandList(listOfObjects<TrainStnInfo *> *stnInfoList)
{
  listOfObjects<TrainStnInfo *> *currList, *expandedList;
  TrainStnInfo *currInfo;
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
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
      string depStn = currInfo->departureStn;
      string arrStn = currInfo->arrivalStn;
      int depId = currInfo->depIndex;
      int arrId = currInfo->arrIndex;

      for (int i = 0; i < 7; i++)
      {
        if (currInfo->daysOfWeek[i])
        {
          TrainStnInfo *newExpandedElement = new TrainStnInfo(jCode, stSeq, arrTime, depTime, depStn, arrStn, depId, arrId);
          if (newExpandedElement == nullptr)
          {
            // logFile << "Memory allocation failure." << endl;
            cerr << "Memory allocation failure." << endl;
            continue;
          }
          newExpandedElement->setDayOfWeek(i);

          listOfObjects<TrainStnInfo *> *newExpandedListElement = new listOfObjects<TrainStnInfo *>(newExpandedElement);
          if (newExpandedListElement == nullptr)
          {
            // logFile << "Memory allocation failure." << endl;
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

int findTransitTime(TrainStnInfo *train2, TrainStnInfo *train1, int maxTime, listOfObjects<TrainInfoPerStation *> **tempStnInfo)
{
  int train2Day, train1Day;
  for (int i = 0; i < 7; i++)
  {
    if (train1->daysOfWeek[i])
      train1Day = i;
    if (train2->daysOfWeek[i])
      train2Day = i;
  }
  int dayDiff;
  if (train2Day >= train1Day)
    dayDiff = train2Day - train1Day;
  else
    dayDiff = 7 + train2Day - train1Day;
  listOfObjects<TrainInfoPerStation *> *arrTrain = nullptr;
  for (int i = 0; i < DICT_SIZE; i++)
  {
    if (i == train2->depIndex)
    {
      arrTrain = tempStnInfo[i];
      break;
    }
  }
  TrainInfoPerStation *temp = findTrain2(train1->journeyCode, tempStnInfo[train2->depIndex]);
  int newTrainDep = ((train2->depTime) % 100);
  newTrainDep = newTrainDep * 100 / 60;
  int prevTrainArriv = ((temp->arrTime) % 100) * (100 / 60);
  prevTrainArriv = prevTrainArriv * 100 / 60;
  int firstTwoDep = (train2->depTime) / 100;
  firstTwoDep *= 100;
  int firstTwoArr = (temp->arrTime) / 100;
  firstTwoArr *= 100;
  newTrainDep = firstTwoDep + newTrainDep;
  prevTrainArriv = firstTwoArr + prevTrainArriv;
  int v = newTrainDep - prevTrainArriv;
  int k = ((v * 60) / 100);
  int l = ((k) / 60) * 100 + k % 60;
  int transitTime = l + 2400 * (dayDiff);
  return transitTime;
}

void printStnInfo(listOfObjects<TrainStnInfo *> *stnInfoList, int maxTransitTime, listOfObjects<TrainInfoPerStation *> **tempStnInfo)
{
  listOfObjects<TrainStnInfo *> *currList;
  TrainStnInfo *currInfo;
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

  // Expanding information in stnInfoList to get a list of train info
  // in which each element of the list refers to a single day of the
  // week.  This is the list that has to be finally sorted using
  // quicksort.

  currList = stnInfoList;

  // Quicksort(expandedList);
  // QuicksortSimple(expandedList, 0, listLength-1);
  cout << "Journey Found: " << endl;
  while (currList != nullptr)
  {
    currInfo = currList->object;
    if (currInfo != nullptr)
    {
      cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << endl;
      cout << RED << "From: " << RESET;
      cout << currInfo->departureStn << "\t";
      cout << RED << " Departure: " << RESET;
      if (currInfo->depTime == -1)
      {
        cout << "Ends";
      }
      else
      {
        cout << currInfo->depTime;
      }
      cout << "\t";
      cout << GREEN << "Day: " << RESET;
      for (int i = 0; i < 7; i++)
      {
        if (currInfo->daysOfWeek[i])
          cout << days[i] << " ";
      }
      cout << endl;
      cout << RED << "To: " << RESET;
      cout << currInfo->arrivalStn << "\t";
      if (currList->next != nullptr)
      {
        TrainInfoPerStation *temp = findTrain2(currInfo->journeyCode, tempStnInfo[currList->next->object->depIndex]);
        cout << RED << "Arrival: " << RESET;
        if (temp->arrTime == -1)
        {
          cout << "Starts";
        }
        else
        {
          cout << temp->arrTime;
        }
        cout << "\t";
        cout << GREEN << "Day: " << RESET;
        for (int i = 0; i < 7; i++)
        {
          if (currList->object->journeyCode == currList->next->object->journeyCode)
          {
            if (currList->next->object->daysOfWeek[i])
            {
              if (currList->object->daysOfWeek[i])
                cout << days[i] << " ";
              else{
                if(i-1>=0) cout << days[(i - 1)] << " ";
                else cout << days[i-1+7] << " ";
              }
            }
          }
          else
          {
            if (currList->next->object->daysOfWeek[i])
            {
              int transit = findTransitTime(currList->next->object, currList->object, maxTransitTime, tempStnInfo);
              int back = 0;
              int arr = temp->arrTime;
              int dep = currList->next->object->depTime;
              if (dep - transit > 0)
                cout << days[i] << " ";
              else
              {
                int k = dep - transit;
                back++;
                while (k < -2400)
                {
                  back++;
                  k = k + 2400;
                }
                if (i >= back)
                {
                  cout << days[(i - back)] << " ";
                }
                else
                {
                  cout << days[(i - back + 7)] << " ";
                }
              }
            }
          }
        }
        cout << endl;
        if (currList->object->journeyCode != currList->next->object->journeyCode)
        {
          cout << "<---------------- " << RED << "Transit Time: " << RESET << findTransitTime(currList->next->object, currList->object, maxTransitTime, tempStnInfo) << " ------------->" << endl;
        }
      }
    }
    if (currList->next == nullptr)
    {
      cout << endl;
      cout << RED << "At Destination: " << RESET;
      cout << currList->object->arrivalStn << endl;

    }
    currList = currList->next;
  }
  cout << endl;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in

  static int recursionLevel = -1;
  static listOfObjects<TrainStnInfo *> *indirectTrains = nullptr;
  listOfObjects<StationConnectionInfo *> *srcToStations = adjacency[stnNameToIndex.get(srcStnName)->value].toStations;
  recursionLevel++;
  if (srcStnName == destStnName)
  {
    listOfObjects<TrainStnInfo *> *temp_indirectTrains = indirectTrains;
    listOfObjects<TrainStnInfo *> *temp = indirectTrains;
    bool valid = true;
    int change = 0;
    listOfObjects<TrainInfoPerStation *> **tempStnInfo = new listOfObjects<TrainInfoPerStation *> *[DICT_SIZE];
    for (int i = 0; i < DICT_SIZE; i++)
    {
      tempStnInfo[i] = stationInfo[i];
    }
    while (temp_indirectTrains->next != nullptr)
    {
      int transitTime = findTransitTime(temp_indirectTrains->next->object, temp_indirectTrains->object, maxTransitTime, tempStnInfo);
      if (!(0 <= transitTime && transitTime <= maxTransitTime))
      {
        valid = false;
        break;
      }
      temp_indirectTrains = temp_indirectTrains->next;
    }
    while (temp->next != NULL)
    {
      if (temp->object->journeyCode != temp->next->object->journeyCode)
        change++;
      temp = temp->next;
    }
    if (valid && change <= maxStopOvers)
      printStnInfo(indirectTrains, maxTransitTime, tempStnInfo);
    listOfObjects<TrainStnInfo *> *tempTrain1 = indirectTrains;
    while (tempTrain1->next != nullptr)
    {
      tempTrain1 = tempTrain1->next;
    }
    tempTrain1 = nullptr;
    return;
  }
  if (srcToStations == nullptr)
  {
    listOfObjects<TrainStnInfo *> *tempTrain1 = indirectTrains;
    while (tempTrain1->next != nullptr)
    {
      tempTrain1 = tempTrain1->next;
    }
    tempTrain1 = nullptr;
    return;
  }
  listOfObjects<StationConnectionInfo *> *itr_srcToStations = srcToStations;
  while (itr_srcToStations != nullptr)
  {

    listOfObjects<TrainStnInfo *> *trainJourney = nullptr; // list of JourneyCodes of trains departing from source
    listOfObjects<TrainStnInfo *> *itrJourney = nullptr;
    listOfObjects<TrainStnInfo *> *itrJrny = nullptr;

    // storing all journey codes of trains departing from source into trainJourney
    listOfObjects<TrainInfoPerStation *> *Trains = itr_srcToStations->object->trains;

    int num_trains = 0;
    while (Trains != nullptr)
    {
      TrainStnInfo *newTrain = new TrainStnInfo(Trains->object->journeyCode, Trains->object->stopSeq, Trains->object->arrTime, Trains->object->depTime, srcStnName, stnNameToIndex.getKeyAtIndex(itr_srcToStations->object->adjacentStnIndex), stnNameToIndex.get(srcStnName)->value, itr_srcToStations->object->adjacentStnIndex);
      for (int i = 0; i < 7; i++)
      {
        if (Trains->object->daysOfWeek[i])
        {
          TrainStnInfo *cpynewTrain = new TrainStnInfo(Trains->object->journeyCode, Trains->object->stopSeq, Trains->object->arrTime, Trains->object->depTime, srcStnName, stnNameToIndex.getKeyAtIndex(itr_srcToStations->object->adjacentStnIndex), stnNameToIndex.get(srcStnName)->value, itr_srcToStations->object->adjacentStnIndex);
          cpynewTrain->setDayOfWeek(i);
          listOfObjects<TrainStnInfo *> *newTrainlist = new listOfObjects<TrainStnInfo *>(cpynewTrain);

          if (trainJourney == nullptr)
          { // Inserting journey codes into the list trainJourney
            trainJourney = new listOfObjects<TrainStnInfo *>(cpynewTrain);
            itrJourney = trainJourney;
            itrJrny = trainJourney;
          }
          else
          {
            listOfObjects<TrainStnInfo *> *temp = trainJourney;
            while (temp->next != nullptr)
            {
              temp = temp->next;
            }
            temp->next = newTrainlist;
          }
          num_trains++;
        }
      }
      Trains = Trains->next;
    }

    TrainStnInfo **trains = new TrainStnInfo *[num_trains];
    int *jrnyCodes = new int[num_trains];
    int num = 0;
    while (itrJourney != NULL)
    {
      jrnyCodes[num] = itrJourney->object->journeyCode;
      itrJourney = itrJourney->next;
      num++;
    }
    for (int i = 0; i < num_trains; i++)
    {
      trains[i] = findTrain(jrnyCodes[i], trainJourney);
    }
    int i = 0;
    while (itrJrny != nullptr)
    {
      if (indirectTrains == nullptr)
      {
        listOfObjects<TrainStnInfo *> *newTrainInfo = new listOfObjects<TrainStnInfo *>(itrJrny->object);
        indirectTrains = newTrainInfo;
      }
      else
      {
        listOfObjects<TrainStnInfo *> *newIndirectTrain = new listOfObjects<TrainStnInfo *>(itrJrny->object);
        listOfObjects<TrainStnInfo *> *tempTrain = indirectTrains;
        while (tempTrain->next != nullptr)
        {
          tempTrain = tempTrain->next;
        }
        newIndirectTrain->prev = tempTrain;
        tempTrain->next = newIndirectTrain;
      }

      printPlanJourneys(stnNameToIndex.getKeyAtIndex(itr_srcToStations->object->adjacentStnIndex), destStnName, maxStopOvers, maxTransitTime);

      listOfObjects<TrainStnInfo *> *tempTrain1 = indirectTrains;
      if (tempTrain1 == nullptr)
      {
      }
      else if (tempTrain1->next == nullptr)
      {
        indirectTrains = nullptr;
      }
      else
      {
        while (tempTrain1->next->next != nullptr)
        {
          tempTrain1 = tempTrain1->next;
        }
        tempTrain1->next = nullptr;
      }
      itrJrny = itrJrny->next;
      i++;
    }

    itr_srcToStations = itr_srcToStations->next;
  }
  recursionLevel--;
  return;
}

#endif
