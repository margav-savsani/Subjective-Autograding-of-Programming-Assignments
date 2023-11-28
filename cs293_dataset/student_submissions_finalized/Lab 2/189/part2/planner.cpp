#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"dictionary.cpp"
#include"planner.h"
using namespace std;
void plannerHandler(Planner &planner){
  while(true) {
      char input[32];
    cout << ">>> " ;
    cin>>input;
    if(strcmp(input,"QUIT") == 0){
      break;
    }
    if(strcmp(input,"ADD") == 0){
        Station station;
        char station_a[32];
        char station_b[32];
        cin>> station_a;
        strcpy(station.name,station_a);
        float time1;
        cin>> time1;
        float time2;
        cin>> time2;
        cin>>station_b;
        int r= Planner::findFreeIndex(station_a);/*We will obtain the index available for the key which essentially in this case is station1's name*/
        Planner::A[r].journey.timeStart=time1;/*after getting the index of the dictionary of stations,we are equating the given data
        into the journey variable we have created for every station index*/
        PLanner::A[r].journey.timeEnd=time2;
    }
    if(strcmp(input,"QUERY_STATION")==0) {
        Station station;
        char station_name[32];
        cin>>station_name;
        Station* S;
        S=Planner::get(station_name);/*This is creating a pointer to the station which we are obtained that is referring to the key provided
        which is essentially the name of a station*/

        cout<<S->journey.station1<<endl;
        cout<<S->journey.station2<<endl;
        cout<<S->journey.timeStart<<endl;
        cout<<S->journey.timeEnd<<endl;

    }
  }
}

      



