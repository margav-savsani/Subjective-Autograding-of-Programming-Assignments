#ifndef PLANNER_H
#define PLANNER_H
#include <string>
#include "dictionary.cpp"
#include "dictionary.h"

struct Station {
  char name[32];
};

struct Journey {
  Station start;
  Station end;
  float startTime;
  float endTime;

};
struct routenode{
  Journey current;
  routenode* next=NULL;
};

struct q_station{
  Station start;
  float time;
};
struct q_journey{
  Station start;
  Station end;
  float time;
};

class Planner {
  public:
  Dictionary stations;
  routenode* route;
  int no_stations;
  public:
  Planner(){
    route= new routenode[DICT_SIZE];
    no_stations=0;
  }


  void addJourney(Journey j){
    Entry *ans;
    ans= stations.get(j.start.name);
    if(ans==NULL){
      route[no_stations].current=j;
      Entry e;
      strcpy(e.key,j.start.name);
      e.value=no_stations;
      stations.put(e);
      no_stations++;
      }
    else{
      int index=ans->value;
      float time=j.startTime;
      routenode* r= &route[index];
      routenode* s= new routenode;
      if(r->current.startTime>=time){
        s->current=r->current;\
        s->next=r->next;
        r->current=j;
        r->next=s;
      }
      else{
        s->current=j;
        while(true){
        if(r->next==NULL){
          r->next=s;
          break;
        }
        if(time<=r->next->current.startTime){
          s->next=r->next;
          r->next=s;
          break;
        }
        r=r->next;
      }
      }
    }

  } 

  void query_station(q_station q){
    Entry *ans;
    ans=stations.get(q.start.name);
    if(ans==NULL){
      cout<<endl<<"ERROR";
    }
    else{
      int index=ans->value;
      routenode* r =&route[index];
      int total=0;
      while(r!=NULL){
        if(r->current.startTime>=q.time){
          total++;
          cout<<endl<<r->current.startTime<<" "<<r->current.end.name;
        }
        
        
        
        
        r=r->next;
      }
      if(total==0)cout<<endl<<"ERROR";
    }
  }

  void query_journey(q_journey q){
    bool found=false;
    Entry *ans;
    ans=stations.get(q.start.name);
    if(ans==NULL){
      cout<<endl<<"ERROR";
    }
    else{
      int index=ans->value;
      routenode* r =&route[index];

      while(r!=NULL){

        
        
        if(r->current.startTime>=q.time){
          if(strcmp(r->current.end.name , q.end.name)==0){
              
              cout<<endl<<r->current.startTime;
              return;
          }
          else{
            Entry* ans2;
            ans2=stations.get(r->current.end.name);
            if(ans2==NULL){}
            else{
              int i=ans2->value;
              routenode* x=&route[i];
              while(x!=NULL){
                if((x->current.startTime >= r->current.endTime)&& (strcmp(x->current.end.name,q.end.name)==0)){
                  cout<<endl<<r->current.startTime<<" "<<r->current.end.name<<" "<<(x->current.startTime);
                  return;
                }
                x=x->next;
              }
            }
          }

        }
        r=r->next;
      }
      cout<<endl<<"ERROR";
    }  
  }

  void interactive(){
    cout<<endl;
    while(true){
      char inp[64];
      cin>>inp;
      if(strcmp(inp,"ADD")==0){
        Journey j;
        char start[64];
        char end[64];
        float stime,etime;
        cin>>start>>stime>>end>>etime;
        strcpy(j.end.name,end);
        strcpy(j.start.name,start);
        j.endTime=etime;
        j.startTime=stime;
        addJourney(j);
      }
      if(strcmp(inp,"QUERY_JOURNEY")==0){
        q_journey q;
        char start[64];
        char end[64];
        float stime;
        cin>>start>>stime>>end;
        strcpy(q.end.name,end);
        strcpy(q.start.name,start);
        q.time=stime;
        query_journey(q);

      }
      if(strcmp(inp,"QUERY_STATION")==0){
        q_station q;
        char start[64];
        float stime;
        cin>>start>>stime;
        strcpy(q.start.name,start);
        q.time=stime;
        query_station(q);

      }
      if(strcmp(inp,"EXIT")==0)break;
      
    }
  }
  



};



int main(){
  Planner p;
  p.interactive();
  
}

#endif
