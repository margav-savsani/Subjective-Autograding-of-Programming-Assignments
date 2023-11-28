#include <iostream>
#ifndef PLANNER_H
#define PLANNER_H
#include <string.h>
#include <cmath>
using namespace std;

struct Station {
  // define suitable fields here
};

struct Journey {
  string s1;
  string s2;
  float t1;
  float t2;

};

struct Query{
  // define suitable fields here
};

class Planner {
  Journey* J;
  int n;
  public:
  Planner(){
    n=512;
    J = new Journey[n];//ARRAY IS CREATED
    for(int i=0;i<n;i++){
      J[i].s1 = "NULL";//INITIALIZED THE GARBAGE VALUE TO ARRAY
    }
  }
  int hashValue(string y){//FUNCTION TO GET THE HASHVALUE OF THE STRING
    int h=0,j=41;
    for(int i=0;i<y.length();i++)
      h = (h * j) + int(y[i]);
    double x=h*((sqrt(5)-1)/2);
    double frac,inte;
    frac = modf(x,&inte);
    frac = frac*n;
    return abs((int)frac);
  }
int findFreeIndex(string x){//FUNCTION TO CHECK FOR PROBING
    int probing=hashValue(x);
    while(J[probing].s1 != "NULL"){
        probing=(probing+1)%n;
        if(probing == hashValue(x)){
            return -1;
        }
    }
    return probing;
}
void ADD(string a,float x,string b,float y){//ADDING A JOURNEY
  int position = findFreeIndex(a);
  if(position != -1){
    Journey A;
    A.s1 = a;
    A.t1 = x;
    A.s2 = b;
    A.t2 = y;
    J[position] = A;
  }
}
void QUEERY_STATION(string p,float q){
  int probing=hashValue(p),c=0;
  
  while(J[probing].s1 != "NULL"){
    if(J[probing].s1 == p){
    cout<<J[probing].t1<<" "<<J[probing].s2<<endl;
    c++;
    } 
    probing=(probing+1)%n;
    if(probing == hashValue(p) && c==0){
        cout<<"ERROR\n";
        return ;
    }
    if(probing == hashValue(p)){
        return ;
    }
  }
}
float find(string stat,string stat2){
    int hash=hashValue(stat);
    for (int i = 0; i < n; i++)
    {
      if(J[(hash+i)%n].s1=="NILL"){
        return -1;
      }
      if(J[(hash+i)%n].s1==stat && J[(hash+i)%n].s2==stat2){
        return J[(hash+i)%n].t1;
      }
    }
    return -1;
}

  void QUEERY_JOURNEY(string l, float m, string st){
    int hash=hashValue(l);
    float itime=2500,stime=2500;
    string istation="NILL";
    for (int i = 0; i < n; i++)
    {
      if(J[(hash+i)%n].s1==l){
        if(J[(hash+i)%n].s2==st){
          if(J[(hash+i)%n].t1>=m && J[(hash+i)%n].t1<=stime){
            stime=J[(hash+i)%n].t1;
            istation=st;
          }
        }
        else{
          float in=find(J[(hash+i)%n].s2,st);
          float x=J[(hash+i)%n].t1;
          if(x>=m && x<=stime && in>=0 && in<itime){
            stime=x;
            itime=in;
            istation=J[(hash+i)%n].s2;
          }
        }
      }
      if(J[(hash+i)%n].s1=="NILL"){
        break;
      }
    }   
    if(istation=="NILL")cout<<"Error"<<endl;
    else{
      if(istation==st){
        cout<<stime<<endl;
      }
      else cout<<stime<<" "<<istation<<" "<<itime<<endl;
    }
  }
};

#endif
