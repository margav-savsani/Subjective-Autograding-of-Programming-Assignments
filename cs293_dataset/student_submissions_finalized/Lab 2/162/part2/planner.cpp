#include "planner.h"
#include<vector>
#include <iostream>

const int int_max =2147483647;
void Planner::ADD(Query query)
{
  Entry *station = stations.get(query.journey.station1.stationName);
  if (station == NULL)
    station = new Entry;
  strcpy(station->stationName, query.journey.station1.stationName);
  stations.put(*station);
  station = stations.get(query.journey.station1.stationName);
  station->journeys.QInsert(query.journey);
}

vector<Journey> Planner::QUERY_STATION(Query query)
{
  Entry *station = stations.get(query.journey.station1.stationName);
  vector<Journey> journeys;
  if (station == NULL)
    return journeys;
  // std::cout<<"here";
  // cout<<"hehr";
  
  // cout<<"hehr";
  for (int i = 0; i < station->journeys.size(); i++)
  { 
    Journey j = station->journeys[(i+station->journeys.returnHead())%(station->journeys.trueSize())];
    if(query.journey.startTime > j.startTime)
    {break;}
    journeys.push_back(j);
    
  }
  
  
  return journeys;
}

ThreeTuple Planner::QUERY_JOURNEY(Query query)
{
  Entry *station = stations.get(query.journey.station1.stationName);
  ThreeTuple result;
  result.n1 = int_max;
  result.n2= int_max;
  if (station == NULL)
  {
    return result;
  }

  vector<Journey> journeysNotOccured;

  for (int i =0; i < station->journeys.size(); i++)
  { 
    Journey j = station->journeys[(i+station->journeys.returnHead())%(station->journeys.trueSize())];

    if (j.startTime < query.journey.startTime)
    {
      // cout<<"Called"<<endl;
      break;
    }
    journeysNotOccured.push_back(j);
  }
  float minTime = int_max;
  float interTime = int_max;
  char interStn[32];
  //1st pass, look into only one station
  vector<Entry *> intermediateStations;
  vector<float> timeofArrivals;
  vector<float> timeofStarts;

  for (auto j : journeysNotOccured)
  {
    if (strcmp(j.station2.stationName, query.journey.station2.stationName) == 0)
    {

      minTime = (minTime > j.startTime) ? j.startTime : minTime;
      strcpy(interStn,"NULL");
    }
    else
    {
      Entry *interStation = stations.get(j.station2.stationName);
      if (interStation != NULL)
      {
        intermediateStations.push_back(interStation);
        timeofArrivals.push_back(j.endTime);
        timeofStarts.push_back(j.startTime);
      }
    }
  }
  //2nd pass, see if its possible to go to destination using an intermediate station
  for (int i = 0; i < intermediateStations.size(); i++)
  {
    vector<Journey> journeysFromInterNotOccured;

    for (int j = 0; j < intermediateStations[i]->journeys.size(); j++ )
    { 
      Journey k = intermediateStations[i]->journeys[(j+intermediateStations[i]->journeys.returnHead())%(intermediateStations[i]->journeys.trueSize())];
      if (k.startTime < timeofArrivals[i])
      {
        break;
      }
      journeysFromInterNotOccured.push_back(k);
    }

    for (auto j : journeysFromInterNotOccured)
    {
      if (strcmp(j.station2.stationName, query.journey.station2.stationName) == 0)
      {
        if(minTime  > timeofStarts[i] )
        {
          minTime  = timeofStarts[i];
          interTime  = j.startTime;
          strcpy(interStn,j.station1.stationName);
        }
        
        
        
      }
    }
  }
  result.n1 = minTime;
  result.n2 = interTime;
  strcpy(result.string,interStn);

  return result;
}
