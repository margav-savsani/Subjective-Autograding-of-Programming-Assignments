#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

listOfObjects<TrainInfoPerStation *> * gettrains(Dictionary<int> newstnnametoindex,StationAdjacencyList *newadjacency,listOfObjects<TrainInfoPerStation *> *list,string source,string dest,int jCode){
  Entry<int> *a = newstnnametoindex.get(source);
  int x = a->value;

  StationAdjacencyList b = newadjacency[x];
  listOfObjects<StationConnectionInfo *> *adjstat;
  adjstat = b.toStations;

  if(source.compare(dest)==0){
    return list;
  }

  for(int k=0;adjstat!=nullptr;adjstat = adjstat->next){
    listOfObjects<TrainInfoPerStation *> *listoftrains = adjstat->object->trains;

    for(int j=0;listoftrains!=nullptr;listoftrains = listoftrains->next){
      if(listoftrains->object->journeyCode == jCode){
        listOfObjects<TrainInfoPerStation *> *dummy = list;
        for(int i=0;dummy->next!=nullptr;i++){
          dummy = dummy->next;
        }
        listOfObjects<TrainInfoPerStation *> *p = new listOfObjects<TrainInfoPerStation *>(listoftrains->object);
        dummy->next = p;
        p->prev = dummy;
        return gettrains(newstnnametoindex,newadjacency,list,newstnnametoindex.getKeyAtIndex(adjstat->object->adjacentStnIndex),dest,jCode);
      }     
    }
  }

  listOfObjects<TrainInfoPerStation *> *nullity = nullptr;
  return nullity;
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  Entry<int>* a = stnNameToIndex.get(srcStnName);
  int x = a->value;
  Entry<int>* a1 = stnNameToIndex.get(destStnName);
  int y = a1->value;
  StationAdjacencyList b = adjacency[x];
  int nooftrains = 0;
  //cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  listOfObjects<TrainInfoPerStation*> *list = nullptr;
  listOfObjects<StationConnectionInfo *> *c = b.toStations;

  for(int i=0;c!=nullptr;c = c->next){
    int index = c->object->adjacentStnIndex;

    listOfObjects<TrainInfoPerStation *> *listoftrains = c->object->trains;
    for(int j=0;listoftrains!=nullptr;listoftrains = listoftrains->next){
      list = gettrains(stnNameToIndex,adjacency,new listOfObjects<TrainInfoPerStation *>(listoftrains->object),stnNameToIndex.getKeyAtIndex(index),destStnName,listoftrains->object->journeyCode);

      for(int l=0;l<1;nooftrains++){
        if(list!=nullptr){
          printStationInfo(list);
        }
        l++;
      }    
      }
  }

  if(nooftrains ==0){
    cout << "No direct journeys available" <<endl;
  }
  return;
}

#endif