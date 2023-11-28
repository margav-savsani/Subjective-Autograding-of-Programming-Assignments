#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

bool update(int t,int s,StationAdjacencyList *adjacency,int j)
{
  if(s==j)//base case for the reccursion
  {
    return true;
  }
  listOfObjects<StationConnectionInfo *> *to=adjacency[s].toStations;//finds the adjacent station of the current station
  while(to!=NULL)
  {
  listOfObjects<TrainInfoPerStation *> *tr=to->object->trains;
    while(tr!=NULL)
    {
      int k=tr->object->journeyCode;
        if(t==k)
        {
          return update(t,to->object->adjacentStnIndex,adjacency,j);//reccursion call 
        }
      tr=tr->next;
    }
    to=to->next;
  }
  return false;
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  listOfObjects<TrainInfoPerStation *> *station=nullptr;
  listOfObjects<TrainInfoPerStation *> *stat=nullptr;
  Entry<int> *index_start=stnNameToIndex.get(srcStnName);  //stoes the entry of the source station
  Entry<int> *index_end=stnNameToIndex.get(destStnName);  //stores the entry of the destination station
  int i=index_start->value;
  int j=index_end->value;
  listOfObjects<StationConnectionInfo *> *toS=adjacency[i].toStations;
  listOfObjects<StationConnectionInfo *> *fromS=adjacency[j].fromStations;
  listOfObjects<int> *arr=new listOfObjects<int> (0);
  listOfObjects<int> *array=arr;

  while(fromS!=NULL)
  {
  listOfObjects<TrainInfoPerStation *> *tra=fromS->object->trains;
    while(tra!=NULL)
    {
      int t=tra->object->journeyCode;
      arr->next=new listOfObjects<int>(t);//stores the codes of the from journeyCode 
      arr=arr->next;
      tra=tra->next;
    }
    fromS=fromS->next;
  }

  while(toS!=NULL)//runs the loop until all the stations are covered
  {
  listOfObjects<TrainInfoPerStation *> *tra=toS->object->trains;

    while(tra!=NULL)
    {
      int t=tra->object->journeyCode;
      listOfObjects<int>*dum=array;

      while(dum!=NULL)
      {
        if(t==dum->object)//checks if the code is present in from station of the destination station
        {
          if(update(t,toS->object->adjacentStnIndex,adjacency,j))//if the code is present in from station of the destination station 
                                                                //then it will reccursively check if the code is present in the next station
          {
            if(station==nullptr)
            {
              station=new listOfObjects<TrainInfoPerStation *>(tra->object);//updates the station for the first time
              stat=station;
            }
            else 
            {
              station->next=new listOfObjects<TrainInfoPerStation *>(tra->object);//updates the station for the other times
              station=station->next;
            }
          }
        }
        dum=dum->next;
      }

      tra=tra->next;
    }

    toS=toS->next;
  }
  if(stat!=nullptr){
  printStationInfo(stat);}//prints the station info if the stat is not equal to nullptr
  else
  cout << "No direct journeys available" << endl;//print a statement if the stat is equal to nullptr

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
