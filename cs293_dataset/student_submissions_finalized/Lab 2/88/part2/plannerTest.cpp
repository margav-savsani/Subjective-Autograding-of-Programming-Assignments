#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.h"
using namespace std;

/*

In interactive mode you can give commands `
  EXIT
  ADD <station_one> <start_time> <station_two> <finish_time>
  QUERY_STATION <station_one> <start_time>
  QUERY_JOURNEY <station_one> <start_time> <station_two>

*/

void plannerHandler(Planner P){
    bool num = 1;
    while(num == 1){ // takes user input until EXIT is entered
        char input[30];
        cin >> input;
        num = P.HandleQuery(input);
    }
}

int main(){
    Planner P;
    plannerHandler(P);
}