#include<iostream>

#include"planner.h"
using namespace std;

bool Planner:: isPresent(char station[]){

    if(stations.find(station)){
        return true;
    }
    else{
        return false;
    }
}



void Planner:: queryStation(char startStation[], float startTime){
    Entry * station = stations.get(startStation);
    // cout<<station->key;
    bool flag = false;
    // cout<<"Size"<<station->journeys.size();
    for(int i = 0; i<station->journeys.size();i++){
        // cout<<"Entered the loop" <<endl;
        if(station->journeys[i].startTime>=startTime){
            cout<<station->journeys[i].startTime<<" "<<station->journeys[i].endStation<<endl;
            flag = true;
        }
    }

    if(flag==false){
        cout<<"ERROR"<<endl;
    }
    
}

void Planner:: queryJourney(char startStation[], float startTime, char endStation[]){
    Entry * startstation = stations.get(startStation);

    Journey minJourney;
    strcpy(minJourney.startStation, startStation);
    minJourney.startTime = 1000000;
    bool isDirectJourney = false;

    
    for(int i =0; i<startstation->journeys.size();i++){
        if(startstation->journeys[i].startTime>=startTime && strcmp(startstation->journeys[i].endStation, endStation)==0){
            if(startstation->journeys[i].startTime<minJourney.startTime){
                // copying the parameters of minimum direct journey into min journey
                strcpy(minJourney.startStation, startstation->journeys[i].startStation);
                strcpy(minJourney.endStation, startstation->journeys[i].endStation);
                minJourney.startTime = startstation->journeys[i].startTime;
                minJourney.endTime = startstation->journeys[i].endTime;

                isDirectJourney = true;
            }
        }
        else if(startstation->journeys[i].startTime>=startTime){
            Entry * midstation = stations.get(startstation->journeys[i].endStation);
            for(int j = 0; j<midstation->journeys.size();j++){

                if(midstation->journeys[j].startTime>=startstation->journeys[i].endTime && strcmp(midstation->journeys[j].endStation, endStation)==0){
                    
                    if(startstation->journeys[i].startTime<minJourney.startTime){
                        // copying the parameters of minimum one-stop journey into min journey
                        strcpy(minJourney.startStation, startstation->journeys[i].startStation);
                        strcpy(minJourney.endStation, startstation->journeys[i].endStation); // midstation
                        minJourney.startTime = startstation->journeys[i].startTime;// start time
                        minJourney.endTime = midstation->journeys[j].startTime; // departure from middle stop
                    
                        isDirectJourney = false;
                    }
                }
            }
        }
    }
    if(minJourney.startTime == 1000000){
        cout<<"ERROR"<<endl;
    }
    else if(isDirectJourney){
        cout<<minJourney.startTime<<endl;
    }
    else{
        cout<<minJourney.startTime<<" "<<minJourney.endStation<<" "<<minJourney.endTime<<endl;
    }
}