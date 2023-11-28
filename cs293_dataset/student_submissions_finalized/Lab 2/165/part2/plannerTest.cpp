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

    //ADD <station_one> <start_time> <station_two> <finish_time>
    if(strcmp(input,"ADD") == 0){

      char station_one[32];
      cin >> station_one;
      double start_time;
      cin >> start_time;
      char station_two[32];
      cin >> station_two;
      double finish_time;
      cin >> finish_time;
      Entry query;
      query.free = false;//this place becomes occupied
      strcpy(query.key,station_one);
      query.value  = start_time;
      strcpy(query.station2,station_two);
      query.reachtime  = finish_time;
      planner.add(query);
    
    }

     if(strcmp(input,"QUERY_STATION") == 0){

      char station_one[32];
      cin >> station_one;
      double start_time;
      cin >> start_time;
      planner.station(station_one,start_time);//function called
    
    }

     if(strcmp(input,"QUERY_JOURNEY") == 0){

      char station_one[32];
      cin >> station_one;
      double start_time;
      cin >> start_time;
      char station_two[32];
      cin >> station_two;
      planner.journey(station_one,start_time,station_two);//function called
    
    }
  }
}


void interactive()
{
  cout<<"Welcome to Planner \n";
  cout<<"";
  Planner planner;
  plannerHandler(planner);
}


int main()
{
  
  interactive();
  return 0;
}
