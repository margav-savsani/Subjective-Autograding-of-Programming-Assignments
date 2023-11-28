#include"planner.h"
#include<iostream>
#include <bits/stdc++.h>
using namespace std;

void Planner::add(struct Entry query){
    dictionary.put(query);//since we have already created insert function in dictionary.cpp
}

void Planner::station(char station_one[],float start_time){

    Entry* store ;//store stores all the entries whose start station is station one
    
    store = dictionary.getarray(station_one);//all the entries whose key is station_one gets stored in this
    int count = 0;//counter for checking whether loop is entered
    for(int i = 0; strcmp(store[i].key,"$")!=0;i++){//iterate through store
        if(store[i].value >= start_time){//if the start time of this train from station 1 is greater than user provided start time
            cout<<store[i].value<<" "<<store[i].station2<<endl;
            count =1;
        }
    }
    if(count == 0) cout << "ERROR\n";//if entry is not present
}

void Planner::journey(char station_one[],float start_time,char station_two[]){//first called in QUERY_JOURNEY

    Entry* store ;//store stores all the entries whose start station is station one

    store = dictionary.getarray(station_one);
   
    

    //call base with same parameters
    Entry* final;
    Entry* final_Direct;
    float final_timeDirect = 9999,final_time=9999;;
    final_Direct = base(station_one,start_time,station_two);
    if(final_Direct != NULL){
        final_timeDirect = final_Direct->value;//time of leaving from intermediate station
    }

    
    float start_timeIndirect = 9999;//start time from station1
    char intermediate_station[32];
    
    //loop over--call base in every iteration using diff parameters that is intermediate station
    int i=0 ;
    for(i = 0; strcmp(store[i].key,"$")!=0;i++){
        
        if(store[i].value >= start_time ){//if the start time of this train from station 1 is greater than user provided start time
            final = base(store[i].station2,store[i].reachtime,station_two);
            if(final != NULL){//copy the parameters recieved
                final_time = final->value;
                start_timeIndirect = store[i].value;
                strcpy(intermediate_station,store[i].station2);
                break;
            }
            
        }
    }

    if(final_time == 9999 && final_timeDirect == 9999)//if initial values are unchanged
        cout<<"No Such Train available!"<<endl;
    else if(start_timeIndirect<final_timeDirect)     //comparison between direct and indirect start time
        cout<<start_timeIndirect<<" "<<intermediate_station<<" "<<final_time<<endl;
    else    
        cout<<final_timeDirect<<endl; 
}

    


Entry* Planner::base(char station_one[],float start_time,char destinatiion[]){//next called in QUERY_JOURNEY , and then journey is called from inside with base, reachtime and destination
    Entry* store ;//store stores all the entries whose start station is station one

    store = dictionary.getarray(station_one);
    int i;
    for(int i = 0; strcmp(store[i].key,"$")!=0;i++){
        if(store[i].value >= start_time && strcmp(store[i].station2,destinatiion)==0){//if the start time of this train from station 1 is greater than user provided start time
            return &store[i];//returns reference of this entry
        }
    }
    return NULL;//else return a null pointer signifying entry not found
}

 




