#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include "planner.h"
#include "dictionary.h"
using namespace std;


//I created this file to test the planner class

void plannerHandler(Planner &planner){
  for(int i=0;i>=0;i++)
  {
    char input[32];
    cout << ">>> " ;
    cin>>input;

    // EXIT
    if(strcmp(input,"EXIT") == 0){
      break;
    }

    // ADD <station_one> <start_time> <station_two> <finish_time>
    if(strcmp(input,"ADD") == 0){

      char station1[32],station2[32];
      float start,finish;
      cin >> station1>>start>>station2>>finish;

      Entry jstart,jend;
      strcpy(jstart.key,station1);
      jstart.value  = start;
      strcpy(jend.key,station2);
      jend.value  = finish;
      int freeIndex1=planner.getStarts().findFreeIndex(station1);
      if(freeIndex1 >= 0){
        int index=planner.addJourney(jstart,1,0);
        planner.addJourney(jend,2,index);
        cout << "Successfully Added " << endl;
      }
      else{
        cout << "No Available space " << endl;
      }
      
    }

    // QUERY_STATION <station_one> <start_time>
    else if(strcmp(input, "QUERY_STATION") == 0){
      char station[32];
      cin >> station;
      float startTime;
      cin>>startTime;
      planner.queryStation(station,startTime);
    }

    // QUERY_JOURNEY <station_one> <start_time> <station_two>
    else if(strcmp(input,"QUERY_JOURNEY") == 0){
      char st1[32],st2[32];
      float startTime;
      cin>>st1>>startTime>>st2;
      planner.queryJourney(st1,st2,startTime);
    }

    //planner.showJourneys();
    //planner.showStations();
  }
}

int main(){
    Planner planner;
    plannerHandler(planner);
    return 0;
}