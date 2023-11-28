#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
//
#include <queue>
#include <vector>


struct QueueElem
{ // The Object present in the Queue. Contains the train no connecting two adjacent Stations 
  // and the station_No of the 2nd station.
public:
  int stn_ind; // The index of the station which is the end of the edge
  int trainno; // The journeyCode of the train from which we came to this node
  QueueElem() //Default constructor
  {
    stn_ind = -1;
    trainno = -1;
  }
  QueueElem(int name, int jCode)
  {
    stn_ind = name;
    trainno = jCode;
  }
};


void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here

  // The Index of destination station
  int destination_ind = stnNameToIndex.get(destStnName)->value;

  // The Direct journeys are stored in form of vector of their Train-No.
  listOfObjects<TrainInfoPerStation *> *dest_j = NULL;

  // insert your code here
  queue<QueueElem> queue_BFS;

  // Index of the station_Name
  int index = stnNameToIndex.get(srcStnName)->value;

  // The adjacency of the current station.
  StationAdjacencyList *curr ;
  curr =  adjacency;

  // An iterator for the to.Stations to store all the adjacent stations
  listOfObjects<StationConnectionInfo *> *adjstns = curr[index].toStations;

  while (adjstns != NULL) // Storing all the adjacent station Names
  {
    // The index of the station which we have reached
    int ind_of_station = adjstns->object->adjacentStnIndex;
   //  cout << ind_of_station << endl;

    // An iterator for trains to this station
    listOfObjects<TrainInfoPerStation *> *train = adjstns->object->trains;

    while (train != NULL)
    {
      // If there is direct train at start from source to stop.
      if (ind_of_station == destination_ind)
      {
        // Adding the Train Infos in dest_j.
        if (dest_j == NULL)
        {
          dest_j = new listOfObjects<TrainInfoPerStation *>(train->object);
        }
        else
        {
          listOfObjects<TrainInfoPerStation *> *iterator = dest_j;
          while (iterator->next != NULL)
          {
            iterator = iterator->next;
          }
          iterator->next = new listOfObjects<TrainInfoPerStation *>(train->object);
        }
        train = train->next;
        continue; // Since we donot add these trains to the Queue
      }
      queue_BFS.push(QueueElem(ind_of_station, train->object->journeyCode));
      train = train->next;
    }
    adjstns = adjstns->next;
  }

  // std::cout<<"INITIAL_SZ"<<queue_BFS.size()<<endl;

  while (!queue_BFS.empty())
  {                                    // The Main BFS loop
    QueueElem head; // Head of the Queue
    head = queue_BFS.front();           // This stores the Head in the 'head' pointer
    queue_BFS.pop();
    int trainno = head.trainno;       // Gives the Train No of the Head
    int stn_ind = head.stn_ind;       // Gives Station index of the HEAD.
    adjstns = adjacency[stn_ind].toStations;
    while (adjstns != NULL)
    {
      listOfObjects<TrainInfoPerStation *> *train = adjstns->object->trains;
      int adjStn = adjstns->object->adjacentStnIndex;
      while (train != NULL)
      {
        if (train->object->journeyCode == trainno)
        {
          // Check Whether the Removed trainno is same as that removed from Queue.
          if (adjStn == destination_ind)
          {
            // When we reach the destination required.
            //  Adding the Train Infos in dest_j.
            if (dest_j == NULL)
            {
              dest_j = new listOfObjects<TrainInfoPerStation *>(train->object);
            }
            else
            {
              listOfObjects<TrainInfoPerStation *> *iterator = dest_j;
              while (iterator->next != NULL)
              {
                iterator = iterator->next;
              }
              iterator->next = new listOfObjects<TrainInfoPerStation *>(train->object);
            }
            break; // No further train exists hence exit While Loop
          }
          // Adding the element into the Queue
          queue_BFS.push(QueueElem(adjStn, trainno));
        }
        train = train->next;
      }
      adjstns = adjstns->next;
    }
  // std::cout<<"SIZE IS "<<queue_BFS.size()<<endl;
  // std::cout<<"hehe"<<endl;
  }

  // Finally dest_j contain the TrainInfoPerStation for the "Destination" station.
  // We Check the Source Station for the corresponding TrainNo.

  // Finally the list to be returned.

  listOfObjects<TrainInfoPerStation *> *source_j = NULL;

  // Total Train Info for the source station.
  listOfObjects<TrainInfoPerStation *> *Total_source = stationInfo[stnNameToIndex.get(srcStnName)->value];

  // Vector to store the TrainNo.s in dest_j

  vector<int> Train_nos;
  while (dest_j != NULL)
  {
    Train_nos.push_back(dest_j->object->journeyCode);
    dest_j = dest_j->next;
  }

  // find(vector.begin(), vector.end(), item)!=vector.end())
  //  sort(Train_nos.begin(),Train_nos.end());

  while (Total_source != NULL)
  {
    //for (int i = 0; i < Train_nos.size(); i++)//
    int i = 0;
    while(i < Train_nos.size())   
    {
      if (Train_nos[i] == Total_source->object->journeyCode)
      {
        if (source_j == NULL)
        {
          source_j = new listOfObjects<TrainInfoPerStation *>(Total_source->object);
        }
        else
        {
          listOfObjects<TrainInfoPerStation *> *iterator = source_j;
          while (iterator->next != NULL)
          {
            iterator = iterator->next;
          }
          iterator->next = new listOfObjects<TrainInfoPerStation *>(Total_source->object);
        }
      }
      i++;
    }
    Total_source = Total_source->next;
  }
  
  if (!source_j)
  {
    cout<<RED << "No direct journeys available" <<RESET<< endl;
    return;
  }

  printStationInfo(source_j);

  return;
}

#endif