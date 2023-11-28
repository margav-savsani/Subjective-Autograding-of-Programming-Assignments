#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;
int count = 0;

// Class Helpful for printing the information
// it contains Traininfo perstation along with other parameters like start station , end station ,
// and  also type of journey in Traininfostation
class PRINT_STAT
{

public:
  TrainInfoPerStation *a;

  PRINT_STAT(TrainInfoPerStation b)
  {
    a = new TrainInfoPerStation(b);
  }
  int transit_time;
  int start_station;
  int end_station;
  int end_time;
  int type;
  // type =0 start station
  // type =2 station without changing train at source station
  // type =1 station with changing train at source station
};

// Print function to print journeys
// Various colors are used and several useful info. are printed
// A description is printed OF train to take followed by a text description containing path to follow
// like train to be continued or changed along with no of stops.
void myprintStationInfo(listOfObjects<PRINT_STAT *> *stnInfoList, Dictionary<int> stnNameToIndex)
{
  int count = 0;
  listOfObjects<PRINT_STAT *> *currList;
  TrainInfoPerStation *currInfo;
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  currList = stnInfoList;
  while (currList != nullptr)
  {

    currInfo = currList->object->a;
    if (currInfo != nullptr)
    {
      cout << GREEN << "Day(s): " << RESET;
      for (int i = 0; i < 7; i++)
      {
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
      if (currList->object->type == 0)
        cout << RESET << "START YOUR JOURNEY FROM " << GREEN << stnNameToIndex.getKeyAtIndex(currList->object->start_station) << RESET << " TO reach " << GREEN << stnNameToIndex.getKeyAtIndex(currList->object->end_station) << RESET << " at " << BLUE << currList->object->end_time << endl;
      else if (currList->object->type == 2)
      {
        cout << RESET << "CONTINUE YOUR JOURNEY IN SAME TRAIN from " << GREEN << stnNameToIndex.getKeyAtIndex(currList->object->start_station) << RESET << " TO reach " << GREEN << stnNameToIndex.getKeyAtIndex(currList->object->end_station) << RESET << " at " << BLUE << currList->object->end_time << endl;
      }
      else if (currList->object->type == 1)
      {
        count++;
        cout << RESET << "CHANGE YOUR JOURNEY from " << GREEN << stnNameToIndex.getKeyAtIndex(currList->object->start_station) << RESET << " TO reach " << GREEN << stnNameToIndex.getKeyAtIndex(currList->object->end_station) << RESET << " at " << BLUE << currList->object->end_time << endl;
        cout << RESET << "TRANSIT TIME IS " << BLUE << currList->object->transit_time << endl;
      }
    }

    currList = currList->next;
  }
  cout << RESET<<"NO OF STOPS is " <<BLUE<< count << endl;
  cout << endl
       << "===============================================" << endl
       << RESET;
}

// function declared here but is defined below the main function and is described there
void find_journey(listOfObjects<PRINT_STAT *> *journey_list, int jrny, int current_stat, int end_index,
                  int maxStopovers, int max_Time, int reach_time, StationAdjacencyList *adjacency,
                  Dictionary<int> stnNameToIndex, Planner *myplanner,
                  listOfObjects<TrainInfoPerStation *> **stationInfo, int day);

// function doing the DFS
// This function takes journey one by one from source station and pass it to helper function
// for completions. The list is expanded here itself by passing it for different days seprately
// and according managing the daysofweek[] of expanded list.
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  int start_index = stnNameToIndex.get(srcStnName)->value;
  int end_index = stnNameToIndex.get(destStnName)->value;
  // insert your code here
  // cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  // return;

  // queue of tostations from source station
  listOfObjects<StationConnectionInfo *> *myqueue = adjacency[start_index].toStations;
  while (myqueue != nullptr)
  {
    // taking trains corresponding to particular index
    listOfObjects<TrainInfoPerStation *> *trains = myqueue->object->trains;
    while (trains != nullptr)
    {
      // expanding the list
      for (int i = 0; i < 7; i++)
      {
        // checking if trains runs on th ith day
        if (trains->object->daysOfWeek[i] == 1)
        {
          // making the object to be passed in linked list of journeys
          TrainInfoPerStation b = *trains->object;
          // Traininfo holds the TraininfoPerstation at the destination index. This is used to take out
          // time and date at destination  for passing in helper function
          TrainInfoPerStation Train_info = *trains->object;
          // Taking stationInfo list of adjacentindex for finding Train_Info
          listOfObjects<TrainInfoPerStation *> *curr_stat_info = stationInfo[myqueue->object->adjacentStnIndex];
          // finding Train_info by matching journeycode in curr_stat_info list
          while (curr_stat_info != nullptr)
          {
            if (curr_stat_info->object->journeyCode == trains->object->journeyCode)
            {
              Train_info = *curr_stat_info->object;
              break;
            }
            curr_stat_info = curr_stat_info->next;
          }
          // variable holding day at destination station
          int z;
          // taking the case where train can possibly arrive destination at that day only
          // and checking for first possible day of destination and according updating days of week
          // of Train_info
          if (b.depTime < Train_info.arrTime)
          {
            z = i;
            while (Train_info.daysOfWeek[z] == 0)
            {
              z = (z + 1) % 7;
            }
            for (int j = 0; j < 7; j++)
            {
              if (i != j)
              {
                Train_info.daysOfWeek[j] = 0;
              }
            }
          }
          // taking the case where train can possibly arrive destination at next day only i.e, dest_time<source_time
          // and checking for first possible day of destination and according updating days of week
          // of Train_info.
          else
          {
            z = (i + 1) % 7;
            while (Train_info.daysOfWeek[z] == 0)
            {
              z = (z + 1) % 7;
            }
            for (int j = 0; j < 7; j++)
            {
              if (z != j)
              {
                Train_info.daysOfWeek[j] = 0;
              }
            }
          }
          // setting days of week of object passed into link list i.e, TraininfoperStation
          // at source station
          for (int k = 0; k < 7; k++)
          {
            b.daysOfWeek[k] = (k == i);
          }
          // creating object helpful for printing
          // And setting its attributes like start_staion, end_station,end_time,type of journey,
          // and Traininfo per station accordingly
          PRINT_STAT ii(b);
          ii.type = 0;
          ii.end_time = Train_info.arrTime;
          ii.start_station = start_index;
          ii.end_station = myqueue->object->adjacentStnIndex;
          listOfObjects<PRINT_STAT *> *a = new listOfObjects<PRINT_STAT *>(&ii);
          // passing the linked list for completion through DFS.
          find_journey(a, trains->object->journeyCode, myqueue->object->adjacentStnIndex, end_index, maxStopOvers, maxTransitTime,
                       Train_info.arrTime, adjacency, stnNameToIndex, this, stationInfo, z);
          delete (a);
        }
      }
      trains = trains->next;
    }

    myqueue = myqueue->next;
  }
}

