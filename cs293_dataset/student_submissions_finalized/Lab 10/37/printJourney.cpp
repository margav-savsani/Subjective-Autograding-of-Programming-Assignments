#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP
#ifndef PLANNER_H
#include "planner.h"
#endif
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
void find_indirect(listOfObjects<TrainInfoPerStation *> *&ans, listOfObjects<TrainInfoPerStation *> *&end, int srci, int desti, int ind[], int i, int jrnycodes[DICT_SIZE][10], StationAdjacencyList adjacency[])
{
  for (int j = 0; j < i; j++)
  {
    listOfObjects<StationConnectionInfo *> *curr = adjacency[ind[j]].toStations;
    int tempind[DICT_SIZE], ti = 0, tjrnycodes[DICT_SIZE][10];
    while (curr != NULL)
    {

      int index_of_this_station = curr->object->adjacentStnIndex;

      if (index_of_this_station == desti)
      {

        listOfObjects<TrainInfoPerStation *> *curr_train = curr->object->trains;

        while (curr_train != nullptr)
        {
          bool found = false;

          for (int k = 1; k <= jrnycodes[j][0]; k++)
          {

            if (curr_train->object->journeyCode == jrnycodes[j][k])
            { // checking if the journeycode is same as previous station's train
              found = true;
              break;
            }
          }
          if (found)
          {

            if (ans == nullptr)
            {
              ans = new listOfObjects<TrainInfoPerStation *>(curr_train->object);
              end = ans;
              curr_train = curr_train->next;
              continue;
            }

            end->next = new listOfObjects<TrainInfoPerStation *>(curr_train->object);
            end = end->next;
          }
          curr_train = curr_train->next;
        }
      }

      else
      {

        listOfObjects<TrainInfoPerStation *> *curr_train = curr->object->trains;
        tempind[ti] = index_of_this_station; // updating the "ind" array

        ti++;
        tjrnycodes[ti - 1][0] = 0;
        int tjrnycodes2[10];
        tjrnycodes2[0]=0;
        while (curr_train != nullptr)
        {
          tjrnycodes2[0]++; // updating the "jrnycodes" array
          tjrnycodes2[(tjrnycodes[0])] = curr_train->object->journeyCode;
          curr_train=curr_train->next;
        }

        curr_train = curr->object->trains;
        while (curr_train != nullptr)
        {
          bool found = false;

          for (int k = 1; k <= jrnycodes[j][0]; k++)
          {

            if (curr_train->object->journeyCode == jrnycodes[j][k])
            { // checking if the journeycode is same as previous station's train
              found = true;
              break;
            }
          }
          if (found)
          {
            tjrnycodes[ti - 1][0]++; // updating the "jrnycodes" array
            tjrnycodes[ti - 1][(tjrnycodes[ti - 1][0])] = curr_train->object->journeyCode;
          }

          else{

          }
          curr_train = curr_train->next;
        }
      }

      find_indirect(ans, end, srci, desti, tempind, ti, tjrnycodes, adjacency); // recurrsive call

      curr = curr->next;
    }
  }
}


void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  cout << "This function is to be implemented by you." << endl;
  int srci = stnNameToIndex.hashValue(srcStnName), desti = stnNameToIndex.hashValue(destStnName);
  while (true)
  {
    if (srcStnName == stnNameToIndex.getKeyAtIndex(srci))
      break;
    srci = (srci + 1) % DICT_SIZE;
  }

  while (true)
  {
    if (destStnName == stnNameToIndex.getKeyAtIndex(desti))
      break;
    desti = (desti + 1) % DICT_SIZE;
  }

  if (desti == srci)
  {
    cout << "No direct journeys available!\n";
    return;
  }

  listOfObjects<TrainInfoPerStation *> *ans = nullptr; // list which contains the correct stations
  listOfObjects<TrainInfoPerStation *> *end = nullptr; // points to the end of the "ans" list so that it becomes easy to add new element

  int ind[DICT_SIZE], i = 0;    // Stores indexes of prospective intermediate stations,i is no of stations found.
  int jrnycodes[DICT_SIZE][10]; // Stores journeycodes so we can compare to make sure we select trains with same journeycodes only
  listOfObjects<StationConnectionInfo *> *curr = adjacency[srci].toStations;

  while (curr != NULL) // parsing through tostations of source station to find direct journeys and initialize "ind" and "jrnycodes"
  {

    int index_of_this_station = curr->object->adjacentStnIndex;
    if (index_of_this_station == desti)
    {
      listOfObjects<TrainInfoPerStation *> *curr_train = curr->object->trains;
      while (curr_train != nullptr)
      {

        if (ans == nullptr)
        {
          ans = new listOfObjects<TrainInfoPerStation *>(curr_train->object);
          end = ans;
          curr_train = curr_train->next;
          continue;
        }

        end->next = new listOfObjects<TrainInfoPerStation *>(curr_train->object);
        end = end->next;

        curr_train = curr_train->next;
      }
      curr = curr->next;
      continue;
    }

    else
    {
      listOfObjects<TrainInfoPerStation *> *curr_train = curr->object->trains;
      ind[i] = index_of_this_station;

      i++;
      jrnycodes[i - 1][0] = 0;
      while (curr_train != nullptr)
      {
        jrnycodes[i - 1][0]++;
        jrnycodes[i - 1][(jrnycodes[i - 1][0])] = curr_train->object->journeyCode;

        curr_train = curr_train->next;
      }

      curr = curr->next;
    }
  }

  find_indirect(ans, end, srci, desti, ind, i, jrnycodes, adjacency); // Using recursion finds indirect journeys and update "ans" list which we pass by reference
                                                                      //  Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
                                                                      //  for the source station and then we can print it out by invoking
                                                                      //  printStationInfo that we had used in Lab 7.
                                                                      //  printStationInfo is a private member function of the Planner class
                                                                      //  It is declared in planner.h and implemented in planner.cpp
  if (ans == nullptr)
  {
    cout << "No direct journeys available!\n";
    return;
  }
  printStationInfo(ans);
  return;
}

#endif
