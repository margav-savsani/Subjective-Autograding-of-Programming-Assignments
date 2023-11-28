#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
#include <vector>
#include <queue>

struct path
{
public:
  int count;                                                      // for storing max no of crossovers
  int present_train;                                              // train in which we are present now
  int present_station;                                            // station at which we are present
  vector<int> trains;                                             // for storing history of trains used
  vector<int> stations;                                           // for storing history of stations reached
  path(int pres_tra, int pres_sta, int c, int train, int station) // constructor
  {
    present_train = pres_tra;
    present_station = pres_sta;
    count = c;
    trains.push_back(train);
    stations.push_back(station);
  }
};

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  queue<path> BFS;                                                // Inititlazation of BFS
  queue<path> allpaths;                                           // To store the paths which reached the destination stations
  int source_index = stnNameToIndex.get(srcStnName)->value;       // getting index of source station.
  int destination_index = stnNameToIndex.get(destStnName)->value; // getting index of destination station.

  listOfObjects<TrainInfoPerStation *> *intial_trains = stationInfo[source_index];
  while (intial_trains != nullptr) // adding all trains leaving source into queue
  {
    BFS.push(path(intial_trains->object->journeyCode, source_index, 0, intial_trains->object->journeyCode, source_index));
    intial_trains = intial_trains->next;
  }

  while (!BFS.empty()) // starting bfs on paths
  {
    path elem = BFS.front(); // getting first element of que
    StationAdjacencyList *current = adjacency;
    listOfObjects<StationConnectionInfo *> *adj = current[elem.present_station].toStations;
    while (adj != nullptr) // for all adjacent stations of present stations
    {
      int presentstn_index = adj->object->adjacentStnIndex;
      // selected one of the adjacency station
      listOfObjects<TrainInfoPerStation *> *presentstn_trains = adj->object->trains;
      // all the trains from prev to curr station.
      if (presentstn_index == destination_index)
      // to check whether the same train is there on present stn
      {

        while (presentstn_trains != nullptr)
        {
          if (presentstn_trains->object->journeyCode == elem.present_train) // if found then that train reaches the destination
          {
            path insert = elem;
            insert.present_station = destination_index;
            insert.stations.push_back(destination_index);
            allpaths.push(insert);
            break;
          }
          presentstn_trains = presentstn_trains->next;
          // going to next train in curr to check this condition.
        }
      }

      else // if the curr station is not the final destination.
      {
        while (presentstn_trains != nullptr) // to check a train is there from prev station to this station.
        {
          if (presentstn_trains->object->journeyCode == elem.present_train)
          {
            listOfObjects<TrainInfoPerStation *> *presentstn_trains_to_add = stationInfo[presentstn_index];
            // Now add the same train and different trains cases in the queue.
            listOfObjects<TrainInfoPerStation *> *to_get_arr_time = stationInfo[presentstn_index];
            int Arr;
            int Dep;

            while (to_get_arr_time != nullptr)
            {
              if (elem.present_train == to_get_arr_time->object->journeyCode)
              {
                Arr = to_get_arr_time->object->arrTime;
                break;
              }
              to_get_arr_time = to_get_arr_time->next; // findining arrival time of train to the present station
            }
            while (presentstn_trains_to_add != nullptr)
            {
              Dep = presentstn_trains_to_add->object->depTime;
              float k = (Dep - Arr) / 100;
              if (presentstn_trains_to_add->object->journeyCode == elem.trains.back())
              {
                path insert = elem;
                // adding the train and station name to the present path
                insert.present_station = presentstn_index;
                insert.present_train = presentstn_trains_to_add->object->journeyCode;
                insert.stations.push_back(presentstn_index);
                insert.trains.push_back(presentstn_trains_to_add->object->journeyCode);
                BFS.push(insert); // adding this path into the que
              }
              // checking for transint time and max no of crossovers.
              else if (elem.count != maxStopOvers && Dep > Arr && k <= maxTransitTime) // changing the train at the present train
              {
                path insert = elem;
                // adding the train and station name to the present path
                insert.present_station = presentstn_index;
                insert.present_train = presentstn_trains_to_add->object->journeyCode;
                insert.stations.push_back(presentstn_index);
                insert.trains.push_back(presentstn_trains_to_add->object->journeyCode);
                insert.count++;   // update the count in elem before pushing it.
                BFS.push(insert); // adding this path into the que
              }
              presentstn_trains_to_add = presentstn_trains_to_add->next; // checking for next train
            }
          }
          presentstn_trains = presentstn_trains->next;
        }
      }
      adj = adj->next; // checking for next station in adjacency list
    }
    BFS.pop();
  }

  // printing the journeys in our required way

  if (allpaths.empty())
  {
    cout << RED << "NO TRAINS ARE PRESENT" << RESET << endl;
  }
  while (!allpaths.empty())
  {
    path curr_path = allpaths.front();
    int sz = curr_path.trains.size();
    int k = curr_path.trains[0];
    for (int i = 0; i < sz; i++)
    {
      bool checking = false; // checking for change of trains

      if (i == 0)
      {
        cout << RED << "source Station of Journey" << RESET << endl;
      }
      cout << "we have reached    :" << BLUE << stnNameToIndex.getKeyAtIndex(curr_path.stations[i]) << RESET << endl;
      if (k != curr_path.trains[i])
      {
        cout << RED << "you have to change the train now at :   " 
        << stnNameToIndex.getKeyAtIndex(curr_path.stations[i]) << RESET << endl;
        checking = true;
      }
      listOfObjects<TrainInfoPerStation *> *a = stationInfo[curr_path.stations[i]];
      listOfObjects<TrainInfoPerStation *> *a1 = stationInfo[curr_path.stations[i]];

      while (a != nullptr)
      {
        if (a->object->journeyCode == curr_path.trains[i]) // for getting information about present train
        {

          if (checking) // looping this to print transist time if ther is change of trains
          {
            while (a1 != nullptr)
            {
              if (a1->object->journeyCode == k)
              {
                float time = (a->object->depTime - a1->object->arrTime) / 100;
                cout << "transist time is :  " << BLUE << time << "hrs" << RESET << endl;
                break;
              }
              a1 = a1->next;
            }
          }
          cout << "taking the train with :" << GREEN << "Jcode" << '\t' << a->object->journeyCode << RESET << '\t';
          if (a->object->arrTime == -1)
          {
            cout << GREEN << "Arr" << '\t' << "START" << RESET << '\t';
          }
          else
          {
            cout << GREEN << "Arr" << '\t' << a->object->arrTime << RESET << '\t';
          }
          if (a->object->depTime == -1)
          {
            cout << GREEN << "Dep" << '\t' << "END" << RESET << '\t' << "at "
                 << stnNameToIndex.getKeyAtIndex(curr_path.stations[i]) << endl;
          }
          else
          {
            cout << GREEN << "Dep" << '\t' << a->object->depTime << RESET << '\t' << "at " 
            << stnNameToIndex.getKeyAtIndex(curr_path.stations[i]) << endl;
          }
          break;
        }
        a = a->next;
      }
      k = curr_path.trains[i];
    }
    cout << RED << "Reached Destination Station" << RESET << endl;
    cout << BLUE << stnNameToIndex.getKeyAtIndex(curr_path.stations.back()) << RESET << endl;
    cout << "-----*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*----" << endl;
    allpaths.pop();
  }
  return;
}

#endif