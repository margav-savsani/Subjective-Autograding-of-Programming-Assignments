#include<iostream>
#include"planner.h"
#include<cstring>
#include"Dictionary.h"
#include<fstream>
using namespace std;
int main(){
    // char t[30];
    // cin>>t;
    // char h[30];
    // cin>>h;
    // char c[30];
    // char ci[30];
    // strcpy(c,t);
    // strcpy(ci,h);
    // Planner p;
    // float f,o;
    // cin>>f;
    // cin>>o;
    // p.add(c,f,ci,f);
    // p.add(ci,o,c,o);
    // float k;
    // cin>>k;
    // p.query_station(c,k);
    // p.query_journey(c,k,c);




     Planner planner;
  
        ifstream fin;
        char word[50];
        string filename;
        filename="input1.in";
        fin.open(filename.c_str());
        while(fin>>word){
            if(!strcmp(word,"ADD")){
            float starttime,endtime;
            char station1[30];
            char station2[30];
            fin>>word;
            strcpy(station1,word);
            fin>>word;
            starttime=stof(word);
            fin>>word;
            strcpy(station2,word);
            fin>>word;
            endtime=stof(word);
            planner.add(station1,starttime,station2,endtime);
            }
            else if(!strcmp(word,"QUERY_STATION")){
                char station[30]; 
                fin>>word;
                strcpy(station,word);
                fin>>word;
                float time=stof(word);
                planner.query_station(station,time);
            }
            else if(!strcmp(word,"QUERY_JOURNEY")){
                char station1[30];
                char station2[30];
                fin>>word;
                strcpy(station1,word);
                fin>>word;
                float starttime=stof(word);
                fin>>word;
                strcpy(station2,word);
                planner.query_journey(station1,starttime,station2);
            }
            else if(!strcmp(word,"EXIT")){
                break;}
            }
}