#include<iostream>
#include"planner.cpp"
using namespace std;

int main(){
    char ADD[32] = "ADD";
    char QUERY_STATION[32] = "QUERY_STATION";
    char QUERY_JOURNEY[32] = "QUERY_JOURNEY";
    char EXIT[32] = "EXIT";

    Planner p;

    char inpt[32];
    cin >> inpt;

    while(strcmp(inpt, EXIT) != 0){
        if(strcmp(inpt, ADD) == 0){
            char st1[32];
            float t1;
            char st2[32];
            float t2;

            cin >> st1 >> t1 >> st2 >> t2;

            p.add(st1, t1, st2, t2);
        }
        else if(strcmp(inpt, QUERY_STATION) == 0){
            char st[32];
            float t;

            cin >> st >> t;

            p.query_station(st, t);
        }
        else if(strcmp(inpt, QUERY_JOURNEY) == 0){
            char st1[32];
            float t;
            char st2[32];

            cin >> st1 >> t >> st2;

            p.query_journey(st1, t, st2);
        }

        cin >> inpt;
    }

}