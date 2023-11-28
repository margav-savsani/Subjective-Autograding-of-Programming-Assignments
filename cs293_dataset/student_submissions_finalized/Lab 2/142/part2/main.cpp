#include<iostream>
#include"planner.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include<cstring>
using namespace std;


int main(){
	 for(int i=0;i>=0;i++){
		char input[32];
		cin >> input;
		if(!strcmp(input,"EXIT"))break;

	 if(strcmp(input,"ADD") == 0){
      Train data;
      char inputKey1[32], inputKey2[32];
      float t1, t2;
      cin >> inputKey1 >> t1 >> inputKey2 >> t2;

      strcpy(data.start_station.name,inputKey1);
      data.start_time = t1;
      strcpy(data.end_station.name,inputKey2);
      data.end_time = t2;

      int hashValueData1 = hashValue(data.start_station.name);
      int freeIndexData1 = findFreeIndex(data.start_station.name);
      int hashValueData2 = hashValue(data.end_station.name);
      int freeIndexData2 = findFreeIndex(data.end_station.name);

      Planner p;

      if(freeIndexData1 >= 0){
        p.add(data.start_station, t1, data.end_station, t2);
        cout << "Successfully Added " << endl;
      }
      else{
        cout << "NO Available space " << endl;
      }
    }

    // DEL <key>
    else if(strcmp(input, "QUERY_STATION") == 0){
      float t;
      Planner p;
      Train data;
      char inputKey[32];
      cin >> inputKey >> t;
      strcpy(data.start_station.name,inputKey);
      data.start_time = t;
      p.getquerystation(data.start_station,data.start_time);
    }

    // FIND <key>
    else if(strcmp(input,"QUERY_JOURNEY") == 0){
      float t;
      Planner p;
      Train data;
      char inputKey1[32]; char inputKey2[32];
      cin >> inputKey1 >> t >> inputKey2;
      strcpy(data.start_station.name,inputKey1);
      strcpy(data.end_station.name,inputKey2);
      data.start_time = t;
      p.queryjourney(data.start_station,t,data.end_station);
    }
  }
}
	/*if(!strcmp(command,"ADD")){
		Station s1, s2;
		float t1, t2;
		cin >> s1 >> t1 >> s2 >> t2;
		add(s1,t1,s2,t2);
	}
	if(!strcmp(command,"QUERY_STATION")){
		Station s1;
		float t1;
		cin >> s1 >> t1;
		getquerystation(s1,t1);
	}
	if(!strcmp(command,"QUERY_JOURNEY")){
		Station s1, s2;
		float t1;
		cin >> s1 >> t1 >> s2;
		queryjourney(s1, t1, s2 );
	}
	if(!strcmp(command,"EXIT")){
		return 0;
	}



}*/