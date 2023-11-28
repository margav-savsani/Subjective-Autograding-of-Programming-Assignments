#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"dictionary.cpp"
#include "planner.h"
using namespace std;

void QueryJourney(Dictionary &dict){
    char startstation[32];
    char endstation[32];
    float time;
    float currtime; //Stores the time of the soonest starting train found till now.
    bool found;
    found  = false;
    cin>>startstation;
    cin>>time;
    cin>>endstation;
    Entry *e; // for quering first journey
    Entry *f; // for quering second journey
    LongJourney J; // This is where we store the answer
    e = dict.get(startstation); //Query station 1
    if(e==NULL) {
        cout<< "No train starts here"<<endl; //This means no journey from this station has been added yet
        return ;
    }
    for(int i=0 ; i< e->stat.n; i++){
        if(e->stat.journeys[i].starttime>=time)
        {
            //Condition for direct train
            if(strcmp(e->stat.journeys[i].end,endstation) == 0 ){
                if(found == 0) {
                    currtime = e->stat.journeys[i].starttime;
                    found = true;
                }
                if(currtime >= e->stat.journeys[i].starttime){
                    //Adding journey to J.
                    currtime  = e->stat.journeys[i].starttime;
                    J.J1 = e->stat.journeys[i];
                    J.indirect = 0;
                }   
            }

            //Now we check for indirect journey
            else {
                f = dict.get(e->stat.journeys[i].end);
                //If f is NULL it means no train starts at the end station
                if(f!=NULL){
                    for(int j=0 ; j<f->stat.n; j++){

                        //The condition for the journey to be valid 
                        if(f->stat.journeys[j].starttime>=e->stat.journeys[i].endtime && strcmp(f->stat.journeys[j].end,endstation)==0){
                            if(found == 0) {
                                currtime = e->stat.journeys[i].starttime;
                                found = true;
                            }
                            if(currtime >= e->stat.journeys[i].starttime){
                                //Adding journey to J
                                currtime  = e->stat.journeys[i].starttime;
                                J.J1 = e->stat.journeys[i];
                                J.J2 = f->stat.journeys[j];
                                J.indirect = 1;
                            }
                        }
                    }
                }
                
            }
        }
    }
    if(found==0) cout<<"No such journey exists"<<endl;
    else J.print();
}

void Query_Handler(){
    Dictionary dict; //The main dictionary which stores all stations 
    while(true){
        char input[32];
        // cout<<">>> "; // Add for interactive mode 
        cin>>input;
        if(strcmp(input,"EXIT") == 0){
        break; // EXIt condition
        }

        else if(strcmp(input,"ADD")==0){
            //ADD condition
            char station1[32];
            char station2[32];
            float starttime,finishtime;
            cin>>station1;
            cin>>starttime;
            cin>>station2;
            cin>>finishtime;

            //Firstly we create a journey
            Journey J;
            strcpy(J.start,station1);
            strcpy(J.end,station2);
            J.starttime = starttime;
            J.endtime = finishtime;

            //Now we query the station key to the dictionary
            Entry *e;
            e = dict.get(station1);
            if (e==NULL) {
                //In this case the station needs to be created 
                Entry f;
                f.stat.n = 1;
                f.stat.journeys[0] = J;
                strcpy(f.key , station1);
                dict.put(f);
            }
            else {
                //In this case just add the journey to the station
                e->stat.journeys[e->stat.n] = J;
                e->stat.n++;

            }

        }

        else if(strcmp(input,"QUERY_STATION")==0){
            //This just accesses the station and lists all journeys starting there after start time
            char station[32];
            float time;
            cin>>station;
            cin>>time;
            Entry *e;
            e = dict.get(station);
            if(e==NULL) cout<<"Error";
            else{
                int si = e->stat.n;
                for(int i=0;i <si ; i++){
                    if(e->stat.journeys[i].starttime>= time) e->stat.journeys[i].print();
                }
            } 
        }

        else if(strcmp(input,"QUERY_JOURNEY")==0){
            //Seperate function for this query
            QueryJourney(dict);
        }

    }
}

int main(){
    Query_Handler();
    return 0;
}