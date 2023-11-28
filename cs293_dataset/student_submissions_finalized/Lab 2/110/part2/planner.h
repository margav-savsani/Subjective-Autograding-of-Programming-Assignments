#ifndef PLANNER_H
#define PLANNER_H
#include<iostream>
#include<cmath>
#include<string.h>
using namespace std;

int N = 64;
class Journey {
    public:
    string station1 = "empty";
    string station2;
    float starttime;
    float endtime;
};

class Planner {
  public:
    Journey journ[64];

    int hashvalue(string s){
        int x = 37;
        long long int poly=0;
        int i = 0;
        while(s[i] != '\0'){
            poly = x*poly+s[i];
            poly = poly%N;
            i++;
        }
        return poly;
    }
 void add(Journey j){
    int p = hashvalue(j.station1);
    int i=p;
    while(i<N){
        if(journ[i].station1 == "empty"){
             journ[i] = j;
             break;
        }
        i++;
    }
    
    return;
 }

 void Query(Journey j){
    int p = hashvalue(j.station1);
    int k = p;
    bool b = true;
    for(k=p;k<N;k++){
         if((journ[k].station1==j.station1)&&(journ[k].starttime >= j.starttime)){
              cout<<journ[k].starttime<<" "<<journ[k].station2<<endl;
              b = false;
         }
    }
   if(b) cout<<"ERROR"<<endl;
 }
 
};

#endif
