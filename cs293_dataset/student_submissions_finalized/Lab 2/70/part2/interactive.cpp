#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"dictionary.cpp"
#include "circularQueue.h"
#include "planner.cpp"
using namespace std;

/* 

In interactive mode you can give commands 
	ADD <station_one> <start_time> <station_two> <finish_time>
	QUERY_STATION <station_one> <start_time>
	QUERY_JOURNEY <station_one> <start_time> <station_two>

*/
void railplanner(Planner &planner){
	for(int i=0; i>=0; i++){
		char input[32];
		cout << ">>> ";
		cin >> input;
		if(strcmp(input,"EXIT") == 0){
      		break;
      	}

      	if(strcmp(input,"ADD") == 0){
      		char station1[32];
      		cin >> station1;
      		int start;
      		cin >> start;
      		char station2[32];
      		cin >> station2;
      		int finish;
      		cin >> finish;
      		Journey j;
			strcpy(j.s1.name,station1);
			strcpy(j.s2.name,station2);
			j.start = start;
			j.finish = finish;
			if(planner.findFreeIndex1(station1)!=-1){
				planner.Add(j);
			}
      	}

      	else if(strcmp(input, "QUERY_STATION")==0){
      		char station[32];
      		cin >> station;
      		int time;
      		cin >> time;
      		station_query sq;
			strcpy(sq.s.name, station);
			sq.start_time = time;
			planner.query_station(sq);
      	}

      	else if(strcmp(input,"QUERY_JOURNEY")==0){
      		char stationa[32];
      		cin >> stationa;
      		int time2;
      		cin >> time2;
      		char stationb[32];
      		cin >> stationb;
      		journey_query jq;
			strcpy(jq.s1.name, stationa);
			strcpy(jq.s2.name, stationb);
			jq.start_time = time2;
			planner.query_journey(jq);
      	}
	}
}
int main(){
	Planner p;
	cout <<"You Have Entered interactive mode"<<endl;
	railplanner(p);
	return 0;

}