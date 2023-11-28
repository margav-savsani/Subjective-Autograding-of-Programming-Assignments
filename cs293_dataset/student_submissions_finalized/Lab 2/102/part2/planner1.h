

#ifndef PLANNER_H
#define PLANNER_H



#include<iostream>
#include<string>
#include<cmath>
#include <cstring>
#include"assert.h"
#include"planner.h"
using namespace std;

//Assuming that we are working on set of 64 trains .
//Can be changed later+accordingly...

const int DICT_SIZE = 64;
int current_trains=0;

//A variable current_trains that keep tracks of current trains running

// struct Station holding name of station.

struct Station {
  // define suitable fields here
  public:
  char station_name[32];
};

// struct train : keeping track of where and when train starting and reaching
// when and where.

struct train {
  public:
  Station start_station;
  float start_time;
  Station end_station;
  float end_time; 
  train(){
    start_station.station_name[0]='N';
    start_time=-1;
  }

  void add_station(Station S1 , float T1 , Station S2,float T2);

};


// struct Query keeping query functions declaration  

struct Query{
  // define suitable fields here
  public:
  void query_Station(Station S1 , float T1);
  void query_Journey(Station S1 , float T1 , Station S2);
};

// making array for storing trains data .

train all_trains[DICT_SIZE];

// function hashValue() return key/index for key

int hashValue(char key[]){
    int x=33;  // this is for polynomial
    int sum_key=0; //getting sum of it 
    for(int i=0 ; i<31 && key[i]!='\0' ; i++){
        
        sum_key+=((int)key[i]-65)*pow(x,i);
    }
    double keyA;
    double A= (sqrt(5)-1)/2;
    keyA=(sum_key*A);
    keyA=keyA-(int)keyA;
    double keyR=floor(keyA*DICT_SIZE);
    assert(keyR<DICT_SIZE);
    return keyR;
}

// function findFreeIndex() doing linear probing

int findFreeIndex(char key[]){
    int keyC=hashValue(key);
    int i=0;
    while(i<DICT_SIZE){
        if(all_trains[keyC%DICT_SIZE].start_time==-1){
            return keyC%DICT_SIZE;
        }
        keyC++;
        i++;
    }

    return -1;
}

// definition of add_station : fills up table of trains at appropriate index

void train::add_station(Station S1 , float T1 , Station S2,float T2){
    int index=findFreeIndex(S1.station_name);
    if(index==-1){return;}
    all_trains[index].start_station=S1;
    all_trains[index].start_time=T1;
    all_trains[index].end_station=S2;
    all_trains[index].end_time=T2;
    current_trains++;
}

// function query_Station returns all train from that station , after 
// specified time 


void Query::query_Station(Station S1 , float T1){
    bool tt=true;
    for(int i=0; i<64; i++){
        int check;
        if(all_trains[i].start_time!=-1){
            check=strcmp(all_trains[i].start_station.station_name,S1.station_name);
        }
        else continue;
        if( check==0 && all_trains[i].start_time>=T1){
            cout<<all_trains[i].start_station.station_name<<" ";
            cout<<all_trains[i].start_time<<" ";
            cout<<all_trains[i].end_station.station_name<<" ";
            cout<<all_trains[i].end_time<<endl;
            tt=false;
        }
    }
    if(tt){
        cout<<"No trains are there..."<<endl;
    }
    return;
}

// function query_Journey returns all trains between two stations , 
// and also total time taken ... 
// keeps track so that departure of a train is not before arrival of
// previous train

void Query::query_Journey(Station S1 , float T1 , Station S2){
    bool tt=false;
    for(int i=0 ; i<64 ; i++){
        int check,check1;
        //all_trains[i].end_station.station_name==S2.station_name 
        if(all_trains[i].start_time!=-1){
            check=strcmp(all_trains[i].start_station.station_name,S1.station_name);
            check1=strcmp(all_trains[i].end_station.station_name,S2.station_name);
        }
        else continue;
        if(check==0 && check1==0 && all_trains[i].start_time>=T1 ){
            cout<<all_trains[i].start_station.station_name<<" ";
            cout<<all_trains[i].start_time<<endl; 
            tt=true;           
        }

    }
    
    //if train not found for non stop journey//
    //have to keep check of time 
    if(tt){return;}
    for(int i=0 ; i<64 ; i++){
        int check,check1,check2;
        if(all_trains[i].start_time!=-1){
            check=strcmp(all_trains[i].end_station.station_name,S2.station_name);
        }   
        else continue;
        if(check==0  ){
            for(int j=0;j<64;j++){
                check1=strcmp(all_trains[j].start_station.station_name,S1.station_name);
                check2=strcmp(all_trains[j].end_station.station_name,all_trains[i].start_station.station_name);
                if(check1==0 && check2==0 && all_trains[j].end_time<=all_trains[i].start_time && all_trains[j].start_time>=T1){
                    cout<<all_trains[j].start_station.station_name<<" ";
                    cout<<all_trains[j].start_time<<"-";
                    cout<<all_trains[j].end_time<<" ";
                    cout<<all_trains[j].end_station.station_name<<" ";
                    cout<<all_trains[i].start_time<<"-";
                    cout<<all_trains[i].end_time<<" ";
                    cout<<all_trains[i].end_station.station_name<<" ";
                    cout<<"Total time taken : "<<all_trains[i].end_time-all_trains[j].start_time<<endl;
                    tt=true;
                }
            }
        }
    }
    if(!tt){
        cout<<"No trains are there..."<<endl;
    }
    
}

#endif