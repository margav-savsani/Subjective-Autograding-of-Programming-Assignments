#include <iostream>
#include "planner.h"
#include "string.h"
using namespace std;

void rail_planner(Planner &P){
    for(int i=0;i>=0;i++){
        char input[32];
        cin>>input;
        if(strcmp(input,"EXIT") == 0){
            break;
        }
        if(strcmp(input,"ADD") == 0){
            char start_station[32];
            cin>>start_station;
            float start_time;
            cin>>start_time;
            char end_station[32];
            cin>>end_station;
            float end_time;
            cin>>end_time;
            P.add_journey(start_station, start_time, end_station, end_time);         
        }
        if(strcmp(input,"QUERY_STATION") == 0){
            char station[32];
            cin>>station;
            float start;
            cin>>start;
            P.all_trains(station, start);
        }
        if(strcmp(input,"QUERY_JOURNEY") == 0){
            char start_station[32];
            cin>>start_station;
            float start_time;
            cin>>start_time;
            char end_station[32];
            cin>>end_station;
            P.soonest(start_station, start_time, end_station);
        }
    }
}

int main(){
    Planner P;
    rail_planner(P);
}