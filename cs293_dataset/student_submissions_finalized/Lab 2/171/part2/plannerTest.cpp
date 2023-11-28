#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.cpp"
using namespace std;

/*

In interactive mode you can give commands '
  ADD <station_one> <start_time> <station_two> <finish_time>
  QUERY_STATION <station_one> <start_time>
  QUERY_JOURNEY <station_one> <start_time> <station_two>
  EXIT 
*/

void plannerHandler(Planner &planner){
  for(int i=0;i>=0;i++)
  {
    char input[32];
    cin>>input;
    if(strcmp(input,"EXIT") == 0){
      break;
    }
    // INS <key> <value>
    if(strcmp(input,"ADD") == 0){

      char station1[32];
      cin >> station1;
      float time1;
      cin >> time1;
      char station2[32];
      cin >> station2;
      float time2;
      cin >> time2;
      Journey data;
      strcpy(data.s1,station1);
      data.t1=time1;
      strcpy(data.s2,station2);
      data.t2=time2;


      int hashValueData = planner.hashValue(data.s1);
      int freeIndexData = planner.findFreeIndex(data.s1);
      cout << "Hash Value: " << hashValueData << endl;
      cout << "Free Location: "<< freeIndexData << endl;
      if(freeIndexData >= 0){
        planner.put(data);
        cout << "Successfully Added " << endl;
      }
      else{
        cout << "NO Available space " << endl;
      }
    }

    else if(strcmp(input,"QUERY_STATION") == 0){
      char station[20];
      cin >> station;
      float time;
      cin >> time;
      Journey * j= planner.station(station, time);
      if(j[0].value==0)cout<<"ERROR"<<endl;
      else { 
        for(int i=0; j[i].value!=0; i++){
	      cout<<j[i].t1<<" "<<j[i].s2<<endl;
        }
      }
    }

    else if(strcmp(input,"QUERY_JOURNEY") == 0){
      char station1[20];
      cin >> station1;
      float time;
      cin >> time;
      char station2[20];
      cin >> station2;
      planner.soonest(station1, time, station2);	
    }

  }
}


int main()
{
  Planner planner;
  plannerHandler(planner);
   
  
  return 0;
}


