#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.cpp"
using namespace std;

void plannerHandler(Planner &planner){
  for(int i=0;i>=0;i++){
    char input[32];
    cout << ">>> " ;
    cin>>input;
    if(strcmp(input,"EXIT") == 0){
      break;
    }
  
    // INS <key> <value>
    if(strcmp(input,"ADD") == 0){

      char inputKey1[32];
      cin >> inputKey1;//station_one
      float start_time;
      cin >> start_time;

      char inputKey2[32];
      cin >> inputKey2;//station_two
      float end_time;
      cin >> end_time;

      Journey data;
      strcpy(data.station_one,inputKey1);
      data.start_time=start_time;
      strcpy(data.station_two,inputKey2);
      data.end_time=end_time;

      
      int hashValueData = planner.hashValue(data.station_one); //hashValue for station_one name
      int freeIndexData = planner.findFreeIndex(data.station_one);
      cout << "Free Location: "<< freeIndexData << endl;
      if(freeIndexData >= 0){
        planner.put(data);
      }
      else{
        cout << "CANNOT " << endl;
      }
    }

    if(strcmp(input,"QUERY_STATION") == 0){

      char inputKey1[32];
      cin >> inputKey1;//station_one
      float start_time;
      cin >> start_time;

      Journey data;
      strcpy(data.station_one,inputKey1);
      data.start_time=start_time;
      
        planner.func(data);
      
    }

    if(strcmp(input,"QUERY_JOURNEY") == 0){

      char inputKey1[32];
      cin >> inputKey1;//station_one
      float start_time;
      cin >> start_time;
      char inputKey2[32];
      cin >> inputKey2;

      Journey data;
      strcpy(data.station_one,inputKey1);
      data.start_time=start_time;
      strcpy(data.station_two,inputKey2);
      
    int hashValueData = planner.hashValue(data.station_one); //hashValue for station_one name
      int freeIndexData = planner.findFreeIndex(data.station_one);
      
      if(freeIndexData >= 0){
        planner.que(data);
      }
      else{
        cout << "NO SUCH STATION" << endl;
      }
    }
  } 
}

void interactive(){
  cout<<"RAILWAY PLANNER :) \n";
  cout<<"";
  Planner planner;
  plannerHandler(planner);
}


int main(){
interactive();
return 0;
}

