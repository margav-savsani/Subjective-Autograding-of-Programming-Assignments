#include "planner.h"
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
using namespace std;

void plannerHandler(planner& P){
    while(true){
        char input[32];
        //cout << ">>>> "; 
        cin >> input;
        if(strcmp(input, "QUIT") == 0) break;
        else if(strcmp(input, "ADD") == 0){
            char start[32], end[32];
            float i_time, f_time;
            cin >> start >> i_time >> end >> f_time;
            P.add_journey(start, end, i_time, f_time);
        }
        else if(strcmp(input, "QUERY_STATION") == 0){
            char start[32];
            float time;
            cin >> start >> time;
            P.q_station(start, time);
        }
        else if(strcmp(input, "QUERY_JOURNEY") == 0){
            char start[32], end[32];
            float time;
            cin >> start >> time >> end;
            P.q_journey(start, end, time);
        }
        //P.display();
    }
}
int main(){
    //cout << "Welcome to the rail planner" << endl;
    planner P;
    plannerHandler(P);
}