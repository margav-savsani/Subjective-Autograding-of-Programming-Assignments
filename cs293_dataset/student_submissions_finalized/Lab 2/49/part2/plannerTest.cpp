#include "planner.cpp"
#include <iostream>
using namespace std;
// type out commands as following
//ADD
//station one , time of start, station two, time of end
//QUERY_STATION
//station, time
//QUERY_JOURNEY
//station one, time, station two


void travelplanner(Planner &plan){
    for(int i=0;i>=0;i++){
        char input[32];
        cout << ">>> " ;
        cin>>input;
        if(strcmp(input,"EXIT") == 0){
            break;
        }
        if(strcmp(input,"ADD")==0){
            Station s1,s2;
            float t1,t2;
            cin>>s1.name>>t1>>s2.name>>t2;
            bool addition = plan.add(s1,t1,s2,t2);            
        }
        if(strcmp(input,"QUERY_STATION")==0){
            Station s;
            float t;
            cin>>s.name>>t;
            plan.query_station(s,t);
        }
        if(strcmp(input,"QUERY_JOURNEY")==0){
            Station s1,s2;
            float t;
            cin>>s1.name>>t>>s2.name;
            plan.query_journey(s1,t,s2);
        }
    }
}

int main(){
    Planner plan;
    cout<<"Welcome to the journey planner"<<endl;
    travelplanner(plan);
}
