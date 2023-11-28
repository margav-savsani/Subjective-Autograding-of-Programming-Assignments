#include<iostream>
#include<string>
#include"planner.h"
using namespace std;
//manipulated implementation
int main(){
    Planner pl;
    char c[20];
    
    while(true){
        cin>>c;
        //quit
        if(strcmp(c,"QUIT")==0) break;
        //add
        if(strcmp(c,"ADD")==0){
            string station1;
            string station2;
            int time1;
            int time2;
            cin>>station1>>time1>>station2>>time2;
            pl.ADD(station1,time1,station2,time2);
        }
        //query_journey
        if(strcmp(c,"QUERY_JOURNEY")==0){
            string station1;
            string station2;
            int time1;
            cin>>station1>>time1>>station2;
            pl.QUERY_JOURNEY(station1,time1,station2);
        }
        //query_station
        if(strcmp(c,"QUERY_STATION")==0){
            string station1;
            int time1;
            cin>>station1>>time1;
            pl.QUERY_STATION(station1,time1);
        }
    }
}