#include<iostream>
#include<string.h>
#include "dictionary.h"
#include "dictionary.cpp"
using namespace std;

#ifndef PLANNER_H
#define PLANNER_H


class Planner {
private:
  Dictionary starts;
  Entry ends[DICT_SIZE];
  char stations[DICT_SIZE][32];
  int N,scount;

public:
  //defining the constructor
  Planner(){
    scount=0;
    N=DICT_SIZE;
    for(int i=0;i<DICT_SIZE;i++){
      Entry a;
      ends[i]=a;
      strcpy(stations[i],"");
    }

  }

  //gives the dictionary containing departure stations and start times
  Dictionary getStarts(){
    return starts;
  }

  //returns the array containing arrival stations and end times
  Entry* getEnds(){
    return ends;
  }

  //adds a journey to the planner
  int addJourney(Entry e,int a,int index){
    bool found=false;
    for(int i=0;i<scount;i++){
      if(strcmp(stations[i],e.key)==0){
        found=true;
        break;
      }
    }
    if(!found){
      strcpy(stations[scount],e.key);
      scount++;
    }

    if(a==1){
      int place=starts.findFreeIndex(e.key);
      starts.put(e);
      return place;
    }
    else{
      strcpy(ends[index].key,e.key);
      ends[index].value=e.value;
      return 0;
    }
  }

  //shows a list of all the journeys added so far into the planner.
  void showJourneys(){
    for(int i=0;i<N;i++){
      if(starts.getDict(i)){
        cout<<ends[i].key<<" "<<ends[i].value<<endl;
      }

    }
  }

  //finds journeys leaving from a given station after a given start time.
  void queryStation(char station[],float start){
    bool found=false;
    for(int i=0;i<scount;i++){
      if(strcmp(stations[i],station)==0){
        found=true;
        break;
      }
    }
    if(!found){
      cout<<"This station does not exist, please re-check!"<<endl;
      return;
    }
    int* indices;
    indices=starts.getIndices(station,indices);
    if(indices[0]==1){
      cout<<"This station has 0 trains leaving it after "<<start<<endl;
      return;
    }

    cout<<"The following trains will leave station "<<station<<" after "<<start<<endl;
    found=false;
    for(int i=1;i<indices[0];i++){
      if(starts.getValue(indices[i])>=start){
        found=true;
        cout<<starts.getValue(indices[i])<<" "<<ends[indices[i]].key<<endl;
      }
    }

    if(!found){
      cout<<"This station has 0 trains leaving it after "<<start<<endl;
    }
    cout<<endl;
  }

  //finds the soonest journey from station 1 to station 2 after start time with at most 1 intermediate stop.
  void queryJourney(char station1[],char station2[],float start){
    bool found1=false,found2=false;
    for(int i=0;i<scount;i++){
      if(strcmp(stations[i],station1)==0){
        found1=true;
        break;
      }
    }
    for(int i=0;i<scount;i++){
      if(strcmp(stations[i],station2)==0){
        found2=true;
        break;
      }
    }

    if(!found1){
      cout<<"Station "<<station1<<" does not exist, please re-check!"<<endl;
      return;
    }
    if(!found2){
      cout<<"Station "<<station2<<" does not exist, please re-check!"<<endl;
      return;
    }

    int* indices;
    indices=starts.getIndices(station1,indices);
    if(indices[0]==1){
      cout<<"This station has 0 trains leaving it after "<<start<<endl;
      return;
    }
    int min=-1;
    int intermediatetime=-1;
    for (int i=1;i<indices[0];i++){
      if(starts.getValue(indices[i])>=start){
        if(strcmp(ends[indices[i]].key,station2)==0){
          if(min>-1){
            if(starts.getValue(indices[i])<starts.getValue(min)){
              min=indices[i];
            }
          }
          else{
            min=indices[i];
          }
        }

        else{
          //there's a journey from ends[i].key to station
          int* indices2;
          indices2=starts.getIndices(ends[indices[i]].key,indices2);
          for (int j=1;j<indices2[0];j++){
            if((starts.getValue(indices2[j])>ends[indices[i]].value)&&(strcmp(ends[indices2[j]].key,station2)==0)){
              //cout<<starts.getKey(indices[i])<<" "<<ends[indices[i]].key<<" "<<starts.getKey(indices2[j])<<" "<<ends[indices2[j]].key<<endl;
              if(min>-1){
                if(starts.getValue(indices[i])<starts.getValue(min)){
                  min=indices[i];
                  intermediatetime=starts.getValue(indices2[j]);
                }
              }
              else{
                min=indices[i];
                intermediatetime=starts.getValue(indices2[j]);
              }
            }
          }
        }
      }
    }

    if(min==-1){
      cout<<"No such trains are available."<<endl;
    }

    else if(intermediatetime<0){
      cout<<starts.getValue(min)<<endl;
    }
    else{
      cout<<starts.getValue(min)<<" "<<ends[min].key<<" "<<intermediatetime<<endl;
    }
  }

  //shows a list of all defined stations.
  void showStations(){
    for(int i=0;i<scount;i++){
      cout<<stations[i]<<endl;
    }
  }
};

#endif