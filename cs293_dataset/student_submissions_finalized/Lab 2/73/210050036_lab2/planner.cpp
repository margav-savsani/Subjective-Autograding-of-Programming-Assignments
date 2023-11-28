#include "planner.h"
#include <iostream>
#include <cmath>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
using namespace std;


int main()
{
    Planner *plan;
    plan =new Planner;
    cout<<"lets me help you"<<endl;//instructions
    cout<<"press EXIT to exit the loop\npress ADD and give <station_one> <start_time> <station_two> <finish_time> to add\n";
    cout<<"press QUERY_STATION to find the trains from station after given time give <station_one> <start_time>\n";
    cout<<"press QUERY_JOURNEY and give <station_one> <start_time> <station_two> it will give the train starting in lowest possible time\n";
    while(true)
    {
        string input;
        cout<<">>> ";
        cin>>input;     //taking input 
        if(input.compare("EXIT")==0)
        {
            break;
        }               
        if (input.compare("ADD")==0)        //add the new train
        {
            string inputstat1,inputstat2;
            float time1,time2;
            cin>>inputstat1;
            cin>>time1;
            cin>>inputstat2;
            cin>>time2;
            int hashvalue=plan->hashValue(inputstat1);
            int freeIndex=plan->FindFreeIndex(inputstat1);
            cout<<"Hash Value: "<<hashvalue<<endl;
            cout<<"Free Index: "<<freeIndex<<endl;
            if (freeIndex!=-1)
            {
                plan->addtrain(inputstat1,time1,inputstat2,time2);
                cout<<"Added Successfully"<<endl;
            }
            else
            {
                cout<<"List is full"<<endl;
            }
        }
        if (input.compare("QUERY_STATION")==0)  //QUERY STATION
        {
            string station;
            float time;
            cin>>station;
            cin>>time;
            bool k=plan->QueryStation(station,time);
            if(!k)
            {
                cout<<"there is no train/wrong station name"<<endl;
            }
        }
        if (input.compare("QUERY_JOURNEY")==0)  //QUERY JOURNEY
        {
            string stat1,stat2;
            float time;
            cin>>stat1;
            cin>>time;
            cin>>stat2;
            bool k=plan->QueryJourney(stat1,time,stat2);
            if (!k)
                cout<<"There is no train/wrong station name"<<endl;
        }
    }
}       //by saran 210050036