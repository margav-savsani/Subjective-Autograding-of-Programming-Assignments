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
  int traincode;

  int jc1;
  int flag = 0;
  jc1 = stnNameToIndex.get(srcStnName)->value;

  int jc2;
  jc2 = stnNameToIndex.get(destStnName)->value;
  listOfObjects<TrainInfoPerStation *> *printer;
  listOfObjects<StationConnectionInfo *> *overall;
  int num = 0;
  listOfObjects<StationConnectionInfo *> *prefinal;
  listOfObjects<StationConnectionInfo *> *intermediate = adjacency[jc1].toStations;
  while (intermediate != nullptr)// Copying the adjancy list into a new list which would act as the main queue for the BFS
  {
    if (num == 1)
    {
      prefinal = overall;
      overall = overall->next;
    }
    overall = new listOfObjects<StationConnectionInfo *>(intermediate->object);
    if (num == 1)
    {
      prefinal->next = overall;
      overall->prev = prefinal;
    }
    intermediate=intermediate->next;
    num=1;
  }
  while (overall->prev != nullptr)
  {
    overall = overall->prev;
  }
  listOfObjects<StationConnectionInfo *> *list = overall;

  listOfObjects<int> *jc;
  listOfObjects<StationConnectionInfo *> *checker = list;
  int check = 0;
  listOfObjects<int> *index;
  listOfObjects<int> *lastpointing;
  while (checker != nullptr) // This list acts as mapping of trains to journey code of their parent journey so that only check those journey whose journey code match with their mapping. 
  {
    if (check == 1)
    {
      index = jc;
      jc = jc->next;
    }
    jc = new listOfObjects<int>(-1);
    if (check == 1)
    {
      index->next = jc;
      jc->prev = index;
    }

    check = 1;
    checker = checker->next;
  }
  lastpointing = jc;
  while (jc->prev != nullptr)
  {
    jc = jc->prev;
  }
  listOfObjects<StationConnectionInfo *> *final = adjacency[jc2].fromStations;
  while (list->next != nullptr)
  {
    list = list->next;
  }


  while (overall != nullptr)
  {

    listOfObjects<TrainInfoPerStation *> *traingoing = overall->object->trains; // List of Trains between 2 stations

    while (traingoing != nullptr)
    {
      traincode = jc->object;
      if (traincode == traingoing->object->journeyCode || traincode == -1)// matching the current code with the traincode stored in queue for conforming direct journey. If the station is adjacent to source, we dont need to match codes, hence -1
      {

        int adjstn;
        adjstn = overall->object->adjacentStnIndex;
        string intermediate;
        intermediate = stnNameToIndex.getKeyAtIndex(adjstn);
      
        if (intermediate == destStnName)// If we reach destination station, we add it to the printer for printing journey at the end
        {
          listOfObjects<TrainInfoPerStation *>*listoftrains=stationInfo[jc1];           //For finding the arrival/departure time at the source station of the journey
          while(listoftrains!=nullptr){
            if(traingoing->object->journeyCode==listoftrains->object->journeyCode){     // We match the current journey code in the array of StationInfo list to find the corresponding entry
              break;
            }
            listoftrains=listoftrains->next;

          }
          listOfObjects<TrainInfoPerStation *> *direct;     // Adding the entry to listofObjects and then assgning next/prev values.
          if (flag == 1)
          {
            direct = printer;
            printer = printer->next;
          }
          printer = new listOfObjects<TrainInfoPerStation *>(listoftrains->object);
          if (flag == 1)
          {
            direct->next = printer;
            printer->prev = direct;
          }

          flag = 1;
        }
        else
        {
          if (adjacency[adjstn].toStations != nullptr)      // If we don't reach the destination, we add the adjacent station ,from that station, to the queue of Binary Search tree
          {
            listOfObjects<StationConnectionInfo *> *pre2;
            listOfObjects<StationConnectionInfo *> *intermediate = adjacency[adjstn].toStations;// We move to last element of the list so that the next time insertion can take place.
            while (intermediate != nullptr)
            {
              listOfObjects<StationConnectionInfo *> *temp;
              temp=new listOfObjects<StationConnectionInfo *>(intermediate->object);

              list->next=temp;
              list=list->next;
              intermediate=intermediate->next;

            }

            listOfObjects<StationConnectionInfo *> *number_new;
            number_new = adjacency[adjstn].toStations;
            while (number_new != nullptr)                                       // We add the journeycode of this journey to map its adjacent station to the train code so that we maintain a direct jounrney with same traincode
            {
              listOfObjects<int> *dummy;
              dummy = new listOfObjects<int>(traingoing->object->journeyCode);
              dummy->prev = lastpointing;
              lastpointing->next = dummy;
              lastpointing = lastpointing->next;
              number_new = number_new->next;
            }

            
          }
        }
      }
      
      traingoing = traingoing->next;
    }
   
    jc = jc->next;
   
    overall = overall->next;
   
  }
  
  
  if (flag == 0)
  {
    
    cout << "No direct journeys available" << endl;
  }
  else                                 // We traceback to the 1st element of the printer so that we can supply it to printStationInfo
  {
    while (printer->prev != nullptr)
    {
      printer = printer->prev;
    }
    printStationInfo(printer);
  }

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  return;
}
#endif
