#include<math.h>
#include<iostream>
#include"planner.h"
#define EPSILON 1e-6F

void Station::grow(){ //grow queue size
    Journey** tmp=jq;
    jq= new Journey*[2*size];
    for(int i=0;i<tail;i++) jq[i]=tmp[i];
    size=2*size;
    delete[] tmp;
    return;
}

int Station::find(float time){//finds starting index in array departing on or after time
    //*
    for (int i=0;i<tail;i++){
        if (time<=jq[i]->departure+EPSILON) return i;
    }
    //*/
    return -1;
    //implement this with binary search to make everything more efficient
}
int Station::find(float time , char stn[]){ //finds starting index in array with given stn as destination and departing on or after time

    int first = find(time);
    if (first==-1) return -1;
//zooming through times we are not interested in
    for (int i=first;i<tail;i++){
        if (strcmp(stn,jq[i]->destination)==0)
            return i;
    }
    return -1;
}

int Station::insert(Journey* jrny){ //insert a journey in the queue
    if (tail==size) grow();
    int i=find(jrny->departure);
    if (i==-1) i=tail; //insert at end
    for(int j=tail-1; j >= i; j--){ //shift elements after insertion pt
        jq[j+1]=jq[j];
    }
    jq[i]=jrny;
    tail++;
    return 0;
}

void Station::print_all(float time){ //prints all journeys departing on or after time -- used for QUERY_STATION
    int i = find(time); if (i==-1) {cout<<"ERROR"<<endl;return;}
    for (;i<tail;i++){
        cout<<jq[i]->departure<<' '<<jq[i]->destination<<endl;
    }
}

int Planner::hash(char stationname[]){
    /* old , part 1 code
    unsigned int code= 0;
    for(int i=0; stationname[i]!='\0';i++){ //horner's rule iteratively in reverse order
        code=(code*PRIME_POLY)%PRIME_MOD;//using mode to 1- keep number small for calc frac part, 2- no overflows
        code+=stationname[i];    
    }    
    float garb;//
    int hash = (modf(code*PHINV,&garb))*DICT_SIZE;
    //*/
    //*

    //basically using mod properties to expand the mod to each term to prevent overflow or precision loss
    float garb;  // to direct the `int` parts of upcoming modf s  
    double value=0;
    double multiplier=PHINV; //fib hashing
    for (int i=0; stationname[i]!='\0';i++){
        value+=modf(stationname[i]*multiplier,&garb);
        multiplier= modf(multiplier*PRIME_POLY,&garb);
    }
    int hash = DICT_SIZE*modf(value,&garb);
    //*/
    //cout<<stationname<<": "<<hash<<'\n';
    return hash;
}

int Planner::Find(char station[]){ //find dictionary entry corresponding to station
    int hashval= hash(station);
    for (int i=0;i<DICT_SIZE ;i++){
        if (tt[(hashval+i) %DICT_SIZE]==NULL){
            return -1; //no need to search further
        }
        if ((strcmp(tt[(hashval+i) %DICT_SIZE]->stname,station)==0))//free
            return (hashval+i)%DICT_SIZE;
    }
    return -1;
}

int Planner::FindCreate(char station[]){
    int hashval= hash(station);
    //cout<<"Find Create Called\n";
    for (int i=0;i<DICT_SIZE ;i++){//find corresponsing dictionary entry to make a new station 
        if (tt[(hashval+i) %DICT_SIZE]==NULL){
            tt[(hashval+i) %DICT_SIZE] = new Station(station);
            return (hashval+i)%DICT_SIZE;
        }
    }
    return -1;
}

void Planner::Route(char* from, float starttime, char* to){ //this generates the earliest starting route -- QUERY_JOURNEY
    int ind= Find(from);
    if (ind==-1) {cout<<"ERROR";return ;}

    int jst= tt[ind]->find(starttime);
    if (jst==-1) {cout<<"ERROR";return ;}

    int tail = tt[ind]->gettail();
    for(;jst<tail;jst++){
        if (strcmp(tt[ind]->jq[jst]->destination,to)==0){//direct if found
            cout<<tt[ind]->jq[jst]->departure;
            return;
        }
        else{ //for every journey, see if this intermediate destination has a direct route to the final destination
            int midind = Find(tt[ind]->jq[jst]->destination);
            if (midind==-1) continue;

            int secjr = tt[midind]->find(tt[ind]->jq[jst]->arrival,to);
            if (secjr==-1) continue;

            cout<< tt[ind]->jq[jst]->departure<<' '<< tt[ind]->jq[jst]->destination <<' '<< tt[midind]->jq[secjr]->departure; 
            return;
        }
    }

    cout<<"ERROR";
    return;    
}


void Planner::Query(){//the interface
    while (true){
        char mot[MAX_NAME];

        cin>>mot;
        if (strcmp("EXIT",mot)==0){
            return ;
        }
        else if (strcmp("ADD",mot)==0){
            char src_[MAX_NAME], dest_[MAX_NAME] ;
            float dep_,arr_;
            cin>> src_>>dep_>>dest_>>arr_;

            Journey* nj= new Journey(src_,dep_,dest_,arr_);

            int ind = Find(src_);
            if (ind==-1)   tt[FindCreate(src_)]->insert(nj);
            else tt[ind]->insert(nj);
        }
        else if (strcmp("QUERY_JOURNEY",mot)==0){
            char src_[MAX_NAME], dest_[MAX_NAME];
            float dep_;
            cin>>src_>>dep_>>dest_;

            Route(src_,dep_,dest_);
            cout<<endl;
        }
        else if (strcmp("QUERY_STATION",mot)==0){
            char stn[MAX_NAME];
            float time;
            cin>>stn>>time;

            int ind=Find(stn);
            if (ind==-1) {cout<<"ERROR"<<endl; continue;}
            
            tt[ind]->print_all(time);
        }
    }
}

