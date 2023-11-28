#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include "planner.cpp"
using namespace std;


void Handler(Planner &planner){
  for(int i=0;i>=0;i++)
  {
    char input[32];
    cout << ">>> " ;
    cin>>input;

    if(strcmp(input,"EXIT") == 0){
      break;
    }

    // ADD
    if(strcmp(input,"ADD") == 0){

      char station1[32];
      cin >> station1;
      float time1;
      cin >> time1;
      char station2[32];
      cin >> station2;
      float time2;
      cin >> time2;
      bool add = planner.add_journey(station1,time1,station2,time2);
      if(add==false){cout << "Couldn't add journey";}
    }

    // QUERY_STATION
    else if(strcmp(input, "QUERY_STATION") == 0){
      char station[32];
      cin >> station;
      float tm;
      cin >> tm;

      planner.query_station(station,tm);
    }

    // QUERY_JOURNEY
    else if(strcmp(input,"QUERY_JOURNEY") == 0){
      char station1[32];
      cin >> station1;
      float start;
      cin >> start;
      char station2[32];
      cin >> station2;

      bool jrn = planner.query_journey(station1,start,station2,0);
      if(jrn==false){
        cout << "No route available";
      }
    }
  }
}

int main(){
    Planner planner;
    Handler(planner);
}