# include<iostream>
# include "planner.h"
using namespace std;

void train_handler(Planner &planner){
    while(true)
    {
        char input[32];
        cin>>input;
        if(isequal(input,"EXIT")){
            break;
        }

        // ADD <station_one> <start_time> <station_two> <finish_time>
        if(isequal(input,"ADD"))
        {
            char start_station[32], end_station[32]; 
            float start_time, end_time;
            cin >> start_station >> start_time >> end_station >> end_time;

            if(!planner.add(start_station, start_time, end_station, end_time)){
                cout<<"ERROR: NO Available space"<<endl;
            }
        }

        // QUERY_STATION <station_one> <start_time>
        else if(isequal(input, "QUERY_STATION"))
        {
            char station[32];
            float time;
            cin >> station >> time;

            Journey* journey = planner.query_station(station, time);

            if(journey==NULL){
                cout<<"ERROR"<<endl;
            }
            else{
                while(journey!=NULL){
                    cout << journey->start_time << " " << journey->end_station << endl;
                    journey = journey->next;
                }
            }
        }

        // QUERY_JOURNEY <station_one> <start_time> <station_two>
        else if(isequal(input,"QUERY_JOURNEY")){
            char start_station[32], end_station[32];
            float start_time;
            cin >> start_station >> start_time >> end_station;

            Query_result* res = planner.query_journey(start_station, start_time, end_station);
            if(res == NULL){
                cout<<"ERROR: No journey found"<<endl;
            }
            else if(res->stop[0]==NULL_KEY){
                cout<<res->start_time<<endl;
            }
            else{
                cout << res->start_time <<" "<< res->stop <<" "<< res->next_time <<endl;
            }
        }
    }
}

int main(){
    Planner p;
    train_handler(p);
}