//Copyright: Yuvraj Singh 210050172
#include <cmath>
#include <string.h>
#include <climits>
#include "planner.h"
struct Journey {        //Struct Journey stores the start_time finish_time and destination of a journey
  float start_time;
  char dest[64];
  float finish_time;
  Journey(){
    start_time=-1;
  }
};
struct Station{           //Struct Station is the entry of the dictionary class It contains a key storing the station name and value of type Journey storing the journey details
    char key[64];
    Journey value[64];
    Station(){
        strcpy(key,"-");
    }
};

int DICT_SIZE = 64;       //Size of Dictionary
bool compare_float(float x, float y, float epsilon = 0.01f){      //Fun for checking equality of floating point numbers upto a precision of 2
    if(fabs(x - y) < epsilon){
      return true; //If they are same
    }
    return false; //If they are different
}

class Dictionary{           //Implements a Dictionary
 private:
  int N; // size of array A
  struct Station *A; // Array of dictionary entries

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]){
      int pk=0;
    int x=37;
    int m=1;
    int i=0;
    double c;
    while(key[i]!='\0'){
        pk=pk+int(key[i]);
        pk=(((pk%N)*(m%N))%N);
        m=(m*x)%N;
        i++;
    }
    double Az=(pow(5,0.5)-1)/2;
    double t=pk*Az;
    t=modf(t,&c);
    return floor(t*N);
  }

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]){
      int probe=hashValue(key);
    int i=1;
    while(i<=N){
        if (strcmp(A[probe].key,"-")==0){
            return probe;
        }
        else{
            probe=(probe+1)%N;
        }
        i++;
    }
    return -1;
}

  
  // Default constructor
  Dictionary(){
    N=DICT_SIZE;
    A=new Station[N];
} 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Station *get(char key[]){
      int z=hashValue(key);
    while(!(strcmp(A[z].key,"-")==0)){
        if (strcmp(A[z].key,key)==0){
            return &A[z];
        }
        else{
            z=(z+1)%N;
        }
    }
    return NULL;
  }

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Station e){
      int f=findFreeIndex(e.key);
      if (f!=-1){
        A[f]=e;
        return true;
      }
      return false;
  }
};
//End of Dictionary Header