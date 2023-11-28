#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <fstream>
#include <cmath>
#include "planner.h"
using namespace std;
int in=0;

void dictionaryHandler(Planner &planner)
{   cout << "You can use the following commands:" << endl;
    cout << "ADD <station_one> <start_time> <station_two> <finish_time>" << endl;      //commands clarification
    cout << "QUERY_STATION <station_one> <start_time>" << endl;
     cout << "EXIT" << endl;
    for (int i = 0; i >= 0; i++)  //for infinite many times of input
    {
        char input[32];

        
        cout << ">>> ";

        cin >> input;

        if (strcmp(input, "EXIT") == 0)  //code if input command is exit
        {
            break;
        }

        else if (strcmp(input, "ADD") == 0)   //code if input command is add
        {
            char addinput1[32];
            cin >> addinput1;
            float addinput2;
            cin >> addinput2;
            char addinput3[32];
            cin >> addinput3;
            float addinput4;
            cin >> addinput4;
            
            strcpy(planner.A[in].station1, addinput1);
            planner.A[in].start_time = addinput2;
            strcpy(planner.A[in].station2, addinput3);
            planner.A[in].finish_time = addinput4;
            in++;
            cout << "Train route added" << endl;
        }

        else if (strcmp(input, "QUERY_STATION") == 0)   
        {
            char qsinput1[32];
            cin >> qsinput1;
            float qsinput2;
            cin >> qsinput2;

            int count=0;

            for (i=0;i<64;i++){
                
                if(planner.A[i].start_time >= qsinput2 && (strcmp((planner.A[i].station1),qsinput1) == 0)){
                    cout<<planner.A[i].start_time<<planner.A[i].station2<<endl;
                    count++;
                }
            }

            if(count == 0){cout<<"error";}
        }

        else if (strcmp(input,"QUERY_JOURNEY") == 0) //code if input command query journey
        {
            char qjinput1[32];
            cin>> qjinput1;
            float qjinput2;
            cin>> qjinput2;
            char qjinput3[32];
            cin>> qjinput3;

            float t = 2400;
            float tnos = 2400;
            int count1=0,count2=0,count3=0,count4=0;

            Journey *route1 = new Journey[64];
            Journey *route2 = new Journey[64];
            Journey *route3 = new Journey[64];
            Journey route4 ;
            
            for(int i=0;i<64;i++){
                if((strcmp(planner.A[i].station1,qjinput1)==0)&&(planner.A[i].start_time>=qjinput2)){
                    route1.[count1]=planner.A[i];
                    count1++;
                }
                if(strcmp(planner.A[i].station2,qjinput3)==0){
                    route2[count2]=planner.A[i];
                    count2++;
                }
            }
            for(int i=0;i<count1;i++){
                for(int j=0;j<count2;j++){
                    if((route1[i].station2==route2[j].station1)&&(!(route1[i].station1==route2[j].station1))&&(route1[i].finish_time<=route2[j].start_time)){
                        route3[count4].start_time=route1[i].start_time;
                        route3[count4].finish_time=route2[j].start_time;
                        strcpy(route3[count4].station1,route2[j].station1);
                        strcpy(route3[count4].station2,route2[j].station2);
                        count4++;
                    }
                    if(route1[i].station1==route2[j].station1){
                        route4 = route1[i];
                    }
                }
            } 
            Journey pos = route4;
            for(int i=0;i<count4;i++){
                if(route3[i].start_time<=pos.start_time){
                    pos=route3[i];
                }
            }
            if(strcmp(pos.station1,route4.station1)==0){
                cout<<route4.start_time<<endl;
                count3++;
            }
            else{
                cout<<pos.start_time<<" "<<pos.station1<<" "<<pos.finish_time<<endl;
                count3++;
            }
            if(count3==0)cout<<"ERROR"<<endl;                      
        }
    }
}

Planner ::Planner()
{
    N = 64;
    A = new Journey[64];
    for (int i = 0; i < DICT_SIZE; i++)
    {
        A[i].start_time = 0;
        A[i].finish_time = 0;
    }
}

int Planner ::hashValue(char station1[])
{
    double B = (sqrt(5.00) - 1.00) / 2.00;
    int x = 33;
    int poly = 0;
    int s = 0;
    while (station1[s] != '\0')
    {
        s++;
    }

    for (int i = s - 1; i >= 0; i--)
    {
        int asval = station1[i];
        poly = (poly * x + asval) % N;
    }
    double C = poly * B;
    int D = C;
    int hv = N * (C - D);
    return hv;
}

int Planner ::findFreeIndex(char station1[])
{
    int E = hashValue(station1);
    bool free = true;
    for (int i = 0; i < N; i++)
    {
        if (A[i].value == 0 || A[i].value == -1)
            free = false;
        break;      // all previous functions in part1 problem are defined again
    }
    if (free == true)
        return -1;
    if (A[E].value != 0 || A[E].value != -1)
    {
        E = ((E + 1) % N);
    }
    return E;
}

void Planner ::put(struct Journey r)
{
    char *c = r.station1;
    int a = findFreeIndex(c);
    if (a == -1){
        cout << "sorry no more space in dictionary" << endl;}
    else{   
        strcpy(A[a].station1, c);
        A[a].value = r.value;
        strcpy(A[a].station2, r.station2);
        A[a].start_time = r.start_time;
        A[a].finish_time = r.finish_time;}
}

struct Journey *Planner ::get(char station1[])
{
    char *F = station1;
    int G = hashValue(F);
    for (int i = G; i < N; i++)
    {
        if (strcmp(A[i].station1, F) == 0)
        {
            return &A[i];
        }
    }
    for (int i = 0; i < G; i++)
    {
        if (strcmp(A[i].station1, F) == 0)
        {
            return &A[i];
        }
    }

    return NULL;
}

int main()
{
    Planner planner;
    dictionaryHandler(planner);
    return 0;
}