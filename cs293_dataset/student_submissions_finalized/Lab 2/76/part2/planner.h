#include<iostream>
#include<string.h>
#include<cmath>
using namespace std;

#ifndef PLANNER_H
#define PLANNER_H

struct Station {
  // define suitable fields here
  
 
};
int total_stations = 50;
 
struct Journey {
  // define suitable fields here
  char station_one[32];
  char station_two[32];
  float start_time;
  float finish_time;
};

struct Query{
  // define suitable fields here
};

class Planner {
  // define suitable fields here
  private:
  struct Station *B;
  struct Journey *A;
  int n;
  public:
  Planner(){//initaialise to a variable
    n = total_stations;
  A = new Journey[64];
  for(int i = 0;i<n;i++){
    strcpy(A[i].station_one,"s") == 0;
  }
  for(int i=0;i<n;i++){
    A[i].start_time = 0;
  }
   for(int i = 0;i<n;i++){
    strcpy(A[i].station_two,"s") == 0;
  }
  for(int i=0;i<n;i++){
    A[i].finish_time = 0;
  }
  }
  bool hashValue(char station_one[]){
      string k = station_one;
int n = k.length();
int p = station_one[n-1];
for(int i=(n-1);i>=0;i--){
  p = (station_one[i]+p*(37))%64;
}
double j = ((sqrt(5)-1)/2)*p; 
j = j-int(j);
j = j*(n);
return j;
  }

int findFreeIndex(char station_one[]){
  int h = hashValue(station_one);
int IN = -1;
bool found = false;
if(strcmp(A[h].station_one,"s") == 0){
  found = true;
  IN = h;}
else if(found == false){
  for(int i=(h+1);i<n;i++){
    if(strcmp(A[i].station_one,"s") == 0){
      found = true;
      IN = i;
    }
  }}
else if(found == false){
  for(int i=0;i<h;i++){
    if(strcmp(A[i].station_one,"s") == 0){
      found = true;
      IN = i;
    }
  }
}
return IN;
}
bool ADD(struct Journey e){//insert data
 char *c = e.station_one;
 char *b = e.station_two;
  int h = findFreeIndex(c);
  bool In = false;
  if(h==-1)
        In = false;
  else if((A[h].start_time == 0)&&(A[h].finish_time == 0))
         {
          strcpy(A[h].station_one,c) == 0;
          strcpy(A[h].station_two,b) == 0;
          A[h].start_time = e.start_time;
          A[h].finish_time = e.finish_time;
         In = true;
         } 
  
  return In;

}

struct Journey* QUERY_STATION(char station_one[],int start_time){//compare data
  int h = hashValue(station_one);
  
  for(int i=h;i<64;i++){
    if((strcmp(A[i].station_one,station_one)==0)&&(A[i].start_time>=start_time))
      cout<<A[i].start_time<<" "<<A[i].station_two<<endl;
      
  }
  
  for (int i=0;i<h;i++){
  if((strcmp(A[i].station_one,station_one)==0)&&(A[i].start_time>=start_time))
     cout<<A[i].start_time<<" "<<A[i].station_two<<endl;
      
  }

  return NULL;
  }
  int QUERY_JOURNEY(char station_one[],int start_time,char station_two[]){
    char inter[32];
    int h = hashValue(station_one);
    float p;
    char *m;
    float q;
    int g =0;
    int cnt1=0,cnt2=0;
    Journey* dir = new Journey[64];
    Journey* ind = new Journey[64]; 
     for(int i=0;i<64;i++){
    if(((A[i].start_time == start_time)&&(strcmp(A[i].station_two,station_two) == 0)&&
    (strcmp(A[i].station_one,station_one)==00)))
    
    g=1;
    
     }
     if(g=0)
     cout<<"no path";
    for(int i=0;i<64;i++){
      if((A[i].start_time >= start_time)&&(strcmp(A[i].station_two,station_two) == 0)){
        dir[cnt1] = A[i];
       cnt1++;}
      for(int i=0;i<cnt1;i++){
        if(strcmp(dir[i].station_two,station_two)==0){
        p = dir[i].start_time;
        m = dir[i].station_one;
        ind[cnt2]= dir[i];
        cnt2++;
        
        }

        for(int i=0;i<cnt2;i++){
          if(strcmp(ind[i].station_two,station_two)==0){
            if(p>=ind[i].start_time){
            p = ind[i].start_time;
            m = ind[i].station_one;
          }
        }
        
      }
     
      }
     
    }
cout<<m<<endl;
     return p;
    }
 
  };

#endif