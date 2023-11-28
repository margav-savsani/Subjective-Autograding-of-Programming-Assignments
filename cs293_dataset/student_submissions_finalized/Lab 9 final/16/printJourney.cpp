#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// Train information per station
class Info
{
public:
  int journeyCode; // same as train number
  unsigned short stopSeq;
  int stnidx;         // Storing the current index of station in queue
  bool daysOfWeek[7]; // Days of week when this train travels
                      // to/from this station
  int arrTime;        // Arrival time at station; -1 if train starts from here
  int depTime;        // Departure time from station; -1 if train ends here

public:
  Info(int jCode, int stpSq, int aTm, int dTm, bool days[7], unsigned short ss)
  {
    stopSeq = ss;
    journeyCode = jCode;
    stnidx = stpSq;
    arrTime = aTm;
    depTime = dTm;
    for (int i = 0; i < 7; i++)
    {
      daysOfWeek[i] = days[i];
    }
  }

  ~Info() { ; }
};

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  // insert your code here
  int srcidx = stnNameToIndex.get(srcStnName)->value;
  int dstnidx = stnNameToIndex.get(destStnName)->value;

  // This would store my final selected Journey Codes
  listOfObjects<TrainInfoPerStation *> *selected = nullptr;
  listOfObjects<TrainInfoPerStation *> *selected_end = nullptr;

  // My intermediate JCs queue
  listOfObjects<Info *> *queue_start = nullptr;
  listOfObjects<Info *> *queue_end = nullptr;

  // Need to populate the queue first with all the stations connected to the source
  // StationAdjacencyList curr_source = adjacency[srcidx];
  listOfObjects<StationConnectionInfo *> *stns_connected_to_currsrc = adjacency[srcidx].toStations;
  while (stns_connected_to_currsrc != nullptr)
  {
    // Here I have found the station connected to my current source
    // I now need to iterate to cover all the trains with different journey codes
    // leaving the current station

    // Object has a list of trains and the current source stn index
    StationConnectionInfo *curr_dstn_stn = stns_connected_to_currsrc->object;

    // This is a list of the trains that is connecting my current source and the destination
    listOfObjects<TrainInfoPerStation *> *trains_connecting = curr_dstn_stn->trains;
    while (trains_connecting != nullptr)
    {
      int arrTime, deptTime;
      unsigned short seq;
      listOfObjects<TrainInfoPerStation *> *ptr = stationInfo[srcidx];
      while (ptr != nullptr)
      {
        if (ptr->object->journeyCode == trains_connecting->object->journeyCode)
        {
          arrTime = ptr->object->arrTime;
          deptTime = ptr->object->depTime;
          seq = ptr->object->stopSeq;
          break;
        }
        ptr = ptr->next;
      }
      if (stns_connected_to_currsrc->object->adjacentStnIndex == dstnidx)
      {
        // Let's add it to the final list by getting details from the queue_start
        // TrainInfoPerStation *temp = new TrainInfoPerStation(trains_connecting->object->journeyCode, trains_connecting->object->stopSeq, trains_connecting->object->arrTime, trains_connecting->object->depTime);
        TrainInfoPerStation *temp = new TrainInfoPerStation(trains_connecting->object->journeyCode, seq, arrTime, deptTime);
        // Setting the days
        for (int i = 0; i < 7; i++)
        {
          temp->daysOfWeek[i] = trains_connecting->object->daysOfWeek[i];
        }
        if (selected == nullptr)
        {
          selected = new listOfObjects<TrainInfoPerStation *>(temp);
          selected_end = selected;
        }
        else
        {
          // Adding the elements in the list by modifying the corresponding parent and child pointers
          listOfObjects<TrainInfoPerStation *> *to_add_list_object = new listOfObjects<TrainInfoPerStation *>(temp);
          selected_end->next = to_add_list_object;
          to_add_list_object->prev = selected_end;
          selected_end = selected_end->next;
        }
      }
      else
      {
        // I will for now append the train to my queue that I made, note that this part of the function
        // will change for the stations at level more than 1 as then I need to check if the journey code
        // of the previous stn's train and current is matching or not

        // Lets create our custom object that will go into out temporary queue
        Info *to_add;
        to_add = new Info(trains_connecting->object->journeyCode, curr_dstn_stn->adjacentStnIndex, arrTime, deptTime, trains_connecting->object->daysOfWeek, seq);

        // In case my queue was empty I need to initialise my queue_start
        if (queue_start == nullptr)
        {
          queue_start = new listOfObjects<Info *>(to_add);
          queue_end = queue_start;
        }
        else
        {
          // Adding the elements in the list by modifying the corresponding parent and child pointers
          listOfObjects<Info *> *to_add_list_object = new listOfObjects<Info *>(to_add);
          queue_end->next = to_add_list_object;
          to_add_list_object->prev = queue_end;
          queue_end = queue_end->next;
        }
        // Now the present train along with its information have been added, let's move to see
        // the next train in route, by changing the trains_connecting variable
      }
      trains_connecting = trains_connecting->next;
    }

    // Once the above while loop ends that means all the trains for the given journey has been looked at
    // Lets move to the next station connected to the current source stn
    stns_connected_to_currsrc = stns_connected_to_currsrc->next;
  }

  // after the end of the above loop, we have initialised our queue storing all the probable JCs
  // and stnIdx from which a route may exist. Now let's start the mighty BFS, going over element present
  // in the queue and seeing the trains going from it, seeing if JC matchs the queue element, if so
  // add it in the queue else ignore, once all the stations gets exhausted for the current queue element,
  // dequeue it

  // This entire operation ends once the queue gets empty
  while (queue_start != nullptr)
  {
    Info *currstn = queue_start->object;

    // Need to update the queue based on continuation of the JC
    // StationAdjacencyList curr_source = adjacency[currstn->stnidx];
    listOfObjects<StationConnectionInfo *> *stns_connected_to_currsrc = adjacency[currstn->stnidx].toStations;
    bool found_inter = false;
    bool found_end = false;
    while (stns_connected_to_currsrc != nullptr)
    {
      // Here I have found the station connected to my current source
      // I now need to iterate to cover all the trains with different journey codes
      // leaving the current station

      // Object has a list of trains and the current source stn index
      StationConnectionInfo *curr_dstn_stn = stns_connected_to_currsrc->object;

      // This is a list of the trains that is connecting my current source and the destination
      listOfObjects<TrainInfoPerStation *> *trains_connecting = curr_dstn_stn->trains;
      while (trains_connecting != nullptr)
      {
        // Now we iterate over all the trains from the curr_dest and see if current temp dstn have the same
        // JC or not
        // Check if JC matchs
        if (trains_connecting->object->journeyCode == currstn->journeyCode)
        {
          // we will break the loop and take this element to the end of the queue if it is not same
          // as the final destination we want to go, else simply add it to the final list
          // of connecting trains
          if (stns_connected_to_currsrc->object->adjacentStnIndex == dstnidx)
          {
            // Let's add it to the final list by getting details from the queue_start
            TrainInfoPerStation *temp = new TrainInfoPerStation(queue_start->object->journeyCode, queue_start->object->stopSeq, queue_start->object->arrTime, queue_start->object->depTime);
            // Setting the days
            for (int i = 0; i < 7; i++)
            {
              temp->daysOfWeek[i] = queue_start->object->daysOfWeek[i];
            }
            if (selected == nullptr)
            {
              selected = new listOfObjects<TrainInfoPerStation *>(temp);
              selected_end = selected;
            }
            else
            {
              // Adding the elements in the list by modifying the corresponding parent and child pointers
              listOfObjects<TrainInfoPerStation *> *to_add_list_object = new listOfObjects<TrainInfoPerStation *>(temp);
              selected_end->next = to_add_list_object;
              to_add_list_object->prev = selected_end;
              selected_end = selected_end->next;
            }
            found_end = true;
            break;
          }
          else
          {
            queue_start->object->stnidx = stns_connected_to_currsrc->object->adjacentStnIndex;
            queue_end->next = queue_start;
            queue_start->prev = queue_end;
            queue_start = queue_start->next;
            queue_end = queue_end->next;

            queue_end->next = nullptr;
            queue_start->prev = nullptr;
          }
          found_inter = true;
          break;
        }
        if (found_end || found_inter)
        {
          break;
        }
        // Now the present train did not match the JC, let's move to see
        // the next train in route, by changing the trains_connecting variable
        trains_connecting = trains_connecting->next;
      }
      if (found_end || found_inter)
      {
        break;
      }
      // Once the above while loop ends that means all the trains for the given journey has been looked at
      // Lets move to the next station connected to the current source stn
      stns_connected_to_currsrc = stns_connected_to_currsrc->next;
    }
    if (!found_inter)
    {
      listOfObjects<Info *> *temp = queue_start;
      queue_start = queue_start->next;
      delete temp;
      if (queue_start != nullptr)
      {
        queue_start->prev = nullptr;
      }
    }
  }

  // Hopefully if everything went well we have recieved our list of trains
  // Lets send it to print and see what happens
  if (selected != nullptr)
  {
    printStationInfo(selected);
  }
  else
  {
    cout << "No direct journey found" << endl;
  }

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

  return;
}

#endif