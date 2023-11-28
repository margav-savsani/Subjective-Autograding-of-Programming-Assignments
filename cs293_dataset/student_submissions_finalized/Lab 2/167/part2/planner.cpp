#include<iostream>
#include<string.h>
#include<cmath>
#include"planner.h"
using namespace std;


 
Planner :: Planner(){
	N=64;
	J=new Journey[64];
	for(int j=0;j<N;j++){
		J[j].stat=0;
	}
 };
  
int Planner:: hashValue(char stn[]){
  int h=0;
  string s=stn;
  for(int i=s.length()-1;i>=0;i--){
    h=h*5+stn[i];
  } 
   double x=(sqrt(5)-1)/2; //fibanacci
   double y=64*(h*x-int(h*x));
   h=y; 
   return h;
    
 }
  
int Planner :: findFreeIndex(char stn[]){
    int i=hashValue(stn); 
    while(1){   
     if(J[i].stat==0 ) return i;
     i=(i+1)%N;
    }
     return -1;
  }
  
bool Planner :: put(struct Journey l){
 int x=findFreeIndex(l.stn1.stn);
 if(x==-1)
   return false;
 else 
  J[x]=l;
  J[x].stat=1;
  return true;
}
 
 
void Planner :: get(char stn[],float k){
   int x=hashValue(stn);
   int a=0;
 
  for(int i=x;i<N;i++){
    if(strcmp(J[i].stn1.stn,stn)==0 && J[i].tm1>=k){
     a++;
     cout<<J[i].tm1<<" "<<J[i].stn2.stn<<endl;
    }
    }
    for(int j=0;j<x;j++){
     if(strcmp(J[j].stn1.stn,stn)==0 && J[j].tm1>=k){
     a++;
     cout<<J[j].tm1<<" "<<J[j].stn2.stn<<endl;
    }
    }
   if(a==0) cout<<"ERROR"<<endl;
 }
 
 
 
 void Planner:: soonest(char s1[],float k,char s2[]){
   int x=hashValue(s1);
   float t1=-1,d1;
    while(J[x].stat!=0){
    if(strcmp(J[x].stn1.stn,s1)==0 && strcmp(J[x].stn2.stn,s2)==0 && J[x].tm1>=k ){
       t1=J[x].tm1; break;       
      }
      x=(x+1)%N;
    }
    while(J[x].stat!=0){
    if(strcmp(J[x].stn1.stn,s1)==0 && strcmp(J[x].stn2.stn,s2)==0 && J[x].tm1>=k ){
       d1=J[x].tm1; 
       t1=min(d1,t1);       
      }
      x=(x+1)%N;
    }
    char s[32];
    int p,f;
    float d2=-1,t2,a=2400,h;
    for(int i=0;i<N;i++){
     if(strcmp(J[i].stn1.stn,s1)==0 && J[i].tm1>=k){
       t2=J[i].tm1;
       p=i;
       for(int j=0;j<N;j++)
       if(strcmp(J[j].stn1.stn,J[i].stn2.stn)==0 && strcmp(J[j].stn2.stn,s2)==0) { 
         f=j;                
         if(t1!=-1) t2=min(t1,t2);
          d2=J[j].tm1;
          a=min(d2,a); 
          if(a==d2) f=j;    
       }   
     }
    }
    
    if(d2!=-1)
     cout<<t2<<" "<<J[f].stn1.stn<<" "<<a<<endl;
    else if(t1!=-1 && d2==-1) cout<<t1<<endl;
    else cout<<"ERROR"<<endl;
    }
  
  
float Planner :: duration(struct Journey g){
 float x=g.tm1-g.tm2;//duration of the journey
    if(x<0) return (-x)+2400;
    else return x;
 }     
    
