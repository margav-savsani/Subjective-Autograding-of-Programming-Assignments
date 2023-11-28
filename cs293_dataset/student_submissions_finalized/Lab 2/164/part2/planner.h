#include<iostream>
#include <cmath>
#include"Dictionary.h"
#include <cstring>
using namespace std;
#ifndef PLANNER_H
#define PLANNER_H

struct Query{
  char start[30];
  char end[30];
  float start_point;
};

class Planner {
  Dictionary d;
  public:
    void add( char* star, float st, char* en, float et){
      Entry e;
      strcpy(e.s.end,en);
      strcpy(e.key,star);
      e.s.start_time=st;
      e.s.end_time=et;
      int a=d.put(e);
    }
    void query_station(char * start,float st)
    {int l;
    char k[30];
      int a=d.hashValue(start);
      l=d.A[a].s.start_time;
      for (int i=a;i<64;i++)
      { 
        if (d.A[i].s.start_time>=st)
        {
          if (l>=d.A[i].s.start_time)
          {
            l=d.A[i].s.start_time;
            strcpy(k,d.A[i].s.end);
            cout<<l<<" "<<k<<endl;
          }
          
          
        } 
        
      }
      
    }

    void query_journey(char *start,float st,char *en){
        int a=d.hashValue(start);
        int b=0;
        float t=0;
        int ch=0;
        for (int i = a; i < 64; i++)
        {if (d.A[i].filled==0)
        {
          break;
        }
        
          if(d.A[a].filled==1){
          if (strcmp(d.A[i].s.end,en)==0 && strcmp(d.A[i].key,start)==0)
          {
            if(t==0)
            {
              b=d.A[i].s.start_time;
              t=1;
              ch=1;
            }
            else if(b>d.A[i].s.start_time)
            {
              b=d.A[i].s.start_time;
              ch=1;
            }
          }
        }
        }
        for(int i=a;i<64;i++){
          if (d.A[i].filled==1)
          {
            if(b==0)
            {
              b=d.A[i].s.start_time;
            }
          
          if(strcmp(d.A[i].key,start)==0 && d.A[i].s.start_time<=b && d.A[i].s.start_time>st)
          {
            char l[30];
            strcpy(l,d.A[i].s.end);
            int q=d.hashValue(l);
            for (int j=q;j<64;j++)
            {
              if(d.A[j].filled==1){
              if (strcmp(d.A[j].s.end,en)==0 && strcmp(d.A[j].key,l)==0 && d.A[i].s.end_time<d.A[j].s.start_time)
              {
                cout<< d.A[i].s.start_time<<" "<<l<<" "<<d.A[j].s.start_time<<endl;
                ch=1;
                return;
              }
              }
              
            }
          }
        }
        
    }
    if(ch==0){cout<<"ERROR"<<endl;}
    else cout<<b<<endl;
    }
};

#endif