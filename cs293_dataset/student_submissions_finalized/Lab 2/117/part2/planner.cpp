#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.h"
#include <cmath>
#include<string>
using namespace std;
Planner::Planner(){}

void Planner::add(char startStation[], float startTime, char Endstation[], float endTime){// adding an entry
      struct Entry e;
      strcpy(e.key,startStation);
      e.value = startTime;
      strcpy(e.endStation , Endstation);
      e.endTime = endTime;
      planner.put(e);
    }

void Planner::station(char startStation[], float startTime){// gets all entries with starting station as our station and then
      struct Entry* array = planner.getAll(startStation);// prints those with start time greater than given. If none is printed, error msg is shown
      int count = 0;// number of prints
      for(int i = 0; strcmp(array[i].key,"!")!= 0;i++){
        if(array[i].value>=startTime){
          cout << array[i].value<<" "<<array[i].endStation<<"\n";
          count ++;
        }
      }
      if(count == 0) cout << "No such journey\n";//error
    }


float Planner::journeyDirect(char startStation[], float startTime, char endstation[]){
      struct Entry* array = planner.getAll(startStation);
      float ans=9999999;//placeholder value
      int i;
      for(i = 0; strcmp(array[i].key,"!")!= 0;i++){// for first value
        if(strcmp(array[i].key,startStation)==0 && strcmp(array[i].endStation,endstation) == 0 && (array[i].value>startTime)){
          ans = array[i].value;
          break;
        }
      }
      for(;strcmp(array[i].key,"!")!= 0; i++){// for all values after the first, reduces time but not complexity
        if(strcmp(array[i].key,startStation)==0 && strcmp(array[i].endStation,endstation)==0 && ans> array[i].value){
          ans = array[i].value;
        }
      }
      return ans;//9999999 indicates no direct journey, otherwise lowest time of starting journey is given
    }

void Planner::journeyComplete(char StartStation[], float startTime, char EndStation[]){
      struct Entry* ans;// stores the first journey
      struct Entry* array = planner.getAll(StartStation);
      
      float ans1 = journeyDirect(StartStation, startTime, EndStation);// direct journey,ans1 stores starttime
      float midtime=9999999;// stores startime of second journey
    
      for(int i = 0; strcmp(array[i].key,"!")!=0;i++){// checking for all journeys with intermediate stations
        if(ans1<= array[i].value || array[i].value <= startTime) continue;
        float midtime1 = journeyDirect(array[i].endStation,array[i].endTime,EndStation);
        if(midtime1 != 9999999){ 
          ans1 = array[i].value;
          ans = &array[i];
          midtime = midtime1;
        }
      }
      

      if(ans1 == 9999999){
        cout<<"No such Journey is Possible\n";
        return;
      }
      else if(ans == NULL){
        cout << ans1 << endl;
        return;
      }
      else{
        cout << ans->value << " " << ans->endStation << " " << midtime << "\n";
        return;
      }
    }
