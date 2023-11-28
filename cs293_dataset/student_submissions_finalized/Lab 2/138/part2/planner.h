#ifndef PLANNER_H
#define PLANNER_H


struct Station {
  // define suitable fields here
};

struct Entry {
  char key[32];
  float start_time;
  char station_two[32];
  float finish_time;
  Entry(char s,float start,char f,float end){
    key[0]=s;
    start_time=start;
    station_two[0]=f;
    finish_time=end;
  } 
  Entry(){
    
  }
};

struct listt{
  
};


#endif