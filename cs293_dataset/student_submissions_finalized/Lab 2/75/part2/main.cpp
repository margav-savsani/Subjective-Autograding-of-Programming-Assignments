#include<iostream>
#include<string>
#include"planner.cpp"
using namespace std;

int main(){
    Planner planner;
    cout<<"Enter ADD, QUERY_STATION or QUERY_JOURNEY along with required parameters"<<endl;

    string instruction = "";

    while (true){
        cin>> instruction;

        if(instruction=="ADD"){
            char startStation[32];
            char endStation[32];
            float startTime;
            float endTime;

            cin>>startStation;
            cin>>startTime;
            cin>>endStation;
            cin>>endTime;

            Journey journey;
            journey.startTime = startTime;
            journey.endTime = endTime;
            strcpy(journey.endStation, endStation);
            strcpy(journey.startStation, startStation);

            if(planner.isPresent(startStation)){
                Entry * stationentry = planner.stations.get(startStation);
                stationentry->journeys.push_back(journey);
                // cout<<"size "<<stationentry->journeys.size()<<endl;

                cout<<"Journey added successfully!!!"<<endl;
            }
            else{
                Entry newStation;
                strcpy(newStation.key, startStation);
                planner.stations.put(newStation);
                Entry * stationentry = planner.stations.get(startStation);
                stationentry->journeys.push_back(journey);
                
                // cout<<"size "<<stationentry->journeys.size()<<endl;
                strcpy(newStation.key, startStation);

                

                cout<<"New Station created and Journey added successfully!!!"<<endl;
            }

        }
        else if(instruction=="QUERY_STATION"){
            char startStation[32];
            float startTime;

            cin>>startStation;
            cin>>startTime;

            planner.queryStation(startStation, startTime);
        }
        else if(instruction=="QUERY_JOURNEY"){
            char startStation[32];
            char endStation[32];
            float startTime;

            cin>>startStation;
            cin>>startTime;
            cin>>endStation;

            planner.queryJourney(startStation, startTime, endStation);
        }
        else if(instruction=="EXIT"){
            break;
        }
    }
}