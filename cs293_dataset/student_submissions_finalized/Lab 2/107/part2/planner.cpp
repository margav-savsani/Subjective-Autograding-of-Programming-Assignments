#include "planner.h"

Journey::Journey()
{
  start=NULL;
  end=NULL;
  start_time=0;
  finish_time=0;
};


Station::Station()
{
  mark=-1;  // empty marker
}

Query1::Query1()
{
  start_time=0;
}

Query1::Query1(const Query1& cpy)
{
  this->start_time= cpy.start_time;
  strcpy(this->name, cpy.name);
}

Query2::Query2()
{
  start= NULL;
  inter= NULL;
  end= NULL;
  start_time1=0;
  finish_time1=0;
  start_time2=0;
  finish_time2=0;
}


Planner::Planner(){}

bool Planner::insertJourney(char station_one[], float start_time, char station_two[], float finish_time)
{
  Station *st_one= stations.get(station_one);
  if(st_one==NULL)  // station_one is not there in our dictionary
  {
    if(stations.put(station_one)) // add station_one
      st_one= stations.get(station_one);
    else
      return false; // if our dictionary is full
  }
  Station *st_two= stations.get(station_two);
  if(st_two==NULL)  // station_two is not there in our dictionary
  {
    if(stations.put(station_two))  // add station_two
      st_two= stations.get(station_two);
    else
      return false;  // if our dictionary is full
  }
  Journey journey;  // adding journey to queue of journeys from station_one
  journey.start=st_one;
  journey.end=st_two;
  journey.start_time= start_time;
  journey.finish_time= finish_time;
  (st_one->todest).QInsert(journey);
  return true;
}

bool Planner::validStation(char station_one[])
{
  if(stations.get(station_one)==NULL)  // station_one is not there in our dictionary
    return false;
  return true;
}

LinearQueue<Query1> Planner::allTravels(char station_one[], float start_time)
{
  Station* st_one= stations.get(station_one);
  LinearQueue<Query1> list_all;  // we will return this Linear Queue of Query1 which will have all travels from station_one after start_time
  int sz= (st_one->todest).size();
  for(int i=0; i<sz; i++)
  {
    float etd = ((st_one->todest).allTravels())[i].start_time;
    if(etd<start_time)  // if our journey starts after the train has already left... then continue
      continue;
    Query1 qu;  // this Query1 will be added to list_all
    qu.start_time= etd;
    strcpy(qu.name, (((st_one->todest).allTravels())[i].end)->key);
    list_all.QInsert(qu);
  }
  return list_all;
}

Query2 Planner::earliestStart(char station_one[], float start_time, char station_two[])
{
  Station* st_one= stations.get(station_one);
  Station* st_two= stations.get(station_two);
  int sz1= (st_one->todest).size();
  Query2 qu;   // we will return this Query2 which will have the earliest train from station_one to station_two after start_time
  qu.start=st_one;
  bool atleast1= false;
  for(int i=0; i<sz1; i++)
  {
    Journey ins= ((st_one->todest).allTravels())[i];
    if(start_time>ins.start_time)  // if our journey starts after the train has already left... then continue
      continue;
    if(ins.end==st_two) // if this a direct journey
    {
      if(!atleast1) // if no journey until now leads us to destination
      {
        qu.end=st_two;
        qu.start_time1= ins.start_time;
        qu.finish_time1= ins.finish_time;
        atleast1=true;
      }
      else if(ins.start_time< qu.start_time1) // checks if this journey has an early start than the one in qu
      {
        qu.inter= NULL;
        qu.start_time1=ins.start_time;
        qu.finish_time1= ins.finish_time;
        qu.start_time2= 0;
        qu.finish_time2= 0;
      }
    }
    else
    {
      int sz2= ((ins.end)->todest).size();
      for(int j=0; j<sz2; j++)
      {
        Station *inter= ins.end;
        Journey ins2= ((inter->todest).allTravels())[j];
        if(ins2.end==st_two && ins2.start_time>=ins.finish_time)  // if this journey has one stop
        {
          if(!atleast1)  // if no journey until now leads us to destination
          {
            qu.inter= inter;
            qu.end=st_two;
            qu.start_time1= ins.start_time;
            qu.finish_time1= ins.finish_time;
            qu.start_time2= ins2.start_time;
            qu.finish_time2= ins2.finish_time;
            atleast1=true;
          }
          else if(ins.start_time< qu.start_time1)  // checks if this journey has an early start than the one in qu
          {
            qu.inter= ins2.start;
            qu.start_time1= ins.start_time;
            qu.finish_time1= ins.finish_time;
            qu.start_time2= ins2.start_time;
            qu.finish_time2= ins2.finish_time;
          }
        }
      }
    }
  }
  return qu;
}
