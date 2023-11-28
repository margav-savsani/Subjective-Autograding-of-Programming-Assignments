#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.cpp"
using namespace std;

/*

In interactive mode you can give commands '
  EXIT
  ADD <station_one> <start_time> <station_two> <finish_time>
  QUERY_STATION <station_one> <start_time>
  QUERY_JOURNEY <station_one> <start_time> <station_two>

*/

void plannerHandler(Planner &planner){
  for(int i=0;i>=0;i++)
  {
    char input[32];
    cout << ">>> " ;
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
      float finish_time;
      cin >> finish_time;
      if(planner.insertJourney(station_one, start_time, station_two, finish_time)){
        cout << "Successfully Added " << endl;
      }
      else{
        cout << "No Available space " << endl;
      }
    }

    // QUERY_STATION <station_one> <start_time>
    else if(strcmp(input, "QUERY_STATION") == 0){
      char station_one[32];
      cin >> station_one;
      float start_time;
      cin >> start_time;
      if(planner.validStation(station_one)) { 
        LinearQueue<Query1> total= planner.allTravels(station_one, start_time);
        int num_travels= total.size();
        if(num_travels==0)
        {
          cout<<"No journey to display"<<endl;
          continue;
        }
        for(int i=0; i<num_travels; i++)
        {
          cout<<(total.allTravels())[i].start_time<<" "<<(total.allTravels())[i].name<<endl;
        }
      }
      else {
        cout<<"Beginning station doesn't exist"<<endl;
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
      float finish_time;
      if(planner.validStation(station_one) && planner.validStation(station_two)) {
        Query2 disp= planner.earliestStart(station_one, start_time, station_two);
        if(disp.end==NULL)
        {
          cout<<"No train to Destination station"<<endl;
        }
        else
        {
          if(disp.inter==NULL)
          {
            cout<<disp.start_time1<<endl;
          }
          else
          {
            cout<<disp.start_time1<<" "<<(disp.inter)->key<<" "<<disp.start_time2<<endl;
          }
        }
      }
      else {
        cout<<"Atleast one of the stations given doesn't exist"<<endl;
      }
    }
  }
}

void interactive()
{
  cout<<"Welcome to RAIL PLANNER\n";
  cout<<"";
  Planner planner;
  plannerHandler(planner);
}


int main()
{
  interactive();
  return 0;
}
