#include <iostream>
#include "planner.h"
using namespace std;

Planner::Planner(){
    VAL = 64;
}

bool Planner::add_route(struct Path pt){
    //Adding a new route to our map
    return d.put(pt);
}

bool Planner::queryStation(Station s){
    //Checks if there are any train from the specified station
    int idx = d.get(s.station);
    if(idx == -1)return false;
    int l = d.A[idx].len;
    if(d.A[idx].p[l-1].stime < s.time)return false;
    for(int i = 0; i < l; i++){
        if(d.A[idx].p[i].stime < s.time)continue;
        cout <<d.A[idx].p[i].stime<<" "<<d.A[idx].p[i].dest<<endl;
    }
    return true;
}

bool Planner::queryJourney(struct Query q){
    int idx = d.get(q.St1);
    if(idx == -1)return false;
    bool dir=false;
    bool inter=false;
    float dt;
    int index = 0;
    float in_s;
    float in_l;
    //Checking for a direct route
    for(int i = 0; i < d.A[idx].len; i++){
        if((strcmp(q.St2,d.A[idx].p[i].dest)==0)&&(d.A[idx].p[i].stime > q.time)){
            dir = true;
            dt = d.A[idx].p[i].stime;
        }
    }
    //Checking for an intermediate route
    for(int i = 0; i < d.A[idx].len; i++){
        if(d.A[idx].p[i].stime < q.time)continue;
        int in = d.get(d.A[idx].p[i].dest);
        if(in == -1)continue;
        for(int j = 0; j < d.A[in].len; j++){
            if(d.A[idx].p[i].ftime > d.A[in].p[j].stime)continue;
            if(strcmp(q.St2,d.A[in].p[j].dest)==0){
                inter = true;
                index = i;
                in_s = d.A[idx].p[i].stime;
                in_l = d.A[in].p[j].stime;
            }
        }
    }
    //Comparing earliest route among direct and indirect journeys
    if((!(dir)) && (!(inter)))return false;
    if((dir) && (!(inter))){
        cout << dt <<endl;
        return true;
    }
    if((!(dir)) && (inter)){
        cout << in_s <<" "<< d.A[idx].p[index].dest <<" "<< in_l <<endl;
        return true;
    }
    if((dir) && (inter)){
        if(dt <= in_s){
            cout << dt <<endl;
            return true;
        }
        else{
            cout << in_s <<" "<< d.A[idx].p[index].dest <<" "<< in_l <<endl;
            return true;
        }
    }
    return false;
}

int main(){
    cout << "Welcome to the Queries office\n";
    cout <<"User commands are\n";
    cout << " ADD <station_one> <start_time> <station_two> <finish_time>\n";
    cout << " QUERY_STATION <station_one> <start_time>\n";
    cout << " QUERY_JOURNEY <station_one> <start_time> <station_two>\n";
    cout << " EXIT\n\n";
    Planner plan;
    //Writing the testing part
    for(int i = 1; i > 0; i++){
        char input[32];
        cin>>input;
        if(strcmp(input,"EXIT") == 0)break;
        if(strcmp(input,"ADD") == 0){
            char inp1[32];
            char inp2[32];
            float inpn1;
            float inpn2;
            cin >> inp1;
            cin >> inpn1;
            cin >> inp2;
            cin >> inpn2;
            Path pth;
            strcpy(pth.start,inp1);
            strcpy(pth.dest,inp2);
            pth.stime = inpn1;
            pth.ftime = inpn2;
            if(!plan.add_route(pth)){
                cout <<" Could not add the specified path MAX LIMIT REACHED\n";
            }
        }
        else if(strcmp(input,"QUERY_STATION") == 0){
            char inp[32];
            float inpn;
            cin >> inp;
            cin >> inpn;
            Station st;
            strcpy(st.station,inp);
            st.time = inpn;
            if(!plan.queryStation(st)){
                cout << " No trains with required specifications are availabel\n";
            }
        }
        else if(strcmp(input,"QUERY_JOURNEY") == 0){
            char inp1[32];
            char inp2[32];
            float inpn;
            cin >> inp1;
            cin >> inpn;
            cin >> inp2;
            Query qt;
            strcpy(qt.St1,inp1);
            strcpy(qt.St2,inp2);
            qt.time = inpn;
            if(!plan.queryJourney(qt)){
                cout<<" No trains are availabele for your journey\n";
            }
        }
    } 
    return 0;
}