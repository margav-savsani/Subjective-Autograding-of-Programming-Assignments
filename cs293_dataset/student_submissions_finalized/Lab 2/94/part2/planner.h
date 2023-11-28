#ifndef PLANNER_H
#define PLANNER_H
#include<cstring>
#include<iostream>
#include<cmath>
using namespace std;
#include<cstring>

struct store{
  int t1;
  char s2[32];
  int t2;
  store(){
    strcpy(s2,"");
    int t1=-1;
    int t2=-1;
  }
};
struct Station {
  // define suitable fields here
  char s[32];
  int n;
  store *ds;//data of station
  Station(){
    strcpy(s,"");
    ds=new store[8];
    n=0;
  }
  void add_station(char s2[],int t1,int t2){
    strcpy(ds[n].s2,s2);
    ds[n].t1=t1;
    ds[n].t2=t2;
    n++;
  }
  
};

struct Journey {
  // define suitable fields hered
  
  Station*ls;
  Journey(){
    ls=new Station[64];
  }
  int findFreeIndex(char key[]){
    int f=hashValue(key);
    if((strcmp(ls[f].s,"")==0)||(strcmp(ls[f].s,key)==0)) return f;
    else{
        f=(f+1)%64;
        while(!(f==hashValue(key))){
            if((strcmp(ls[f].s,"")==0)||(strcmp(ls[f].s,key)==0)) return f;
            f=(f+1)%64;
        }
        return -1;
    }

  }
  int hashValue(char key[]){
    double h=0;//hash value
    int i=0;
    int x=31;
    while(!(key[i]=='\0')){
        h=h*x+key[i];
        h=int(h)%143;
        i++;
    }
    h=h*0.5*(pow(5,0.5)-1);
    h=int((h-int(h))*64);
    int k=h;
    return k;

  }
  bool put(struct Station e){
    int f=findFreeIndex(e.s);
    if(f==-1) return false;
    else{
        if(ls[f].n==0){
          strcpy(ls[f].s,e.s);
          

        } 
        else{

        }
        return true;
    }
  }
  struct Station* get(char key[]){
    int f=hashValue(key);
    if(strcmp(ls[f].s, "") == 0) return NULL;
    else if(strcmp(ls[f].s,key) == 0) return &(ls[f]);
    else{
        f=(f+1)%64;
        while(!(f==hashValue(key))){
            if(strcmp(ls[f].s, "")==0) return NULL;
            if(strcmp(ls[f].s,key) == 0) return &(ls[f]);
            f=(f+1)%64;
        }
        return NULL;
    }

  }


  
};

struct Query{
  // define suitable fields here
  
};



#endif
