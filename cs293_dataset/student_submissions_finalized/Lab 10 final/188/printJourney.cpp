#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
// listOfObjects<listOfObjects<StationConnectionInfo *> *> *jrnyPlans = nullptr;
template <typename T>
listOfObjects<T> *getLast(listOfObjects<T> *queue)
{
  listOfObjects<T> *last = queue;
  if (last == nullptr)
    return nullptr;
  while (last->next != nullptr)
  {
    last = last->next;
  }
  return last;
}

listOfObjects<listOfObjects<StationConnectionInfo *> *> *updateLinkedList(listOfObjects<listOfObjects<StationConnectionInfo *> *> *oldList, listOfObjects<StationConnectionInfo *> *jrnyTracker)
{
  listOfObjects<listOfObjects<StationConnectionInfo *> *> *newList = nullptr;
  listOfObjects<listOfObjects<StationConnectionInfo *> *> *temp = oldList;
  if (oldList == nullptr)
  {
    return nullptr;
  }
  else
  {
    while (temp != nullptr)
    {
      listOfObjects<StationConnectionInfo *> *temper = new listOfObjects(jrnyTracker->object);
      temper->next = temp->object;
      temper->next->prev = temper;
      if (newList == nullptr)
      {
        newList = new listOfObjects(temper);
      }
      else
      {
        listOfObjects<listOfObjects<StationConnectionInfo *> *> *ptr = getLast(newList);
        ptr->next = new listOfObjects(temper);
      }
      temp = temp->next;
    }
  }
  return newList;
}

TrainInfoPerStation *find_obj(listOfObjects<TrainInfoPerStation *> *queue, listOfObjects<TrainInfoPerStation *> *obj)
{
  listOfObjects<TrainInfoPerStation *> *last = queue;
  while (last != nullptr)
  {
    // //cout << last->object->journeyCode << " " << obj->object->journeyCode << endl;
    if (last->object->journeyCode == obj->object->journeyCode)
    {
      return last->object;
    }
    last = last->next;
  }
  return nullptr;
}

