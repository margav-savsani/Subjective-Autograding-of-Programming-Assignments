#ifndef PLANNER_H
#define PLANNER_H
#include<iostream>
#include<cmath>
#include<string>
#include<cstring>
using namespace std;

int N = 64; //total number of trains
float B = (sqrt(5)-1)/2;
int ntrains = 0; // current number of trains in array

struct Station {
  // define suitable fields here
 public:
     char name[32];
};

class Train{
private:
public:
    float start_time, end_time; 
    Station start_station, end_station;

  Train(){
    this->status = 0;
  }
  float gettimediff(Train T){
    return (T.end_time - T.start_time);
  }
 /* Station getstation(Train T){
    return T.Station;
  }*/
  bool status = false;  // true if train is on the way
};

Train *A = new Train[N]; //array of size N that stores elements of Train datatyp

int hashValue(char key[]){    // hashtable with trains as entries
    int x = 41;   //value taken to minimize number of collisions
    int h, k ,i;
    k=0;
    i=0;  //h = hash value
    // int *C;  //array of coefficients of polynomial
    
    while(key[i]!= '\0'){
      //C[i] = int(key[i]);
      k +=  int(key[i])*pow(x,i);//polynomial
      i++;
    }
    // i+1 = number of letters in string
    //A = [a_0,a_1,.....,a_i] 

    h = N* ((k*B) - int(k*B));
    return h;
  }

int findFreeIndex(char key[]){
    int i = hashValue(key);
    while(true){
      if(A[i].start_station.name[0] == '\0')return i;
      if(i == 63)i = -1;
      if(i == hashValue(key)-1)return -1;
      i++;
    }
}


struct Journey {
  // define suitable fields here
};

struct Query{
  // define suitable fields here
public:

};


class Planner {
  // define suitable fields here
private:
public:
  bool add(Station S1, float T1, Station S2, float T2){
    if(ntrains < N){
        Train t;
        strcpy(t.start_station.name , S1.name);
        strcpy(t.end_station.name , S2.name);
        t.start_time = T1;
        t.end_time = T2;
        t.status = true;
        A[ntrains] = t;
        ntrains++;
        return true;
        }
    return false;
    }
    void getquerystation(Station S1, float T1){
        for(int i = 0; i < ntrains; i++){
            if((A[i].start_time <= T1)&&(A[i].start_station.name == S1.name)){
                cout << i << "           "<<A[i].start_time << "       " << A[i].end_station.name;
            }
        }
        return;
    }
       void queryjourney(Station S1, float T, Station S2){
        bool x = false;
        for(int i = 0; i < N; i++){
            if(!A[i].status)continue;
            else if(A[i].start_time>=T && strcmp(S1.name,A[i].start_station.name)==0 && strcmp(S2.name,A[i].end_station.name)==0){
                    cout << A[i].start_time <<endl;
                    x = true;
            }           
        }

        for(int i = 0; i < N; i++){
            if(!A[i].status)continue;
            else if(A[i].start_time>=T){
              for(int j = 0; j < N; j++){
                    if(!A[j].status)continue;
                    else if(A[i].end_time<=A[j].start_time && A[i].start_time>=T && strcmp(S1.name,A[i].start_station.name)==0 && strcmp(S2.name,A[j].end_station.name)==0){
                    cout << A[i].start_time << " " << A[i].end_station.name << " " << A[j].start_time << endl;
                    x = true;
                    }
                 
                }
            }
        }

        if(!x){
            cout << "ERROR"<<endl;
        }

        
    }
   

       /* Train T;
        T.start_time*/
    
};

#endif