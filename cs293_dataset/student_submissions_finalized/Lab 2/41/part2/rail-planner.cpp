#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.h"
using namespace std;

float minimum_val(float a1, float a2){
  if(a1>=a2) return a2;
  else return a1;
}

void rail_planner(){
  Planner plan;
  int i = 0;
  for(int i=0;i>=0;i++)
  {
    char input[20];
    cin >> input;
    if(strcmp(input,"EXIT") == 0)
    {
      exit(0);
    }

    if(strcmp(input,"ADD") == 0)
    {
      string station_one, station_two;
      float time_one, time_two;
      cin >> station_one >> time_one >> station_two >> time_two;
      plan.Store_Station(station_one, station_two);
      plan.Store_Journey(time_one, time_two);
      // Entry data;
      // strcpy(data.key,station_one);
      // data.value = i; i++;
    }


    if(strcmp(input, "QUERY_STATION") == 0)
    {
      string q_station_one;
      float q_time_one;
      cin >> q_station_one >> q_time_one;
      plan.Query_list_request(q_station_one,q_time_one);
    }

    if(strcmp(input,"QUERY_JOURNEY") == 0)
    {
      string j_station_one, j_station_two;
      float j_time;
      cin >> j_station_one >> j_time >> j_station_two;
      plan.Query_Journey(j_station_one,j_time,j_station_two);
    }
  }
}

void Planner::Query_list_request(string q_station_start,float q_time_presence){

    for (int j=0;j<index;j++)
    {
      if(q_station_start.compare(station_one[j])==0 && (q_time_presence<=time_one[j]))
      {
        cout << time_one[j] << " " << station_two[j] << endl;
      }
    }
  }

void Planner::Query_Journey(string j_station_start, float j_time, string j_station_end){
  float diff=10000;
  float prev_st, end_st=0;
    for(int j = 0; j<index; j++)
    {
      if(j_station_start.compare(station_one[j])==0 && j_station_end.compare(station_two[j])==0)
      {
        if(j_time<=time_one[j])
        { 
            prev_st = diff;
            diff=minimum_val(diff,time_one[j]);
            
            if((diff!=prev_st)){
              end_st=time_two[j];
            }

            if((minimum_val(end_st,time_two[j])!=end_st) && (diff==prev_st)){
              end_st=minimum_val(end_st,time_two[j]);
          }
        }
      }
    }
    
    if(diff==10000) cout << "ERROR" << endl;
    else cout << diff << endl;
}

int main()
{
  rail_planner();
  return 0;
}
