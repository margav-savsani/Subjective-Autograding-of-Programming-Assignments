#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "planner.h"

using namespace std;

void UI(Planner p){
    while(true){
        char cmd[32];
        cin >> cmd;

        Query q;
        if(strcmp(cmd, "EXIT") == 0) break;

        else if(strcmp(cmd, "ADD") == 0){
            char s1[32], s2[32];
            float stime, etime;
            cin >> s1 >> stime >> s2 >> etime;
            Journey j; strcpy(j.start.name, s1); strcpy(j.end.name, s2); j.stime = stime; j.etime = etime;
            p.insert(j);
        }

        else if(strcmp(cmd, "QUERY_STATION") == 0){
            cin >> q.s1.name >> q.stime;
            p.qStation(q);
        }

        else if(strcmp(cmd, "QUERY_JOURNEY") == 0){
            cin >> q.s1.name >> q.stime >> q.s2.name;
            p.qJourney(q);
        }
    }
}

int main(){
    Planner p;
    UI(p);
}