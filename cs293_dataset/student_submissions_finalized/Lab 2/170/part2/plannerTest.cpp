#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.cpp"
using namespace std;

/*

In handler we have 
  EXIT
  ADD <station_one> <start_time> <station_two> <finish_time>
  QUERY_STATION <station_one> <start_time>

*/

void plannerHandler(Planner &planner){
  for(int i=0;i>=0;i++)
  {
    char input[20];
    cin>>input;
    if(strcmp(input,"EXIT") == 0){
      break;
    }

    // ADD <station_one> <start_time> <station_two> <finish_time>
    if(strcmp(input,"ADD") == 0){

      char station1[20];
      cin >> station1;
      float time1;
      cin >> time1;
      char station2[20];
      cin >> station2;
      float time2;
      cin >> time2;
      Journey data;
      strcpy(data.s1.s,station1);
      data.st = time1;
      strcpy(data.s2.s,station2);
      data.et = time2;
      int hashValueData = planner.hashValue(data.s1.s);
      int freeIndexData = planner.findFreeIndex(data.s1.s);
      cout << "Hash Value: " << hashValueData << endl;
      cout << "Free Location: "<< freeIndexData << endl;
      if(planner.findFreeIndex(data.s1.s) >= 0){
        planner.put(data);
        cout << "Successfully Added " << endl;
      }
      else{
        cout << "NO Available space " << endl;
      }
    }

    //QUERY_STATION <station_one> <start_time>
    else if(strcmp(input,"QUERY_STATION") == 0){
      char station[20];
      cin >> station;
      float time;
      cin >> time;
      Journey * q= planner.get(station, time);
      if(q[0].value==0)cout<<"ERROR"<<endl;
      else { 
      for(int i=0; q[i].value!=0; i++){
	cout<<q[i].st<<" "<<q[i].s2.s<<endl;
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