void find_journey(listOfObjects<PRINT_STAT *> *journey_list, int jrny, int current_stat, int end_index,
                  int maxStopovers, int max_Time, int reach_time, StationAdjacencyList *adjacency, Dictionary<int> stnNameToIndex, Planner *myplanner, listOfObjects<TrainInfoPerStation *> **stationInfo, int day)
{
  // base_case if no of stop_overs are violated.
  if (maxStopovers < 0 and current_stat != end_index)
  {
    return;
  }
  // printing the data if found the end station within the specific no of stops and wait time.
  if (current_stat == end_index and maxStopovers >= 0)
  {

    myprintStationInfo(journey_list, stnNameToIndex);
    return;
  }

  // Traininfo holds the TraininfoPerstation at the destination index. This is used to take out
  // time and date at destination  for passing in recursion layer.
  TrainInfoPerStation *Train_info;
  // finding the tail of the linked list
  listOfObjects<PRINT_STAT *> *a = journey_list;
  while (a->next != nullptr)
  {
    a = a->next;
  }
  // queue of tostations from current station
  listOfObjects<StationConnectionInfo *> *myqueue = adjacency[current_stat].toStations;

  while (myqueue != nullptr)
  {
    // taking trains corresponding to particular adjacent index
    listOfObjects<TrainInfoPerStation *> *trains = myqueue->object->trains;

    // iterating over all trains for completions.
    while (trains != nullptr)
    {
      // Taking stationInfo list of adjacentindex for finding Train_Info
      listOfObjects<TrainInfoPerStation *> *curr_stat_info = stationInfo[myqueue->object->adjacentStnIndex];
      // finding Train_info by matching journeycode in curr_stat_info list
      while (curr_stat_info != nullptr)
      {
        if (curr_stat_info->object->journeyCode == trains->object->journeyCode)
        {
          Train_info = curr_stat_info->object;
          break;
        }
        curr_stat_info = curr_stat_info->next;
      }
      // x holds the maximum time from now till which journey is possible and y contains the day of journey.
      int x = max_Time * 100 + reach_time + 1;
      int y = day;
      // if arr time is more than dept time it means the train will be stopped at station at 2400
      if (trains->object->depTime < trains->object->arrTime)
      {
        y++;
      }
      bool train_found = false;
      // iterating till we are in the requied waiting time
      while (x > 0)
      {
        // checking for the train  condition of arrival and departure time
        if ((trains->object->depTime < x && trains->object->daysOfWeek[y] == 1))
        {
          train_found = true;
          // for the same day journey our train should go after we have reached station
          // by the previous train
          if (y != day || trains->object->depTime > reach_time)
          {
            // making the TraininfoPerstation object for the linked list
            TrainInfoPerStation c = *trains->object;
            listOfObjects<TrainInfoPerStation *> *b = new listOfObjects<TrainInfoPerStation *>(&c);
            // setting up its days of week manually for insertion in linked list
            for (int j = 0; j < 7; j++)
            {
              if (y != j)
              {
                b->object->daysOfWeek[j] = 0;
              }
            }
            // taking the case where train can possibly arrive destination at departure day i.e, dest_time>source_time
            // and checking for first possible day of destination
            int z = y;
            if (Train_info->arrTime > trains->object->depTime)
            {
              while (Train_info->daysOfWeek[z] == 0)
              {
                z = (z + 1) % 7;
              }
            }
            // taking the case where train can possibly arrive destination at next day only i.e,
            // dest_time<source_time and checking for first possible day of destination
            else
            {
              z = (y + 1) % 7;
              while (Train_info->daysOfWeek[z] == 0)
              {
                z = (z + 1) % 7;
              }
            }
            // creating object helpful for printing
            // And setting its attributes like start_staion, end_station,end_time,type of journey
            //,transition_time and Traininfo per station accordingly TYPE 1 implies change of journey
            PRINT_STAT ii(*b->object);
            ii.type = 1;
            // convert time to mins to get the transition time
            int min_d = 60 * (trains->object->depTime / 100) + trains->object->depTime % 100;
            int min_a = 60 * (reach_time / 100) + reach_time % 100;
            // finding conversion to transition time by subtractioning in minutess and
            // converting back to 2400 format
            ii.transit_time = 100 * ((24 * 60 * ((y - day + 7) % 7) + min_d - min_a) / 60) + (24 * 60 * ((y - day + 7) % 7) + min_d - min_a) % 60;
            ii.end_time = Train_info->arrTime;
            ii.start_station = current_stat;
            ii.end_station = myqueue->object->adjacentStnIndex;
            // putting the element at last of linked list
            a->next = new listOfObjects<PRINT_STAT *>(&ii);
            a->next->prev = a;
            // variable to hold journey day of the previous train continuing from the new station
            int k = 0;
            // checking for the train is not the same as the previous one
            // by matching journey code and its day with the continuing journey day.
            if (Train_info->journeyCode == jrny)
            {
              k = day;
              while (trains->object->daysOfWeek[k] == 0)
              {
                k = (k + 1) % 7;
              }
            }
            // passing the list further for completion if transit time is in range and it is not the continue
            // of the previous journey with max_stop-1 as parameter
            if ((y != k || Train_info->journeyCode != jrny) && (ii.transit_time <= 100 * max_Time))
              find_journey(journey_list, Train_info->journeyCode, myqueue->object->adjacentStnIndex, end_index, maxStopovers - 1, max_Time,
                           Train_info->arrTime, adjacency, stnNameToIndex, myplanner, stationInfo, z);
          }
        }
        // Resetting the NEXT of tail again to null for further loops
        if (train_found == true)
        {
          a->next = nullptr;
        }

        x -= 2400;
        y = (y + 1) % 7;
      }
      // dealing the case of continued journey
      if (trains->object->journeyCode == jrny)
      {

        int y = day;
        while (trains->object->daysOfWeek[y] == 0)
        {
          y = (y + 1) % 7;
        }
         // making the TraininfoPerstation object for the linked list
        TrainInfoPerStation c = *trains->object;
        listOfObjects<TrainInfoPerStation *> *b = new listOfObjects<TrainInfoPerStation *>(&c);           
        // setting up its days of week manually for insertion in linked list
         for (int j = 0; j < 7; j++)
        {
          if (y != j)
          {
            b->object->daysOfWeek[j] = 0;
          }
        }

        train_found = true;
        int z = y;
      // taking the case where train can possibly arrive destination at departure day i.e, dest_time>source_time
      // and checking for first possible day of destination
        if (Train_info->arrTime > trains->object->depTime)
        {
          while (Train_info->daysOfWeek[z] == 0)
          {
            z = (z + 1) % 7;
          }
        }
        else
        // taking the case where train can possibly arrive destination at next day only i.e,
        // dest_time<source_time and checking for first possible day of destination
        {
          z = (y + 1) % 7;
          while (Train_info->daysOfWeek[z] == 0)
          {
            z = (z + 1) % 7;
          }
        }
        // creating object helpful for printing
        // And setting its attributes like start_staion, end_station,end_time,type of journey
        //,transition_time and Traininfo per station accordingly TYPE 2 implies NO change of journey
        PRINT_STAT ii(*b->object);
        ii.type = 2;
        ii.end_time = Train_info->arrTime;
        ii.start_station = current_stat;
        ii.end_station = myqueue->object->adjacentStnIndex;
        a->next = new listOfObjects<PRINT_STAT *>(&ii);
        a->next->prev = a;
       // passing the list further for completion with max_stop as parameter
        find_journey(journey_list, Train_info->journeyCode, myqueue->object->adjacentStnIndex, end_index, maxStopovers, max_Time,
                     Train_info->arrTime, adjacency, stnNameToIndex, myplanner, stationInfo, z);

        // Resetting the NEXT of tail again to null for further loops
        if (train_found == true)
        {
          a->next = nullptr;
        }
      }
    // iterationg over the trains
      trains = trains->next;
    }
      // iterationg over the next stations
    myqueue = myqueue->next;
  }
  return;
}

#endif
