#ifndef PLANNER_H
#define PLANNER_H
#include<cmath>
#include<iostream>
using namespace std;

int DICT_SIZE = 32;
double fib = (sqrt(5) - 1)/2;

struct Station {
  // define suitable fields here
};

struct Journey {
  // define suitable fields here
  char key[32];
  char end[32];
  double start_time, end_time;
};

struct Query{
  // define suitable fields here
};

class Planner {
  // define suitable fields here
  private:
    int N;
    struct Journey *A;
  public:
    Planner(){
      N = DICT_SIZE;
      A = new Journey[DICT_SIZE];
    }
    int hashValue(char key[]){
      int poly[32];
	    int size=0;
	    while(key[size] != '\0'){
		    poly[size] = int(key[size]);
		    size++;
	    }
	    int result;
	    result = (poly[0])% N;
	    int x = 33;
	    for(int i=1; i<size; i++){
		    result = ((result*x)%N + (poly[i])%N)%N;
	    }
	    return result;
    }

    int findFreeIndex(char key[]){
      double hash = hashValue(key);
	    int hashindex;
	    double a = hash*fib;
	    int b = int(a);
	    double c = a - b;
	    hashindex = int(N*c);
	    int freeindex = hashindex;
	    for(int i=hashindex; i<=hashindex+N; i++){
		    if(strcmp(A[i].key, "\0")) return freeindex;
		    freeindex = (freeindex+1)%N;
	    }
	    return -1;
    }

    struct Journey *get(char key[]){
      for(int i=0; i<N; i++){
		    if(strcmp(A[i].key,key)==0) return &(A[i]);
    	}
	    return NULL;
    }

    bool put(struct Journey j){
      int index = findFreeIndex(j.key);
      if(index == -1) return false;
      else{
        A[index] = j;
        return true;
      }
    }

    bool remove(char key[]){
      Journey *ptr = get(key);
	    if(ptr == NULL) return false;
	    else{
		    strcpy(ptr-> key,"DELETED");
        strcpy(ptr-> end,"DELETED");
		    ptr-> start_time = -1;
        ptr-> end_time = -1;
		    return true;
	    }
    }
    //  QUERY_STATION
    
};

void query_station(char in_station[], double time, Planner planner){
  Journey *j = planner.get(in_station);
  while(j->end_time !=-1){
    if(!strcmp(j->key,in_station)&&(j->end_time >= time)){
      cout << j->end_time << " " << j->end << endl;
    }

  }
}

void query_journey(char in_station[], double time, char out_station[], Planner planner){
  Journey *j = planner.get(in_station);
  while(j->end_time !=-1){
    if(!strcmp(j->key,in_station)&&(j->end_time >= time)){
      cout << j->start_time << " "<< j->end << " " << j->end_time << endl;
    }

  }
}

#endif