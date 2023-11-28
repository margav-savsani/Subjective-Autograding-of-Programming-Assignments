#include <iostream>
#ifndef PLANNER_H
#define PLANNER_H
#include <string.h>
#include <cmath>
using namespace std;

struct Journey {
  string ss;
  string es;
  float st;
  float et;

};


class Planner {
  Journey* A;
  int n;
  public:
  Planner(){
    n=64;
    A = new Journey[n];//ARRAY IS CREATED
    for(int i=0;i<n;i++){
      A[i].ss = "NULL";//INITIALIZED THE GARBAGE VALUE TO ARRAY
    }
  }
  int hashValue(string key){
        int a = 0;
        int b = 37;
        double c = (sqrt(5)-1)/2;
        for(int i=key.length()-1;i>=0;i--){
                a = int(key[i])+a*b;
        }
        double fractpart,intpart;
        fractpart = abs(modf(c*a,&intpart));
        return int(n*fractpart);
  }

int findFreeIndex(string key){
	int i=hashValue(key);
    	while(A[i].ss != "NULL"){
        	i=(i+1)%n;
            	if(i == hashValue(key)) return -1;
    	}
    return i;
}

void ADD(string a,float x,string b,float y){//ADDING A JOURNEY
  int position = findFreeIndex(a);
  if(position != -1){
    Journey J;
    J.ss = a;
    J.st = x;
    J.es = b;
    J.et = y;
    A[position] = J;
  }
}
void Q_S(string p,float q){
  int i=hashValue(p),c=0;
  
  while(A[i].ss != "NULL"){
    if(A[i].ss == p){
    cout<<A[i].st<<" "<<A[i].es<<endl;
    c++;
    } 
    i=(i+1)%n;
    if(i == hashValue(p) && c==0){
        cout<<"ERROR\n";
        return ;
    }
    if(i == hashValue(p)){
        return ;
    }
  }
}
float find(string stat,string stat2){
    int hash=hashValue(stat);
    for (int i = 0; i < n; i++)
    {
      if(A[(hash+i)%n].ss=="NILL"){
        return -1;
      }
      if(A[(hash+i)%n].ss==stat && A[(hash+i)%n].es==stat2){
        return A[(hash+i)%n].st;
      }
    }
    return -1;
}

  void Q_J(string l, float m, string sf){
    int hash=hashValue(l);
    float itime=2500,stime=2500;
    string istation="NILL";
    for (int i = 0; i < n; i++)
    {
      if(A[(hash+i)%n].ss==l){
        if(A[(hash+i)%n].es==sf){
          if(A[(hash+i)%n].st>=m && A[(hash+i)%n].st<=stime){
            stime=A[(hash+i)%n].st;
            istation=sf;
          }
        }
        else{
          float in=find(A[(hash+i)%n].es,sf);
          float x=A[(hash+i)%n].st;
          if(x>=m && x<=stime && in>=0 && in<itime){
            stime=x;
            itime=in;
            istation=A[(hash+i)%n].es;
          }
        }
      }
      if(A[(hash+i)%n].ss=="NILL"){
        break;
      }
    }   
    if(istation=="NILL")cout<<"Error"<<endl;
    else{
      if(istation==sf){
        cout<<stime<<endl;
      }
      else cout<<stime<<" "<<istation<<" "<<itime<<endl;
    }
  }
};

#endif
