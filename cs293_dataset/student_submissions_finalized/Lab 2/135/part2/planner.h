#ifndef PLANNER_H
#define PLANNER_H

#include <cmath>

using namespace std;


int hashcode(char key[]){
  long long int h = 0, i = 0, x = 31;
  while(key[i] != '\0'){
    h = (h*x + key[i]);
    i++;
  }
  float fibonacci = h*(sqrt(5)-1)/2.0;
  float fraction = fibonacci - int(fibonacci);
  h = 10.0*fraction;
  return h;
}

struct Station {
  // define suitable fields here
  char name[32] = "";
};

struct Journey{
  // define suitable fields here
  Station start;
  float stime = 0;
  Station end;
  float etime = 0;
};

struct Query {
  // define suitable fields here
  Station s1, s2;
  float stime = 0;
};

class Planner {
  // define suitable fields here
  Journey list[100];
  int full = 0;
  public:
  void insert(Journey j){
    if(full == 100){
      cout << "ERROR\n";
      return;
    }
    if(full == 0){
      list[full] = j;
      full++;
    }
    else if(full == 1){
      if(list[full].stime < j.stime){
        list[full] = j;
        full++;
      }
      else{
        list[1] = list[0];
        list[0] = j;
        full++;
      }
    }
    else{
      int free = full;
      for(int i=0; i<full-1; i++){
        if(list[i].stime<j.stime && list[i+1].stime >= j.stime){
          free = i+1;
          break;
        }
      }
      for(int i=full; i>free; i--){
        list[i] = list[i-1];
      }
      list[free] = j;
      full++;
    }
  }

  void qStation(Query q){
    bool found = 0;
    for(int i=0; i<full; i++){
      if(strcmp(list[i].start.name, q.s1.name) == 0 && list[i].stime >= q.stime){
        cout << list[i].stime << " " << list[i].end.name << "\n";
        found = 1;
      }
    }
    if(!found){
      cout << "ERROR\n";
    }
  }
  void qJourney(Query q){
    int singletime = -1, doubletime = -1, start2;
    char* station2;
    for(int i=0; i<full; i++){
      char* s_station = list[i].start.name;
      char* e_station = list[i].end.name;
      int stime = list[i].stime;
      int etime = list[i].etime;
      if(strcmp(s_station, q.s1.name) == 0 && strcmp(e_station, q.s2.name) == 0 && stime >= q.stime){
        singletime = stime;
        break;
      }
    }

    for(int i=0; i<full; i++){
      char* s_station = list[i].start.name;
      char* e_station = list[i].end.name;
      int stime = list[i].stime;
      int etime = list[i].etime;
      if(strcmp(s_station, q.s1.name) == 0 && stime >= q.stime){
        for(int j=0; j<full; j++){
          char* s_station2 = list[j].start.name;
          char* e_station2 = list[j].end.name;
          int stime2 = list[j].stime;
          if(strcmp(e_station, s_station2) == 0 && strcmp(e_station2, q.s2.name)==0 && stime2 >= etime){
            doubletime = stime;
            start2 = stime2;
            station2 = s_station2;
          }
        }
      }
    }

    if(singletime == -1 && doubletime == -1){
      cout << "ERROR\n";
      return;
    }
    if(singletime != -1 && singletime <= doubletime || doubletime == -1){
      cout << singletime << "\n";
    }
    else if(doubletime != -1 && singletime > doubletime || singletime == -1){
      cout << doubletime << " " << station2 << " " << start2 << "\n";
    }
  }
};


#endif