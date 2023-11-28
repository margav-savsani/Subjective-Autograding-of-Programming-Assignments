#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include "planner.cpp"


void queryHandler(Planner &planner){
  for(int i=0;i>=0;i++)
  {
    char input[32];
    // cout << ">>> " ;
    cin>>input;
    if(strcmp(input,"EXIT") == 0){
      break;
    }

    // ADD <station_one> <start_time> <station_two> <finish_time>
    if(strcmp(input,"ADD") == 0){
      char station_one[32];
      cin >> station_one;
      float start_time;
      cin >> start_time;
      char station_two[32];
      cin >> station_two;
      int finish_time;
      cin >> finish_time;
      Journey train;
      strcpy(train.station_one,station_one);
      train.start_time=start_time;
      strcpy(train.station_two,station_two);
      train.finish_time=finish_time;
      int hashValueData = planner.hashValue(train.station_one);
      int freeIndexData = planner.findFreeIndex(train.station_one);
      // cout << "Hash Value: " << hashValueData << endl;
      // cout << "Free Location: "<< freeIndexData << endl;

      if(freeIndexData >= 0){
        planner.addJourney(train);
        // cout << "Successfully Added " << endl;
      }
      else{
        // cout << "NO Available space " << endl;
      }
      //
    }

    // QUERY_STATION <station_one> <start_time>
    else if(strcmp(input, "QUERY_STATION") == 0){
      char station_one[32];
      cin >> station_one;
      float start_time;
      cin >> start_time;
      vector<Journey> trains;
      trains = planner.returnTrains(station_one,start_time);
      if(trains.size()==0){cout<<"Error:Station Not Found!\n";}
      for(int i=0;i<trains.size();i++){
        cout<<trains[i].start_time<<" "<<trains[i].station_two<<endl;
      }
    }

    // QUERY_JOURNEY <station_one> <start_time> <station_two>
    else if(strcmp(input,"QUERY_JOURNEY") == 0){
      char station_one[32];
      cin >> station_one;
      float start_time;
      cin >> start_time;
      char station_two[32];
      cin >> station_two;
      planner.printJourney(station_one, start_time, station_two);
    }
  }
}

void interactive()
{
  // cout<<"Welcome to Planner \n";
  Planner planner;
  queryHandler(planner);
}


int main()
{
  // cout<<"Enter 1 to start"<<endl;
  int which=1;
  // cin>>which;
  
  if(which == 1){
    interactive();
  }
  else {
    return 0;
  }
  return 0;
}