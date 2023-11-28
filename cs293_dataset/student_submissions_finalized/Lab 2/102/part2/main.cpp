#include<iostream>
#include"planner1.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
using namespace std;


int main(){
    
    while(true)
    {
    char input[32];
    cout << ">>> " ;
    cin>>input;
    if(strcmp(input,"QUIT") == 0){
      break;
    }
    // ADD <key> <value>
    if(strcmp(input,"ADD") == 0){
      train data;
      char inputKey[32];
      int time;
      char inputKey1[32];
      int time1;
      cout<<"Enter start station : ";
      cin >> inputKey;
      cout<<"Enter start time : ";
      cin >> time;
      cout<<"Enter end station : ";
      cin >> inputKey1;
      cout<<"Enter end time : ";
      cin >> time1;
      strcpy(data.start_station.station_name,inputKey);
      strcpy(data.end_station.station_name,inputKey1);
      data.start_time  = time;
      data.end_time= time1;
      int hashValueData = hashValue(data.start_station.station_name);
      int freeIndexData = findFreeIndex(data.start_station.station_name);
      int hashValueData1 = hashValue(data.end_station.station_name);
      int freeIndexData1 = findFreeIndex(data.end_station.station_name);
      cout << "Hash Value: " << hashValueData << endl;
      cout << "Free Location: "<< freeIndexData << endl;
      cout << "Hash Value1: " << hashValueData1 << endl;
      cout << "Free Location1: "<< freeIndexData1 << endl;
      if(freeIndexData >= 0){
        data.add_station(data.start_station,time,data.end_station,data.end_time);
        cout << "Successfully Added " << endl;
      }
      else{
        cout << "NO Available space " << endl;
      }
    }
    else if(strcmp(input,"QUERY_STATION") == 0){
      Query Q;
      train data;
      char inputKey[32];
      int time;
      cout<<"Enter start station : ";
      cin >> inputKey;
      cout<<"Enter start time : ";
      cin >> time;
      strcpy(data.start_station.station_name,inputKey);
      data.start_time=time;
      Q.query_Station(data.start_station,data.start_time);
    }

    if(strcmp(input,"QUERY_JOURNEY") == 0){
      Query Q;
      train data;
      Station Destination;
      char inputKey[32];
      char inputKey2[32];
      int time;
      cout<<"Enter start station : ";
      cin >> inputKey;
      cout<<"Enter start time : ";
      cin >> time; 
      cout<<"Enter Destination station : ";
      cin>>inputKey2;
      strcpy(data.start_station.station_name,inputKey);
      data.start_time=time;
      strcpy(Destination.station_name,inputKey2);
      Q.query_Journey(data.start_station,time,Destination);
      
    }


    }
    
}

