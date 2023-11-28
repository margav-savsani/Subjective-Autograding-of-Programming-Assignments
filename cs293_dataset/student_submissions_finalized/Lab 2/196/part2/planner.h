//Copyright: Yuvraj Singh 210050172
#ifndef PLANNER_H
#define PLANNER_H
#include "dict.h"
#include <iostream>
#include<string.h>
using namespace std;

Dictionary Railway;             //Global Dictionary Variable 

class Planner {                 //Planner Class
  public:
    void add(char s1[],float st,char s2[],float ft){    //Add function adds given value to the dictionary
      Station* d=Railway.get(s1);
      if (d==NULL){
            Station data;
            strcpy(data.key,s1);
            data.value[0].start_time=st;
            data.value[0].finish_time=ft;
            strcpy(data.value[0].dest,s2);
            if (Railway.findFreeIndex(s1)>=0){
                Railway.put(data);
            }
            else{
                cout<<"No Space Left"<<endl;
            }
        }
        else{
            for (int i=0;i<64;i++){
                if (compare_float(d->value[i].start_time,-1)){
                    d->value[i].start_time=st;
                    d->value[i].finish_time=ft;
                    strcpy(d->value[i].dest,s2);
                    break;
                }
                if(d->value[i].start_time<st||compare_float(d->value[i].start_time,st)){
                    continue;
                }
                else{
                    Journey x=d->value[i];
                    d->value[i].start_time=st;
                    d->value[i].finish_time=ft;
                    strcpy(d->value[i].dest,s2);
                    for (int j=i+1;j<64;j++){
                        if (compare_float(d->value[j].start_time,-1)){
                            d->value[j]=x;
                            break;
                        }
                        Journey temp=d->value[j];
                        d->value[j]=x;
                        x=temp;
                    }
                    break;
                }
            }
        }
    }
    
    void q_station(char s1[],float st){       //prints the trains starting from s1 on or after st
      Station *s = Railway.get(s1);
      if(s!=NULL){
        for (int i=0;i<64;i++){
            if (compare_float(s->value[i].start_time,-1)){
              break;
            }
            if (s->value[i].start_time>st||compare_float(s->value[i].start_time,st)){
              cout<<s->value[i].start_time<<" "<<s->value[i].dest<<endl;
            }
          }
      }
      else{
        cout<<"Station "<<s1<<" does not exist"<<endl;
      }
    }
    void q_journey(char s1[],float st,char s2[]){       //prints the shortest possible journey with soonest possible start time after st starting from s1 to s2
      Station *s =Railway.get(s1);
      if (s!=NULL){
        bool q=false;
        for(int i=0;i<64;i++){
          if (compare_float(s->value[i].start_time,-1)){
            break;
          }
          if (s->value[i].start_time<st){
            continue;
          }
          else{
            if(strcmp(s->value[i].dest,s2)==0){
              cout<<s->value[i].start_time<<endl;
              q=true;
              break;
            }
            else{
              bool br=false;
              for (int k=i+1;compare_float(s->value[i].start_time,s->value[k].start_time);k++){
                if (strcmp(s->value[k].dest,s2)==0){
                  cout<<s->value[k].start_time<<endl;
                  q=true;
                  br=true;
                  break;
                }
              }
              if(br){
                break;
              }
              else{
                Station *z=Railway.get(s->value[i].dest);
                if (z!=NULL){
                  bool x=false;
                  for(int j=0;j<64;j++){
                    if (compare_float(z->value[j].start_time,-1)){
                        break;
                    }
                    if (z->value[j].start_time<s->value[i].finish_time){
                        continue;
                    }
                    else{
                      if(strcmp(z->value[j].dest,s2)==0){
                        cout<<s->value[i].start_time<<" "<<s->value[i].dest<<" "<<z->value[j].start_time<<endl;
                        q=true;
                        x=true;
                        break;
                      }
                    }
                  }
                  if(x){
                    break;
                  }
                }
              }
            }
          }
        }
        if (!q){
            cout<<"ERROR"<<endl;
        }
      }
    }
};
#endif
//End of Header