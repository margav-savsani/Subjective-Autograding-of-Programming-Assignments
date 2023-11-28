#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#define CONST_GROWTH 40
#define INIT_SIZE 40

#include <queue>
#include <vector>


struct QEle
{ 
public:
  int index;
  int trnn; 
  QEle()
  {
    index = -1;
    trnn = -1;
  }
  QEle(int name, int jCode)
  {
    index = name;
    trnn = jCode;
  }
};

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  int dest_index = stnNameToIndex.get(destStnName)->value;

  listOfObjects<TrainInfoPerStation *> *destjrny = NULL;

  queue<QEle> queue_BFS;

  int index = stnNameToIndex.get(srcStnName)->value;

  // The adjacencylist of the currStation.
  StationAdjacencyList *currStation ;
  currStation =  adjacency;

  listOfObjects<StationConnectionInfo *> *adj_stn_list = currStation[index].toStations;

  while (adj_stn_list != NULL)
  {
    int ind_of_station = adj_stn_list->object->adjacentStnIndex;

    listOfObjects<TrainInfoPerStation *> *train = adj_stn_list->object->trains;

    while (train != NULL)
    {
      // If direct train 
      if (ind_of_station == dest_index)
      {
        if (destjrny == NULL)
        {
          destjrny = new listOfObjects<TrainInfoPerStation *>(train->object);
        }
        else
        {
          listOfObjects<TrainInfoPerStation *> *it = destjrny;
          while (it->next != NULL)
          {
            it = it->next;
          }
          it->next = new listOfObjects<TrainInfoPerStation *>(train->object);
        }
        train = train->next;
        continue; 
      }
      queue_BFS.push(QEle(ind_of_station, train->object->journeyCode));
      train = train->next;
    }
    adj_stn_list = adj_stn_list->next;
  }

  while (!queue_BFS.empty())
  {                                   
    QEle head; 
    head = queue_BFS.front();
    queue_BFS.pop();
    int trnn = head.trnn;    
    int index = head.index;
    adj_stn_list = adjacency[index].toStations;
    while (adj_stn_list != NULL)
    {
      listOfObjects<TrainInfoPerStation *> *train = adj_stn_list->object->trains;
      int adjStn = adj_stn_list->object->adjacentStnIndex;
      while (train != NULL)
      {
        if (train->object->journeyCode == trnn)
        {
          if (adjStn == dest_index)
          {
            if (destjrny == NULL)
            {
              destjrny = new listOfObjects<TrainInfoPerStation *>(train->object);
            }
            else
            {
              listOfObjects<TrainInfoPerStation *> *it = destjrny;
              while (it->next != NULL)
              {
                it = it->next;
              }
              it->next = new listOfObjects<TrainInfoPerStation *>(train->object);
            }
            break; 
          }
          // Add elem to Queue
          queue_BFS.push(QEle(adjStn, trnn));
        }
        train = train->next;
      }
      adj_stn_list = adj_stn_list->next;
    }
  }

  listOfObjects<TrainInfoPerStation *> *srcj = NULL;

  listOfObjects<TrainInfoPerStation *> *Total_source = stationInfo[stnNameToIndex.get(srcStnName)->value];

  vector<int> Train_nos;
  while (destjrny != NULL)
  {
    Train_nos.push_back(destjrny->object->journeyCode);
    destjrny = destjrny->next;
  }

  while (Total_source != NULL)
  {
    int i = 0;
    while(i < Train_nos.size())   
    {
      if (Train_nos[i] == Total_source->object->journeyCode)
      {
        if (srcj == NULL)
        {
          srcj = new listOfObjects<TrainInfoPerStation *>(Total_source->object);
        }
        else
        {
          listOfObjects<TrainInfoPerStation *> *it = srcj;
          while (it->next != NULL)
          {
            it = it->next;
          }
          it->next = new listOfObjects<TrainInfoPerStation *>(Total_source->object);
        }
      }
      i++;
    }
    Total_source = Total_source->next;
  }
  
  if (!srcj)
  {
    cout<<RED << "No direct journeys available" <<RESET<< endl;
    return;
  }

  printStationInfo(srcj);

  return;
}

#endif