listOfObjects<listOfObjects<StationConnectionInfo *> *> *doDFS(StationAdjacencyList adjacency[], listOfObjects<TrainInfoPerStation *> *stationInfo[], int src_index, int dest_index)
{
  static int recursionLevel = -1;
  // Increment recursion level on entering the function
  recursionLevel++;
  listOfObjects<StationConnectionInfo *> *adj_stns = adjacency[src_index].toStations;
  listOfObjects<listOfObjects<StationConnectionInfo *> *> *jrnyPlans = nullptr;

  listOfObjects<TrainInfoPerStation *> *list_of_trains = stationInfo[src_index];
  while (adj_stns != nullptr)
  {
    int adj_ind = adj_stns->object->adjacentStnIndex;
    listOfObjects<TrainInfoPerStation *> *adj_trains = adj_stns->object->trains;
    while (adj_trains != nullptr)
    {

      TrainInfoPerStation *tran = adj_trains->object;
      TrainInfoPerStation *train_info = find_obj(list_of_trains, new listOfObjects(tran));
      // cout << "s:" << train_info->journeyCode << endl;
      listOfObjects<StationConnectionInfo *> *jrnyTracker = new listOfObjects(new StationConnectionInfo(src_index));
      // jrnyTracker tracks a possible path of journey from src to destn
      // if src to destn is reached it must append to jrnyplans
      // else it must add the new stationconnectionInfo into it
      jrnyTracker->object->trains = new listOfObjects(train_info);
      // initiating a StationConnectionInfo with nullptr so that we can store source
      if (adj_ind == dest_index)
      {
        while (adj_trains != nullptr)
        {

          TrainInfoPerStation *tran = adj_trains->object;
          TrainInfoPerStation *train_info = find_obj(list_of_trains, new listOfObjects(tran));

          listOfObjects<StationConnectionInfo *> *jrnyTracker = new listOfObjects(new StationConnectionInfo(src_index));
          // jrnyTracker tracks a possible path of journey from src to destn
          // if src to destn is reached it must append to jrnyplans
          // else it must add the new stationconnectionInfo into it
          jrnyTracker->object->trains = new listOfObjects(train_info);
          listOfObjects<listOfObjects<StationConnectionInfo *> *> *jrny = new listOfObjects(jrnyTracker);
          if (jrnyPlans == nullptr)
          {
            jrnyPlans = jrny;
          }
          else
          {
            listOfObjects<listOfObjects<StationConnectionInfo *> *> *temp = getLast(jrnyPlans);
            temp->next = jrny;
          }
          adj_trains = adj_trains->next;
        }
        return jrnyPlans;
      }
      else
      {
        // Add this StationConnectionInfo into

        listOfObjects<listOfObjects<StationConnectionInfo *> *> *jrnyPlansele = doDFS(adjacency, stationInfo, adj_ind, dest_index);
        jrnyPlansele = updateLinkedList(jrnyPlansele, jrnyTracker);
        if (jrnyPlans == nullptr)
        {
          jrnyPlans = jrnyPlansele;
        }
        else
        {

          listOfObjects<listOfObjects<StationConnectionInfo *> *> *temp = getLast(jrnyPlans);
          temp->next = jrnyPlansele;
        }
      }

      adj_trains = adj_trains->next;
    }
    adj_stns = adj_stns->next;
  }
  return jrnyPlans;
}
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  listOfObjects<TrainInfoPerStation *> *directJourneys = nullptr;
  Entry<int> *srcstn = stnNameToIndex.get(srcStnName);
  int srcstnIndex = srcstn->value;

  Entry<int> *deststn = stnNameToIndex.get(destStnName);
  int deststnIndex = deststn->value;

  listOfObjects<StationConnectionInfo *> *adj_stns = adjacency[srcstnIndex].toStations;
  listOfObjects<listOfObjects<StationConnectionInfo *> *> *jrnyPlans = doDFS(adjacency, stationInfo, srcstnIndex, deststnIndex);
  if (jrnyPlans == nullptr)
  {
    cout << "No Journeys Possible between given stations" << endl;
  }
  else
  {
    while (jrnyPlans != nullptr)
    {
      listOfObjects<StationConnectionInfo *> *jrnyObj = jrnyPlans->object;
      listOfObjects<StationConnectionInfo *> *ptr = jrnyPlans->object;
      bool isEligible = true;
      int stopCount = 0;
      while (ptr != nullptr)
      {
        int transitTime = 0;
        TrainInfoPerStation *tr2 = ptr->object->trains->object;
        int n1, n2;
        if (ptr->prev != nullptr)
        {
          TrainInfoPerStation *tr1 = ptr->prev->object->trains->object;

          if (tr1->journeyCode != tr2->journeyCode)
          {
            stopCount++;

            for (int i = 0; i < 7; i++)
            {
              if (tr1->daysOfWeek[i])
                n1 = i;
            }
            if (tr2->arrTime < tr1->depTime)
              n2 = n1 + 1;
            else
              n2 = n1;
            while (!tr2->daysOfWeek[n2])
            {
              n2 = (n2 + 1) % 7;
            }
            transitTime = tr2->arrTime - tr1->depTime + ((7 + (n2 - n1)) % 7) * 2400;
          }
        }
        // if (ptr->next == nullptr)
        // {
        //   TrainInfoPerStation *tr_obj = find_obj(stationInfo[deststnIndex], new listOfObjects(tr2));
        //   int n3;
        //   if (tr_obj->arrTime < tr2->depTime)
        //     n3 = n2 + 1;
        //   else
        //     n3 = n2;
        //   transitTime = tr_obj->arrTime - tr2->depTime + ((7 + (n3 - n2)) % 7) * 2400;
        // }
        if (transitTime > maxTransitTime || stopCount > maxStopOvers || transitTime < 0)
        {
          isEligible = false;
          break;
        }
        ptr = ptr->next;
      }
      if (isEligible)
      {
        // to be implemented
        listOfObjects<StationConnectionInfo *> *ptr = jrnyPlans->object;
        TrainInfoPerStation *tr2 = nullptr, *tr1 = nullptr;
        string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
        for (int k = 0; k < 7; k++)
        {
          if (ptr->object->trains->object->daysOfWeek[k])
          {
            cout << GREEN << "Journey: " << RESET << endl;
            cout << BLUE << "Source Station: " << RESET << srcStnName << endl;
            cout << GREEN << "Day: " << RESET << days[k] << endl;
            cout << BLUE << "JourneyCode: " << ptr->object->trains->object->journeyCode << RESET << "\t";
            cout << RED << "Arr: " << RESET;
            if (ptr->object->trains->object->arrTime == -1)
            {
              cout << "Starts";
            }
            else
            {
              cout << ptr->object->trains->object->arrTime;
            }
            cout << RED << " Dep: " << RESET;
            if (ptr->object->trains->object->depTime == -1)
            {
              cout << "Ends";
            }
            else
            {
              cout << ptr->object->trains->object->depTime;
            }
            cout << endl;
            while (jrnyObj != nullptr)
            {
              int transit = 0;
              tr2 = jrnyObj->object->trains->object;
              int j1 = k, j2 = k;
              if (jrnyObj->prev != nullptr)
              {
                tr1 = jrnyObj->prev->object->trains->object;
                if (tr1->journeyCode != tr2->journeyCode)
                {

                  while (!tr2->daysOfWeek[j2])
                  {
                    j2 = (j2 + 1) % 7;
                  }
                  if (tr2->arrTime < tr1->depTime)
                    j2 = j1 + 1;
                  else
                    j2 = j1;
                  while (!tr1->daysOfWeek[j1])
                  {
                    j1 = (j1 + 1) % 7;
                  }
                  transit = tr2->arrTime - tr1->depTime + ((7 + (j2 - j1)) % 7) * 2400;
                  cout << BLUE << "Station: " << RESET << stnNameToIndex.getKeyAtIndex(jrnyObj->object->adjacentStnIndex) << endl;
                  cout << GREEN << "Day: " << RESET << days[j2] << endl;
                  cout << BLUE << "JourneyCode: " << tr2->journeyCode << RESET << "\t";
                  cout << RED << "Arr: " << RESET;
                  if (tr2->arrTime == -1)
                  {
                    cout << "Starts";
                  }
                  else
                  {
                    cout << tr2->arrTime;
                  }
                  cout << RED << " Dep: " << RESET;
                  if (tr2->depTime == -1)
                  {
                    cout << "Ends";
                  }
                  else
                  {
                    cout << tr2->depTime;
                  }
                  cout << "\t"
                       << "TransitTime: " << transit << endl;
                }
              }

              jrnyObj = jrnyObj->next;
            }
            cout << BLUE << "Destination Station: " << RESET << destStnName << endl;
            TrainInfoPerStation *tr_obj = find_obj(stationInfo[deststnIndex], new listOfObjects(tr2));
            int j3;
            if (tr_obj->arrTime < tr2->depTime)
              j3 = k + 1;
            else
              j3 = k;
            while (!tr_obj->daysOfWeek[j3])
            {
              j3 = (j3 + 1) % 7;
            }
            cout << GREEN << "Day: " << RESET << days[j3] << endl;
            cout << BLUE << "JourneyCode: " << tr_obj->journeyCode << RESET << "\t";
            cout << RED << "Arr: " << RESET;
            if (tr_obj->arrTime == -1)
            {
              cout << "Starts";
            }
            else
            {
              cout << tr_obj->arrTime;
            }
            cout << endl
                 << endl;
            cout << "-------------------------------------------" << endl;
          }
          cout << "*********************************************" << endl;

        }
      }
          jrnyPlans = jrnyPlans->next;

      // Whenever you need to print a journey, construct a
      // listOfObjects<TrainInfoPerStation *> appropriately, and then
      // use printStationInfo that we had used in Lab 7.
      // printStationInfo is a private member function of
      // the Planner class. It is declared in planner.h and implemented in
      // planner.cpp
    }
  }
      return;
}
#endif