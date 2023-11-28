#include<iostream>
#include<string.h>
#include"planner.h"
using namespace std;

// Adds journey entry, contains start time, intermediate time, and intermediate station
void Journey::add(const char* inter_stn, float stime, float inter_time = -1){
  this ->stime = stime;
  strcpy(this ->inter_stn, inter_stn);
  this->inter_time = inter_time;
}

// default constructor
Planner::Planner(){
}

// adds train journeys to planner
void Planner::add(char start[], float stime, char end[], float etime){
    Entry e1;
    strcpy(e1.key, start);
    e1.value = stime;
    e1.join_idx = station.end.findFreeIndex(end);
    Entry e2;
    strcpy(e2.key, end);
    e2.value = etime;
    e2.join_idx = station.start.findFreeIndex(start);
    station.start.put(e1);
    station.end.put(e2);
    return;
  }

// tells the trains leaving after start time, from given station
void Planner::query_station(char start[], float stime){
      bool found = false;
      struct Entry *ptr = station.start.get(start);
      while(strcmp(ptr->key, start) == 0){
        if(ptr->value >= stime){
          cout << ptr->value << " " << station.end.A[ptr->join_idx].key << endl;
          found = true;
        }
        ptr = station.start.next(ptr->index);
      }
      if(!found)
        cout << "ERROR" << endl;
      return;
  }

// lists the quickest train to catch to get to a location, via one intermediate station
void Planner::query_journey(char start[], float stime, char end[]){
    int jrny_idx = 0;
    Journey min;
    Journey jrny[64];
    min.add("\0", 2359);
    bool found = false;
    struct Entry *ptr = station.start.get(start);

    // if entered data is invalid, exits the program
    if(station.start.get(start) == NULL || station.end.get(end) == NULL){
      cout << "Stations don't exist" << endl;
      return;
    }

    //first finds the journeys from start station to end station, via 1 intermediate station, pertaining to given times

    while(strcmp(ptr->key, start) == 0){
        if(ptr->value >= stime){
          if(strcmp(station.end.A[ptr->join_idx].key, end) == 0){
            jrny[jrny_idx].add("\0", ptr->value, -1);
            jrny_idx = (jrny_idx+1)%64;
            found = true;
          }
          else{
            char* inter = station.end.A[ptr->join_idx].key;
            struct Entry *ptr2 = station.start.get(station.end.A[ptr->join_idx].key);
            while(strcmp(ptr2->key, inter) == 0){
              if(strcmp(station.end.A[ptr2->join_idx].key, end) == 0 && ptr2->value >= station.end.A[ptr->join_idx].value){
                jrny[jrny_idx].add(ptr2->key, ptr->value, ptr2->value);
                jrny_idx = (jrny_idx+1)%64;
                found = true;
              }
              ptr2 = station.start.next(ptr2->index);
            }
          }
        }
        ptr = station.start.next(ptr->index);
    }
    // finds the quickest possible journey, once all journeys are found
    if(found){
      for(int i = 0; jrny[i].stime != -1; i++){
        if(min.stime > jrny[i].stime){
            strcpy(min.inter_stn, jrny[i].inter_stn);
            min.stime = jrny[i].stime;
            min.inter_time = jrny[i].inter_time;
        }
      }
    //prints the required output
      cout<< min.stime <<" " <<min.inter_stn << " ";
      if(min.inter_time > 0)
        cout << min.inter_time << endl;
      else
        cout << endl;
    }
    else
      cout << "ERROR" << endl;
}
