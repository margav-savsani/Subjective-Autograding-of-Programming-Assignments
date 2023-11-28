#ifndef PLANNER_H
#define PLANNER_H
#include <iostream>
#include <string.h>
#include <fstream>
#include <cmath>
using namespace std;

const int MAX_SIZE=100;
class Station{
  public:
  char station[50];
  float time;
};
class Journey {
public: // define suitable fields here
  char station1[50];
  char station2[50];
  float starttime;
  float endtime;
};
class Query{
  public:
  char station1[50];
  char station2[50];
  float starttime;
};
Journey J[MAX_SIZE];



class Planner {
  // define suitable fields here

  public:

    int hashValue(char key[]){
      int size=0,i=0;
    int h=0;
    while(key[i]!='\0'){
        i++;
        size++;
    }
    i=0;
    while(i<size){
        h=h + (h*37+int(key[i]))%10000;
        i++;
    }
    double f=(sqrt(5)-1)/2.0;
    double hash=h;
    hash = hash*f - int(hash*f);
    return (int(hash*MAX_SIZE));
    }

    void Add(Journey j){
      int a=hashValue(j.station1);
      if(strlen(J[a].station1)==0){
        J[a]=j;
        return;
      }
      else{
        a=(a+1)%MAX_SIZE;
        while(strlen(J[a].station1)!=0){
          a=(a+1)%MAX_SIZE;
        }
        J[a]=j;
        return;
      }
    }
  void Query_station(Station s){
    int a=hashValue(s.station);
    int x=0;
    while(strlen(J[a].station1)!=0){
      if(J[a].starttime>=s.time && !strcmp(J[a].station1,s.station)){
      x++;
      cout<<J[a].starttime<<" "<<J[a].station2<<endl;
      }
      a=(a+1)%MAX_SIZE;
    }
     if(x==0){
      cout<<"ERROR"<<endl;
     }
  }
  void Query_journey(Query q){
      int a=hashValue(q.station1);
      int x=0;
      float startmin1=0;
      while(strlen(J[a].station1)!=0){
        if(J[a].starttime>=q.starttime && !strcmp(J[a].station1,q.station1)&& !strcmp(J[a].station2,q.station2)){
          if(x==0){
            startmin1=J[a].starttime;
          }
          else if(startmin1>J[a].starttime){
            startmin1=J[a].starttime;
          }
          x++;
          break;
          }
          a=(a+1)%MAX_SIZE;
      }
      a=hashValue(q.station1);
      int b;
      int y=0;
      float end1=0;
      float startmin_1=0;
      float startmin2=0;
      char s1[50];
      while(strlen(J[a].station1)!=0){
        if(J[a].starttime>=q.starttime && !strcmp(J[a].station1,q.station1)&& strcmp(J[a].station2,q.station2)){
          b=hashValue(J[a].station2);
          while(strlen(J[b].station1)!=0){
            if(J[b].starttime>=J[a].endtime && !strcmp(J[b].station1,J[a].station2)&& !strcmp(J[b].station2,q.station2)){
              if(y==0){
                startmin_1=J[a].starttime;
                startmin2=J[b].starttime;
                end1=J[a].endtime;
                strcpy(s1,J[a].station2);
              }
              else if(startmin2>J[b].starttime){
                startmin2=J[b].starttime;
                startmin_1=J[a].starttime;
                end1=J[a].endtime;
                strcpy(s1,J[a].station2);
              }
                y++;
                break;
              }
              b=(b+1)%MAX_SIZE;
            }
          }
          a=(a+1)%MAX_SIZE;
        }

    if(startmin1<startmin_1 && startmin1!=0){
      cout<<startmin1<<endl;
    }
    else if(startmin1>startmin_1 && startmin_1!=0){
      cout<<startmin_1<<" "<<s1<<" "<<startmin2<<endl;
     }
    else if(startmin1==0 && startmin_1!=0){
      cout<<startmin_1<<" "<<s1<<" "<<startmin2<<endl;
    }
    else if(startmin_1==0 && startmin1!=0){
     cout<<startmin1<<endl;
    }
    else{
      cout<<"ERROR"<<endl;
    }
  }

};

#endif