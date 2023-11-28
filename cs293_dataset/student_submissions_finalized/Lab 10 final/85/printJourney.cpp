#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
int d = 0;
bool route2(StationAdjacencyList *adjacency, int startstnindex, int laststnindex, int jcode, int stop, int transit)
{

  if (startstnindex == laststnindex && stop==0) return true;
  listOfObjects<StationConnectionInfo *> *toStations = adjacency[startstnindex].toStations;
  listOfObjects<TrainInfoPerStation *> *trains;
  if (d < stop)
  {
    while (toStations != nullptr)
    {
      trains = toStations->object->trains;
      listOfObjects<TrainInfoPerStation *> *c = trains;

      while (trains != nullptr)
      {
        if (trains->object->journeyCode == jcode)
        {
          if ((trains->object->arrTime) - (c->object->depTime) < transit)
          {

            d++;
            return route2(adjacency, toStations->object->adjacentStnIndex, laststnindex, jcode, stop, transit);
          }
        }
        trains = trains->next;
      }

      toStations = toStations->next;
    }
  }
  return false;
}

bool route(StationAdjacencyList *adjacency, int startstnindex, int laststnindex, int jcode, int stop, int transit,int days)
{
  bool check=false;
  if (startstnindex == laststnindex && stop>=0) return true;
  listOfObjects<StationConnectionInfo *> *toStations = adjacency[startstnindex].toStations;
  listOfObjects<TrainInfoPerStation *> *trains;
  
  while (toStations != nullptr)
  {
    trains = toStations->object->trains;
    while (trains != nullptr)
    {
      if (trains->object->journeyCode == jcode)
      {
        if (trains->object->daysOfWeek[days] && route(adjacency, toStations->object->adjacentStnIndex, laststnindex, jcode, stop, transit,days) )
        check=true;
      }
      if (trains->object->journeyCode != jcode)
      {
        if ( trains->object->daysOfWeek[days] &&  route(adjacency, toStations->object->adjacentStnIndex, laststnindex, trains->object->journeyCode, stop-1, transit,days))
        check=true;
      }
      trains = trains->next;
    }
    toStations = toStations->next;
  }
  return check;
}
void route1(StationAdjacencyList *adjacency, int startstnindex, int laststnindex, int jcode, int stop, int transit,int days)
{
  if (startstnindex == laststnindex && stop>=0){
    cout<<"Reached destination"<<endl;
    return;
  }
  listOfObjects<StationConnectionInfo *> *toStations = adjacency[startstnindex].toStations;
  listOfObjects<TrainInfoPerStation *> *trains;
  while (toStations != nullptr)
  {
    trains = toStations->object->trains;
    while (trains != nullptr)
    {
      if (trains->object->journeyCode == jcode)
      {
        if (trains->object->daysOfWeek[days] && route(adjacency, toStations->object->adjacentStnIndex, laststnindex, jcode, stop, transit,days) )
        route1(adjacency, toStations->object->adjacentStnIndex, laststnindex, jcode, stop, transit,days);
      }
       if (trains->object->journeyCode != jcode)
      {
        if ( trains->object->daysOfWeek[days] &&  route(adjacency, toStations->object->adjacentStnIndex, laststnindex, trains->object->journeyCode, stop-1, transit,days))
         cout <<BLUE<< "JourneyCode: "<<trains->object->journeyCode <<RESET<< " " <<RED<<"       Arr:"<<RESET<<trains->object->arrTime<<RED<<" Dep:"<<RESET<<trains->object->depTime<<endl;
      }
      trains = trains->next;
    }
    toStations = toStations->next;
  }
  return ;
   
}
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  Entry<int> *index1 = stnNameToIndex.get(srcStnName);
  int i1 = index1->value;

  Entry<int> *index2 = stnNameToIndex.get(destStnName);
  int i2 = index2->value;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp
  bool istravelable = false;
  listOfObjects<StationConnectionInfo *> *toStations = adjacency[i1].toStations;
  listOfObjects<TrainInfoPerStation *> *trains;
  int v=0;
  int u=0;
  while (v<7){
    while(u<=maxStopOvers){
      listOfObjects<StationConnectionInfo *> *toStations = adjacency[i1].toStations;
      string dayname[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
  while (toStations != nullptr)
  {
    trains = toStations->object->trains;
    while (trains != nullptr)
    {
      if (route(adjacency, toStations->object->adjacentStnIndex, i2, trains->object->journeyCode, u, maxTransitTime,v)&&trains->object->daysOfWeek[v])
      {
        istravelable = true;

        printStationInfo(trains);
        cout<<"-----Journey change----"<<endl;
         cout<< GREEN <<"Day(s): "<<RESET<<dayname[v]<<endl;
         route1(adjacency, toStations->object->adjacentStnIndex, i2, trains->object->journeyCode, u, maxTransitTime,v);
        break;
      }
      trains = trains->next;
    }
    toStations = toStations->next;
  }
  u++;}
  v++;}

  if (istravelable == false)
    cout << "No direct journeys in this route" << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

  return;
}

#endif
