#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here

  cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

  // saving the indices of source and destination station
  int source_stn = stnNameToIndex.get(srcStnName)->value;
  int dest_stn = stnNameToIndex.get(destStnName)->value;

  // queue of trains for BFS implementation
  //2 queues are maintained in parallel to keep 2 information, thats it
  listOfObjects<TrainInfoPerStation *> *queue_of_trains = nullptr;
  listOfObjects<TrainInfoPerStation *> *tail_train = nullptr;
  listOfObjects<int> *queue_of_station = nullptr;
  listOfObjects<int> *tail_station = nullptr;

  // Storing the those trains which are known to leave from the source station and also know to arrive at the given destination station.
  // But note that it may be possible that source destination is actually the destination station, we have to check that don't go by the name of the station given
  listOfObjects<StationConnectionInfo *> *currentNode = adjacency[source_stn].toStations;
  while (currentNode != nullptr)
  {
    listOfObjects<TrainInfoPerStation *> *current_Train = currentNode->object->trains;
    while (current_Train != nullptr)
    {
      int journey_code = current_Train->object->journeyCode;
      listOfObjects<StationConnectionInfo *> *currentDestNode = adjacency[dest_stn].fromStations;
      while (currentDestNode != nullptr)
      {
        bool foundnode = false;
        listOfObjects<TrainInfoPerStation *> *current_dest_Train = currentDestNode->object->trains;
        while (current_dest_Train != nullptr)
        {
          if (current_dest_Train->object->journeyCode == journey_code)
          {
            listOfObjects<TrainInfoPerStation *> *x = new listOfObjects<TrainInfoPerStation *>(current_Train->object);
            listOfObjects<int> *y = new listOfObjects<int>(currentNode->object->adjacentStnIndex);
            if (tail_train == nullptr)
            {
              queue_of_trains = x;
              tail_train = x;
              queue_of_station = y;
              tail_station = y;
            }
            else
            {
              tail_train->next = x;
              x->prev = tail_train;
              tail_station->next = y;
              y->prev = tail_station;
              tail_station = y;
              tail_train = x;
            }
            foundnode = true;
            break;
            // add current train to the queue(done)
          }
          current_dest_Train = current_dest_Train->next;
        }
        if (foundnode)
          break;
        currentDestNode = currentDestNode->next;
      }
      current_Train = current_Train->next;
    }
    currentNode = currentNode->next;
  }

  listOfObjects<int> *journeyCodes_passed = nullptr; // This stores the journey codes which are finally selected to be printed and the corresponding train from intersection_trains will be printed
  listOfObjects<int> *tail_journeyCodes_passed = nullptr;

  // Implementing BFS to process the queue and print those journeys which connect source and destination station

  while (queue_of_trains != nullptr)
  {
    TrainInfoPerStation head_train = *(queue_of_trains->object);
    int head_dest_station = queue_of_station->object;
    // Case-1: if the station of the head of the queue is where are our final destination is. so add it in the list to be printed
    if (head_dest_station == dest_stn)
    {
      listOfObjects<int> *y = new listOfObjects<int>(head_train.journeyCode);
      if (journeyCodes_passed == nullptr)
      {
        journeyCodes_passed = y;
        tail_journeyCodes_passed = y;
      }
      else
      {
        tail_journeyCodes_passed->next = y;
        y->prev = nullptr;
        tail_journeyCodes_passed = y;
      }
      // add the train to be printed
      queue_of_station = queue_of_station->next;
      queue_of_trains = queue_of_trains->next;
    }
    // Case2: if the final destination is not the one, then run over the list of to trains of the intermediate station,remove the head element and add only if the train corresponding to the journey code is found
    // else if (head_dest_station == -1)
    //   cout << "index -1 actually printed\n";
    else
    {
      currentNode = adjacency[head_dest_station].toStations;
      bool found = false;
      while (currentNode != nullptr)
      {
        listOfObjects<TrainInfoPerStation *> *current_Train = currentNode->object->trains;
        while (current_Train != nullptr)
        {
          if (current_Train->object->journeyCode == head_train.journeyCode)
          {
            found = true;
            listOfObjects<TrainInfoPerStation *> *x = new listOfObjects<TrainInfoPerStation *>(current_Train->object);
            listOfObjects<int> *y = new listOfObjects<int>(currentNode->object->adjacentStnIndex);
            tail_train->next = x;
            x->prev = tail_train;
            tail_station->next = y;
            y->prev = tail_station;
            tail_station = y;
            tail_train = x;
            queue_of_station = queue_of_station->next;
            queue_of_trains = queue_of_trains->next;
            queue_of_station->prev = nullptr;
            queue_of_trains->prev = nullptr;
            break;
          }
          current_Train = current_Train->next;
        }
        if (found)
          break;
        currentNode = currentNode->next;
      }

      if (currentNode == nullptr)
      {
        queue_of_station = queue_of_station->next;
        queue_of_trains = queue_of_trains->next;
        
      }
    }
  }

  // creating the list of trains to be printed
  listOfObjects<TrainInfoPerStation *> *print_trains = nullptr;
  listOfObjects<TrainInfoPerStation *> *tail_print_trains = nullptr;
  //just traversing the intersection of trains to find the train to be printed when journey code is given
  listOfObjects<int> *traversing_node = journeyCodes_passed;
  while (traversing_node != nullptr)
  {
    listOfObjects<TrainInfoPerStation *> *currentTrain = stationInfo[source_stn];
    while (currentTrain != nullptr)
    {
      if (currentTrain->object->journeyCode == traversing_node->object)
        break;
      currentTrain = currentTrain->next;
    }
    if(currentTrain != nullptr){
      listOfObjects<TrainInfoPerStation *> *x = new listOfObjects<TrainInfoPerStation *>(currentTrain->object);
    
    if (tail_print_trains == nullptr)
    {
      print_trains = x;
      tail_print_trains = x;
    }
    else
    {
      tail_print_trains->next = x;
      x->prev = tail_print_trains;
      tail_print_trains = x;
    }
    }
    traversing_node = traversing_node->next;
  }
  if (print_trains == nullptr)
    cout << "No direct journeys found" << endl;
  else
    printStationInfo(print_trains);

  return;
}

#endif
