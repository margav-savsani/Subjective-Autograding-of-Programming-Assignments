#include <iostream>
using namespace std;
#include "planner.cpp"

int main() {
    Planner planner;
    while(true) {
        cout << "   Enter command :\n";
        char task[50];
        cin>>task;
        if(strcmp(task,"ADD") == 0) {
            Query query;
            cin>>query.stat1>>query.time1>>query.stat2>>query.time2;
            if(planner.add(&query))
                cout<<"Added successfully\n";
            else
                cout<<"Adding failed\n";
        }
        else if(strcmp(task,"QUERY_STATION") == 0) {
            Query query;
            cin>>query.stat1>>query.time1;
            if(!planner.station(&query))
                cout<<"SORRY! No journeys found\n";
        }
        else if(strcmp(task,"QUERY_JOURNEY") == 0) {
            Query query;
            cin>>query.stat1>>query.time1>>query.stat2;
            if(!planner.journey(&query))
                cout<<"Sorry! No journeys found\n";
        }
        else if(strcmp(task,"QUIT") == 0 || strcmp(task,"EXIT") == 0)
            break;
        cout << "\n";
    }
}