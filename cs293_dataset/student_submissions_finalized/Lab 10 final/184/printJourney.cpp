#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
void print(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  listOfObjects<TrainInfoPerStation *> *currList, *expandedList;
  TrainInfoPerStation *currInfo;
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

  // Expanding information in stnInfoList to get a list of train info
  // in which each element of the list refers to a single day of the
  // week.  This is the list that has to be finally sorted using
  // quicksort.

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
            // logFile << "Memory allocation failure." << endl;
            cerr << "Memory allocation failure." << endl;
            continue;
          }
          newExpandedElement->setDayOfWeek(i);

          listOfObjects<TrainInfoPerStation *> *newExpandedListElement = new listOfObjects<TrainInfoPerStation *>(newExpandedElement);
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

  // Quicksort(expandedList);
  //  QuicksortSimple(expandedList, 0, listLength-1);

  currList = expandedList;
  while (currList != nullptr)
  {
    currInfo = currList->object;
    if (currInfo != nullptr)
    {
      cout << GREEN << "Day(s): " << RESET;
      for (int i = 0; i < 7; i++)
      {
        // cout << currInfo->daysOfWeek[i];
        if (currInfo->daysOfWeek[i])
          cout << days[i] << " ";
      }
      cout << endl;
      cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << "\t";
      cout << RED << "Arr: " << RESET;
      if (currInfo->arrTime == -1)
      {
        cout << "Starts";
      }
      else
      {
        cout << currInfo->arrTime;
      }
      cout << RED << " Dep: " << RESET;
      if (currInfo->depTime == -1)
      {
        cout << "Ends";
      }
      else
      {
        cout << currInfo->depTime;
      }
      cout << endl;
    }
    if (currList->next != nullptr)
    {
      cout << "trasit time: ";
      int diff = 0;
      int n1, n2;
      for (int i = 0; i < 7; i++)
      {
        if (currList->object->daysOfWeek[i])
          n1 = i;
        // cout << ;
      }
      for (int i = 0; i < 7; i++)
      {
        if (currList->next->object->daysOfWeek[i])
          n2 = i;
      }
      diff = currList->next->object->arrTime - currList->object->depTime + ((7 + (n2 - n1)) % 7) * 2400;
      cout << diff << endl;
    }
    currList = currList->next;
  }
  cout << endl;
}
void printdirect(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  listOfObjects<TrainInfoPerStation *> *currList, *expandedList;
  TrainInfoPerStation *currInfo;
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

  // Expanding information in stnInfoList to get a list of train info
  // in which each element of the list refers to a single day of the
  // week.  This is the list that has to be finally sorted using
  // quicksort.

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
            // logFile << "Memory allocation failure." << endl;
            cerr << "Memory allocation failure." << endl;
            continue;
          }
          newExpandedElement->setDayOfWeek(i);

          listOfObjects<TrainInfoPerStation *> *newExpandedListElement = new listOfObjects<TrainInfoPerStation *>(newExpandedElement);
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

  // Quicksort(expandedList);
  //  QuicksortSimple(expandedList, 0, listLength-1);

  currList = expandedList;
  while (currList != nullptr)
  {
    currInfo = currList->object;
    if (currInfo != nullptr)
    {
      cout << GREEN << "Day(s): " << RESET;
      for (int i = 0; i < 7; i++)
      {
        // cout << currInfo->daysOfWeek[i];
        if (currInfo->daysOfWeek[i])
          cout << days[i] << " ";
      }
      cout << endl;
      cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << "\t";
      cout << RED << "Arr: " << RESET;
      if (currInfo->arrTime == -1)
      {
        cout << "Starts";
      }
      else
      {
        cout << currInfo->arrTime;
      }
      cout << RED << " Dep: " << RESET;
      if (currInfo->depTime == -1)
      {
        cout << "Ends";
      }
      else
      {
        cout << currInfo->depTime;
      }
      cout << endl;
    }
    currList = currList->next;
  }
  cout << endl;
}
void printplan(int source, int dest, int maxstops, int maxtran, listOfObjects<TrainInfoPerStation *> *listing, StationAdjacencyList adjacency, listOfObjects<TrainInfoPerStation *> *stationInfo, Dictionary<int> stnNameToIndex)
{
}
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here

  // cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  static int count = 0; // count is to count no of direct journeys fron source to destination station.
  static int jrny_code = 0;
  static listOfObjects<TrainInfoPerStation *> *listing = nullptr;

  Entry<int> *source = stnNameToIndex.get(srcStnName);
  int source_index = source->value; // storing index of the source station
  Entry<int> *dest = stnNameToIndex.get(destStnName);
  int dest_index = dest->value; // storing index of the destination station

  // static int j_code=0;
  if (maxStopOvers == 0)
  {
    listOfObjects<StationConnectionInfo *> *to = adjacency[source_index].toStations;
    while (to != nullptr)
    {
      int adj = to->object->adjacentStnIndex;
      if (adj == dest_index)
      {
        // cout << "found" << endl;
        listOfObjects<TrainInfoPerStation *> *each = to->object->trains;
        while (each != nullptr)
        {
          int j_code = each->object->journeyCode;
          int past_code = jrny_code; // to store the previous code so to restore

          listOfObjects<TrainInfoPerStation *> *last2 = listing;
          while (last2 != nullptr && last2->next != nullptr)
            last2 = last2->next;

          if (listing == nullptr)
          {
            listing = new listOfObjects<TrainInfoPerStation *>(each->object);
          }
          else
          {
            listOfObjects<TrainInfoPerStation *> *last1 = listing;
            while (last1->next != nullptr)
              last1 = last1->next;
            listOfObjects<TrainInfoPerStation *> *add = new listOfObjects<TrainInfoPerStation *>(each->object);
            last1->next = add;
          }
          // cout << "jrnycode: " << jrny_code << endl;
          if (jrny_code == 0 || j_code == jrny_code)
          {
            printdirect(listing);
            cout << "**************************************************" << endl;
            count++;
          }
          // cout << (last2->next == nullptr) << endl;
          // cout << "(last2 == nullptr):" << (last2 == nullptr) << endl;
          // cout << "(listing == nullptr): " << (listing == nullptr) << endl;
          // cout << (last2 == listing) << endl;
          // listing = last2;
          if (last2 != nullptr)
            last2->next = nullptr;
          else
            listing = nullptr;
          each = each->next;
        }
      }
      else
      {
        // cout << "not found" << endl;
        listOfObjects<TrainInfoPerStation *> *each = to->object->trains;
        while (each != nullptr)
        {
          int j_code = each->object->journeyCode;
          int past_code = jrny_code; // to store the previous code so to restore

          listOfObjects<TrainInfoPerStation *> *last2 = listing; // to store the prev listing to restore
          while (last2 != nullptr && last2->next != nullptr)
            last2 = last2->next;

          if (listing == nullptr)
          {
            listing = new listOfObjects<TrainInfoPerStation *>(each->object);
          }
          else
          {
            listOfObjects<TrainInfoPerStation *> *last1 = listing;
            while (last1->next != nullptr)
              last1 = last1->next;
            listOfObjects<TrainInfoPerStation *> *add = new listOfObjects<TrainInfoPerStation *>(each->object);
            last1->next = add;
          }
          // cout << "jrnycode: " << jrny_code << endl;
          if (jrny_code == 0) // 1st stop after source station
          {
            // cout << "hello1" << endl;
            jrny_code = j_code;
            // cout << "jrnycode: " << jrny_code << endl;
            //  printdirect(listing);
            printPlanJourneys(stnNameToIndex.getKeyAtIndex(adj), destStnName, maxStopOvers, maxTransitTime);
          }
          else if (j_code == jrny_code) // should not count as a stop over.
          {
            // cout << "hello2" << endl;
            printPlanJourneys(stnNameToIndex.getKeyAtIndex(adj), destStnName, maxStopOvers, maxTransitTime);
          }
          else
          {
            // cout << "hello3" << endl;
          }
          // cout << (last2->next == nullptr) << endl;
          // cout << "(last2 == nullptr):" << (last2 == nullptr) << endl;
          // cout << "(listing == nullptr): " << (listing == nullptr) << endl;
          // cout << (last2 == listing) << endl;
          // listing = last2;
          if (last2 != nullptr)
            last2->next = nullptr;
          else
            listing = nullptr;
          jrny_code = past_code;
          // cout << jrny_code << endl;
          each = each->next;
        }
      }
      to = to->next;
    }
    if (count == 0)
    {
      cout << RED << "NOT FOUND" << RESET << endl;
    }
  }
  else
  {
    listOfObjects<StationConnectionInfo *> *to = adjacency[source_index].toStations;
    while (to != nullptr)
    {
      int adj = to->object->adjacentStnIndex;
      if (adj == dest_index) // direct without even stops for same journey code
      {
        listOfObjects<TrainInfoPerStation *> *each = to->object->trains;
        while (each != nullptr)
        {
          listOfObjects<TrainInfoPerStation *> *last2 = listing; // to store the previous listing so to restore
          while (last2 != nullptr && last2->next != nullptr)
            last2 = last2->next;

          if (listing == nullptr)
          {
            listing = new listOfObjects<TrainInfoPerStation *>(each->object);
          }
          else
          {
            listOfObjects<TrainInfoPerStation *> *last1 = listing;
            while (last1->next != nullptr)
              last1 = last1->next;
            listOfObjects<TrainInfoPerStation *> *add = new listOfObjects<TrainInfoPerStation *>(each->object);
            last1->next = add;
          }
          printdirect(listing);
          cout << "***********************************************" << endl;
          count++; // found a journey
          // listing = last2;
          if (last2 != nullptr)
            last2->next = nullptr;
          else
            listing = nullptr;
          each = each->next;
        }
      }
      else
      {
        listOfObjects<TrainInfoPerStation *> *each = to->object->trains;
        while (each != nullptr)
        {
          int j_code = each->object->journeyCode;
          int past_code = jrny_code; // to store the previous code so to restore

          listOfObjects<TrainInfoPerStation *> *last2 = listing; // to store the previous listing so to restore
          while (last2 != nullptr && last2->next != nullptr)
            last2 = last2->next;

          listOfObjects<TrainInfoPerStation *> *last1 = listing;
          while (last1 != nullptr && last1->next != nullptr)
            last1 = last1->next;
          if (listing == nullptr)
          {
            // cout << "hello1" << endl;
            listing = new listOfObjects<TrainInfoPerStation *>(each->object);
          }
          else
          {
            // cout << "hello2";
            listOfObjects<TrainInfoPerStation *> *last1 = listing;
            while (last1->next != nullptr)
              last1 = last1->next;
            listOfObjects<TrainInfoPerStation *> *add = new listOfObjects<TrainInfoPerStation *>(each->object);
            last1->next = add;
          }

          if (past_code == 0) // 1st stop after source station
          {
            jrny_code = j_code;
            printPlanJourneys(stnNameToIndex.getKeyAtIndex(adj), destStnName, maxStopOvers, maxTransitTime);
          }
          else if (j_code == jrny_code) // should not count as a stop over.
          {
            printPlanJourneys(stnNameToIndex.getKeyAtIndex(adj), destStnName, maxStopOvers, maxTransitTime);
          }
          else // should count stop over
          {
            printPlanJourneys(stnNameToIndex.getKeyAtIndex(adj), destStnName, maxStopOvers - 1, maxTransitTime);
          }

          // listing = last2;
          if (last2 != nullptr)
            last2->next = nullptr;
          else
            listing = nullptr;
          jrny_code = past_code;
          each = each->next;
        }
      }
      to = to->next;
    }
    if (count == 0)
    {
      cout << RED << "NOT FOUND" << RESET << endl;
    }
  }
  return;
}

#endif
