

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

/** One very simple solution exists, without BFS, :
 * make a list of all journey codes from source station that depart from there
 * make a list of all journey codes from destination station that arrive there
 * take intersection of the lists and print them
 * 
 * But of course, since the lab is about BFS, a different approach:
 * make a list of all trains that leave source. Start moving in BFS way and at each station check whether the journey codes in our list are present or not
 * if not, delete them, if present, continue in those paths
 */


/*
Final Strategy : Do BFS except that push object of the type StationConnectionInfo into the queue. The StationConnectionInfo object has list of
the trains that arrived from the source station. Break the loop if the list becomes empty of if the train reaches destination.
 */


// Function to take the intersection of linked lists of journey codes. It returns linked list of intersection of elements.
listOfObjects<TrainInfoPerStation*>*intersection_list(listOfObjects<TrainInfoPerStation*>* list, listOfObjects<TrainInfoPerStation*>* toTrains){
  listOfObjects<TrainInfoPerStation*>*  newlist = nullptr;
  listOfObjects<TrainInfoPerStation*>*  nl = nullptr;
  listOfObjects<TrainInfoPerStation*>* L = list;
  listOfObjects<TrainInfoPerStation*>* T = toTrains;
  while (L != nullptr){   // taking intersection

    while (T != nullptr){
      if (L->object->journeyCode == T->object->journeyCode){
        if (newlist == nullptr){
            newlist = new listOfObjects<TrainInfoPerStation*>(L->object);
            nl = newlist;
        }
        else {
          nl->next = new listOfObjects<TrainInfoPerStation*>(L->object);
          nl = nl->next;
        }
      }
      T = T->next;
    }
    T = toTrains;
    L = L->next;
  }
  return newlist;
}


// Adding the stations to the queue
listOfObjects<StationConnectionInfo*>* find_trains(listOfObjects<TrainInfoPerStation*>* list, listOfObjects<StationConnectionInfo*>* toList, int dest){
  listOfObjects<StationConnectionInfo*>* newtolist = nullptr;
  listOfObjects<StationConnectionInfo*>* nl = nullptr;
  listOfObjects<StationConnectionInfo*>* T = toList;
  listOfObjects<TrainInfoPerStation*>* I = nullptr;
  while (T != nullptr){
    I = intersection_list(list, T->object->trains);   // updating the trains that reach here
    if (I != nullptr){
      if (newtolist == nullptr){
        newtolist = new listOfObjects<StationConnectionInfo*> (T->object);
        newtolist->object = new StationConnectionInfo;
        newtolist->object->adjacentStnIndex = T->object->adjacentStnIndex;
        newtolist->object->trains = I;
        nl = newtolist; 
      }
      else if (T->object->adjacentStnIndex == dest){    // selectively putting the destination at the top if adjacent to the station
        listOfObjects<StationConnectionInfo*>* D = new listOfObjects<StationConnectionInfo*> (T->object);
        D->next = newtolist;
        D->object->trains = I;
        newtolist = D;
      }
      else{
        nl->next = new listOfObjects<StationConnectionInfo*> (T->object);
        nl = nl->next;
        nl->object = new StationConnectionInfo;
        nl->object->adjacentStnIndex = T->object->adjacentStnIndex;
        nl->object->trains = I;
      }
    }
    T = T->next;
  }
  return newtolist;
}

// this function returns the list of all direct journeys in a linked list
listOfObjects<TrainInfoPerStation*>* list_trains(int source, int dest, StationAdjacencyList *adjacency){
  listOfObjects<TrainInfoPerStation*>* final_list = nullptr;
  listOfObjects<TrainInfoPerStation*>* end_list = nullptr;
  listOfObjects<StationConnectionInfo*> *S = adjacency[source].toStations;
  listOfObjects<StationConnectionInfo*>* queue = S;
  listOfObjects<StationConnectionInfo*>* end = nullptr;
  // listOfObjects<StationConnectionInfo*>* p = nullptr;
  if (S == nullptr){
    return nullptr;
  }
  int j = 0;
  while(S != nullptr){    // handling the immediate adjacent stations
    if (S != nullptr && S->object->adjacentStnIndex == dest){
      if (final_list == nullptr){
        final_list = new listOfObjects<TrainInfoPerStation*> (*S->object->trains);
        end_list = final_list;
        while(end_list->next != nullptr){
          end_list = end_list->next;
        }
      }
      else {
        end_list->next = new listOfObjects<TrainInfoPerStation*> (*S->object->trains);  
        while(end_list->next != nullptr){
          end_list = end_list->next;
        }
      }
      
    }
    else {
      if (j == 0){
        queue = S;
        j++;
      }
      if (end == nullptr){
        end = S;
      }
      else{
        end->next = S;
        end = end->next;
      }
      
    }
    S = S->next;
  }

  while(queue != nullptr){      // adding and processing the queue until it becomes empty

    S = find_trains(queue->object->trains, adjacency[queue->object->adjacentStnIndex].toStations, dest);
    while (S != nullptr && S->object->adjacentStnIndex == dest){
      if (final_list == nullptr){
        final_list = new listOfObjects<TrainInfoPerStation*> (*S->object->trains);
        end_list = final_list;
        while(end_list->next != nullptr){
          end_list = end_list->next;
        }
      }
      else {
        end_list->next = new listOfObjects<TrainInfoPerStation*> (*S->object->trains);  
        while(end_list->next != nullptr){
          end_list = end_list->next;
        }
      }
      S = S->next;
      
    }
      if (end != nullptr){
        end->next = S;
        while (end->next != nullptr){
          end = end->next;
        }
      }

    queue = queue->next;

  }
  return final_list;
}



void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  int source = stnNameToIndex.get(srcStnName)->value;
  int dest = stnNameToIndex.get(destStnName)->value;

  listOfObjects<TrainInfoPerStation*> *A = list_trains(source, dest, adjacency);
  // listOfObjects<StationConnectionInfo*> *B = adjacency[source].toStations;
  if (A == nullptr){
    cout << "No direct journeys available" << endl;
  }
  printStationInfo(A);    // printing the linked list
  
  return;
}