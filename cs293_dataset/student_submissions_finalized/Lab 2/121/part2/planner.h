#ifndef PLANNER_H
#define PLANNER_H
#include<iostream>
#include<cstring>
using namespace std;

struct Station {
  // define suitable fields here
  char name[32];
};

struct Journey {
  char dest[32];    //destination name, source name is not needed as these will be assigned to a source in dictionary
  float dept_time;  //time of departure from source
  float arr_time;  //time of arrival on destination
};

struct Query{
  // define suitable fields here
};

class departures {
  Journey * connections;  //sorted (by dept_time) array of possible journeys possible from source
  int capacity = 50;    //current capacity of array
  int increment = 50;    //if need arises, array can be grown
  int size = 0;   //number of journeys possible from station at any time
public:
  departures(){
    connections = new Journey[capacity];

  } 

  void add_journey(Journey j){
    if (size == capacity){  //array is full
      //growing the array
      Journey* temp = new Journey[capacity+increment]; //new temp array
      for (int i=0; i<size; i++){  //copying the array
        temp[i] = connections[i]; 
      }
      capacity += increment; //updating variables
      delete []connections;
      connections = temp;  //reassigning 
      temp = nullptr;
    }
    if (size == 0){  //trivial case
      connections[0] = j; 
      size++;
      return;
    }
    int i=size-1;   //adding the journey on the correct spot and shifting all the elements to the right of it
    for (i = size - 1; (i >= 0 && connections[i].dept_time > j.dept_time); i--)
        connections[i + 1] = connections[i];
 
    connections[i + 1] = j;
    size++;
    return;
  }
  void start_query(float time){   //for Query_station, gives the journey including and after start time
    int ind;   
    int i=0;
    for (ind=size-1; (ind>=0 && (connections[ind].dept_time + 0.001)>=time); ind--){
      cout<<connections[ind].dept_time<<" "<<connections[ind].dest<<endl;
      i++;
    }
    
    if (i==0) cout<<"No trains after selected time were found"<<endl;
  }
  Journey* direct(char stn[], float time){   //tells if the source station is connected with the given station after a given time
  //returns journey pointer if there is any Journey in connections whose dest is same as stn
    for (int i=0; i<size; i++){
      if ((strcmp(stn, connections[i].dest)==0) && ((connections[i].dept_time+0.001)>=time)){
        return &(connections[i]);
      }
    }
    return nullptr;
  }
  int bin_search_time(int time){ // returns the smallest index with dept time >= time
    int high = size-1;  //binary search for least index with dept time >= 'time'
    int low=0;
    while(low<=high){
      if((connections[low].dept_time+0.001)>=time) return low;
      int mid = (high+low)/2;
      if((connections[mid].dept_time-0.001)<time) low = mid+1;
      else if((connections[mid].dept_time+0.001)>=time) high=mid;
    }
    return -1;
  }
  Journey refer(int ind){   //returns the journey of a particular index
  //basically, the output of this function will either be used as directly final destination or an intermediate station
    return connections[ind];  
  }
  void print_journey(int ind){
    cout<<connections[ind].dept_time<<endl;
  }
  int len(){   //length of depratures 'list'
    return size;
  }
};


#endif