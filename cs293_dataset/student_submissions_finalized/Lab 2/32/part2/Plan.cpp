#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.cpp"
using namespace std;



void dictionaryHandler(Planner &planner)
  {
  for(int i=0;i>=0;i++)
  {
    char input[64];
    cin>>input;

    if(strcmp(input,"EXIT") == 0)
    {
      break;
    }

    if(strcmp(input,"ADD") == 0){

      char station_one[300];
      cin >> station_one;

      float start_time;
      cin >> start_time;

      char station_two[300];
      cin >> station_two;

      float finish_time;
      cin >> finish_time;




      Station station;
      strcpy(station.station_one, station_one);
      strcpy(station.station_two, station_two);
      station.start_time  = start_time;
      station.finish_time = finish_time;

      planner.add(station);
    }

    else if(strcmp(input,"QUERY_STATION") == 0)
    {
      char station[300];
      cin >> station;

      float time;
      cin>>time;

      planner.query_station(station, time);


    }

    else if(strcmp(input, "QUERY_JOURNEY") == 0)
    {
       char station1[300];
       cin>>station1;

       float time;
       cin>>time;

       char station2[300];
       cin>>station2;

       planner.query_journey(station1, time, station2);
    }
  }}



int main()
  {
     Planner planner;
     dictionaryHandler (planner);
  };



