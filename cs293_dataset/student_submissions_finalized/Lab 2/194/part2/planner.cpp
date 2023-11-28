#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <cmath>
#include "planner.h"

using namespace std;

void trainPlanner(Planner &planner){
    for(int I=0;I>=0;I++){  //loop breaks only with EXIT
        char command[32];
        cin>>command;  //ADD,QUERY-JOURNEY,etc...

        if(strcmp(command,"EXIT")==0){ 
            break;  //exit the program
        }

        if(strcmp(command,"ADD")==0){ //ADD AN ENTRY
            char stn_one[32];
            cin >> stn_one;
            float strt_t;
            cin >> strt_t;
            char stn_two[32];
            cin >> stn_two;
            float end_t;
            cin >> end_t;
            Journey jour;
            strcpy(jour.station_1, stn_one);
            strcpy(jour.station_2, stn_two);
            jour.start_time=strt_t;
            jour.end_time=end_t;
            planner.put(jour);
        }   

        else if(strcmp(command,"QUERY_STATION")==0){  //All trains from station after a specified time
            char stn_one[32];
            cin>>stn_one;
            float strt_t;
            cin>>strt_t;
            int hash_val=planner.hashValue(stn_one);
            int count=0;  

            for(int i=hash_val; ;i=(i+1)%64){
                if(strcmp(planner.journey[i].station_1,stn_one)==0){
                    if(planner.journey[i].start_time>=strt_t){
                        cout<<planner.journey[i].start_time<<" "<<planner.journey[i].station_2<<endl;
                        count++;
                    }
                    else continue;
                }

                else if((strcmp(planner.journey[i].station_1,"")==0)||(i==hash_val-1)){
                    break;
                }
            }

            if(count==0){ //check whether there is atleast one train
                cout<<"No trains left!"<<endl;
            }
        }

        else if(strcmp(command,"QUERY_JOURNEY")==0){ //all trains which go from stn1 to stn2 with atmost one intermediate station with soonest starting time after the given time
            char stn_one[32];
            cin>>stn_one;
            float strt_t;
            cin>>strt_t;
            char stn_two[32];
            cin>>stn_two;
            int hash_val=planner.hashValue(stn_one);
            float start=9999999; //giving it a large value
            char intermediate[32];  //name of the intermediate station(if any)
            float int_leave=-1; //check whether intermediate station is present or train directly goes to destination

            for(int i=hash_val; strcmp(planner.journey[i].station_1,"")!=0 ; i=(i+1)%64){
                if((strcmp(stn_one,planner.journey[i].station_1)==0)&&(planner.journey[i].start_time>=strt_t)){                    
                    if(strcmp(planner.journey[i].station_2,stn_two)==0){
                        if(planner.journey[i].start_time<start){
                            start=planner.journey[i].start_time;
                        }
                        else continue;
                    }
                    else{
                        int hash_int=planner.hashValue(planner.journey[i].station_2);
                        for(int j=hash_int; strcmp(planner.journey[j].station_2,"")!=0 ;j=(j+1)%64){
                            if((strcmp(planner.journey[j].station_2,stn_two)==0) && (planner.journey[i].end_time<=planner.journey[j].start_time)){
                                if(planner.journey[i].start_time<start){
                                    start=planner.journey[i].start_time;
                                    strcpy(intermediate,planner.journey[i].station_2);
                                    int_leave=planner.journey[j].start_time;
                                }
                            }
                        }
                    }
                    if(i==hash_val-1){
                        break;
                    }     
                }

            }
            if(start==9999999){
                cout<<"NO PATH EXISTS"<<endl;
            }
            else if(int_leave==-1){
                cout<<start<<endl;
            }
            else{
                cout<<start<<" "<<intermediate<<" "<<int_leave<<endl;
            }
        }
    } 
}

int main(){
    Planner planner;
    trainPlanner(planner);
}
