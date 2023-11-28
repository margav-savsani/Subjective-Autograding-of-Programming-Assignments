#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.cpp"
#include <cmath>
#include<string>
using namespace std;

void queries(){
    Planner planner;
    while(true){
        char input[32];
        cin >> input;
        if(strcmp(input, "EXIT") == 0) break;//  should stop at break
        if(strcmp(input, "ADD") == 0){// calls add function with the respective parameters taken as input
            char station1[32], station2[32];
            float start, end;
            cin >> station1>> start>> station2>> end;
            planner.add(station1, start, station2, end);

        }
        if(strcmp(input, "QUERY_STATION") == 0){// calls the station function with the respective parameters taken as input
            char station[32];
            float start;
            cin >> station >> start;
            planner.station(station, start);
                 
        }
        if(strcmp(input, "QUERY_JOURNEY") == 0){// calls journey complete with the respective parameters taken as input
            char station1[32], station2[32];
            float start;
            cin >> station1 >> start >> station2;
            planner.journeyComplete(station1, start, station2);
        }
    }
}

int main(int argc, char* argv[]){
    /*queries();*/
    queries();
}