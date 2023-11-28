#ifndef PLANNER_H
#define PLANNER_H
#include<iostream>
#include "string.h"
#include "queue.h"
#include "linearQueue.cpp"
using namespace std;

struct Station {
  char* name;
};

struct Journey {
  Station start;
  Station end;
  float start_time;
  float end_time;
};

class Planner {
  public:
    DynamicQueue<Journey> Queue;
    void add_journey(char *A, float start, char *B, float end){
      Journey J;
      J.start.name = A;
      J.end.name = B;
      J.start_time = start;
      J.end_time = end;
      Queue.QInsert(J);
      cout<<"ADDED"<<endl;
    }
    void all_trains(char *A, float start){
      int N = Queue.size();
      int p = 0;
      int q = 0;
      for(int i=0; i<N; i++){
        if(!strcmp(Queue.A[i].start.name,A)){
          q++;
          if(Queue.A[i].start_time>=start){
            cout<<Queue.A[i].start_time<<" "<<Queue.A[i].end.name<<endl;
            p++;
          }
        }
      }
      if(p==0){
        if(q==0) cout<<"ERROR! Station doesn't exist"<<endl;
        else cout<<"ERROR! No trains after this time"<<endl;
      }
    }
    void soonest(char *A, float start, char *B){
      int N = Queue.size();
      float least_time_zero_stop = 10000;
      for(int i=0; i<N; i++){
        if((Queue.A[i].start.name) == A){
          if(Queue.A[i].end.name == B){
            if(Queue.A[i].start_time<least_time_zero_stop) least_time_zero_stop=Queue.A[i].start_time;
          }
        }
      }
      float least_time_one_stop = 10000;
      char *P;
      float end_time;
      for(int i=0; i<N; i++){
        if((Queue.A[i].start.name) == A && Queue.A[i].end.name == B){
          char *C = Queue.A[i].end.name;
          for(int j=0; j<N; i++){
            if(Queue.A[j].start.name == C){
              if(Queue.A[j].end.name == B){
                if(Queue.A[i].start_time<least_time_one_stop) {
                  least_time_one_stop=Queue.A[i].start_time;
                  P=C;
                  end_time=Queue.A[j].start_time;
                }                
              }
            }
          }
        }
      }
      float least_time = min(least_time_one_stop, least_time_zero_stop);
      if(least_time == 10000) cout<<"ERROR! No such path"<<endl;
      else{
        if(least_time==least_time_zero_stop) cout<<least_time<<endl;
        else cout<< least_time<<" "<<P<<" "<<end_time<<endl;
      }
    }
};

#endif
