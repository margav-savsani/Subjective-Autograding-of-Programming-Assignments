#ifndef PLANNER_H
#define PLANNER_H
#include "dictionary.cpp"
#include<iostream>
#include<cassert>

struct Journey {
  // define suitable fields here
  char* dest_name;
  int finish_time;
  Journey(){
    dest_name = new char[32];
  }
};

struct Query{
  // define suitable fields here
  int start_time;
  Journey *j;
  bool null;
  Query(){
    j = new Journey;
    null=true;
  }
};

struct Station {
  // define suitable fields here
  char *name;
  Query *z;
  int tail;
  Dictionary *dest;
  Station(){
    name = new char[32];
    z= new Query[50];
    tail=0;
    dest = new Dictionary;
  }
  void add_t(Query q){
    z[tail]=q;
    Entry e;
    e.key()=q.j->dest_name;
    e.value()=tail;
    dest->put(e);
    tail++;
  }
  int q_st(char *final){
    if(dest->get(final)==NULL) return -1;
    else {
      int ind= dest->get(final)->value();
      return z[ind].start_time;
    }
  }
};

class Planner {
  // define suitable fields here
  Station *s;
  int end;
  Dictionary *station;

  public:
  Planner(){
    s = new Station[20];
    end=0;
    station = new Dictionary;
  }

  void add(char *start, int st_time, char *dest, int fi_time){

    Query q;
    q.start_time=st_time;
    q.j->dest_name=dest;
    q.j->finish_time=fi_time;
    q.null=false;

    if(station->get(start)!=NULL){
      int index=station->get(start)->value();
      s[index].add_t(q);
    }
    else{
      Station temp_s;
      temp_s.name=start;
      temp_s.add_t(q);

      s[end]=temp_s;

      Entry e;
      e.key()=start;
      e.value()=end;

      station->put(e);
    
      end++;
    }
    
  }

  Station* get_station(char *begin){
    if(station->get(begin)==NULL){
      return NULL;
    }
    else{
      int index=station->get(begin)->value();
      return &s[index];
    }
  }
};

#endif