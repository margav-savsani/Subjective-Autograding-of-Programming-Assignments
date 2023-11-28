#include<iostream>
#include<string.h>
#include"planner.h"
using namespace std;

void planninghandler(Planner &planner){
    for(int i=0;i>=0;i++){
        char input[32];
        cout << ">>> " ;
        cin>>input;
        if(strcmp(input,"EXIT") == 0){
          break;
        }

        // ADD
        if(strcmp(input,"ADD") == 0){
            char station1[32];
            cin>>station1;
            float start;
            cin>>start;            
            char station2[32];
            cin>>station2;
            float end;
            cin>>end;
            planner.add_journey(station1,start,station2,end);
        }

        //QUERY_STATION
        if(strcmp(input,"QUERY_STATION") == 0){
            char station[32];
            cin>>station;
            float start;
            cin>>start;
            if(planner.index(station)  != planner.num_stations()){
                Query Q;            
                Q = planner.query_station(station,start);
                if(Q.n == 0) {
                cout<<"Sorry! no trains are available during that time"<<endl;
                }
                else{
                    for(int i=0;i<Q.n;i++){
                    cout<<Q.E[i].start<<" "<<Q.E[i].key<<endl;
                    }
                }  
            }     
            else{
                cout<<"Enter a valid station name"<<endl;
            }                              
        }

        //QUERY_JOURNEY
        if(strcmp(input,"QUERY_JOURNEY") == 0){
            char s1[32];
            cin>>s1;
            float start;
            cin>>start;
            char s2[32];
            cin>>s2;                   
            planner.query_journey(s1,start,s2);
        }
    }
}

void interactive(){
    cout<<"Welcome! \n";
    cout<<"";
    Planner planner;
    planninghandler(planner);
}

int main(){
    interactive();
}