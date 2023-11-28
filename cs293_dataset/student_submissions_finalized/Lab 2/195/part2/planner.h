#ifndef PLANNER_H
#define PLANNER_H
#include <string.h>
#include <iostream>
using namespace std;

struct Station {
  // define suitable fields here
};

struct Journey {
  string Station1;
  string Station2;
  float departure=-1;
  float arrival;
  
       // define suitable fields here
};
Journey k[50];
struct Query{
};
class Planner {
  public:
   void ADD(Journey k){
     cout<<k.Station1<<endl;
     cout<<k.departure<<endl;
     cout<<k.Station2<<endl;
     cout<<k.arrival<<endl;
   }
   void QUERY_STATION(string S,float p){
         int a=p/100;
             int i=0;
             while(k[a].departure!=-1){
             if(!strcmp(k[a].Station1.c_str(),S.c_str())&&(k[a].departure>=p)){
                   cout<<k[a].departure<<" "<<k[a].Station2<<endl;
                   i=i+1;
             }
             a=(a+1)%50;
             }
            if(i==0){
                  cout<<"ERROR"<<endl;
            }
   }
   };
  // define suitable fields here

#endif