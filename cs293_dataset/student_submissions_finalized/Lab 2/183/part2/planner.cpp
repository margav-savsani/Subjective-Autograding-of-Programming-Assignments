#include <iostream>
#include <cmath>
#include "planner.h"
#include <cmath>
#include <string.h>
using namespace std;
int m=64;

int Planner::hashValue(char key[]){
     
     int x=33;
     string y=key;
     int l=y.length();
     long long int s_int=0;
     for(int i=l-1;i>=0;i--){            //calculating hashvalue for key assuming x=33
           s_int=x*s_int+int(key[i]);
           }
     double h=sqrt(5)-1/2;
     double a=s_int*h;
     long int r=a;
     int res=m*(a-r);
     return res;
}
int Planner::findFreeIndex(char key[]){
     
       int probe=hashValue(key);
       for(int i=probe;i<64;i++){
                      if(J[i].pre==0)return i;   //if free index is found return i
                      }
       for(int i=0;i<probe;i++){
                      if(J[i].pre) return i;}
       return -1;                      //else return -1
 } 
 Planner::Planner(){
       J=new Journey[64];}     //constructor
        

void Planner::display_station(char key[],float st){
      int probe=hashValue(key);
      int cnt=0;
      for(int i=probe;i<N;i++){
              if(J[i].pre==0) {if(cnt==0){cout<<"ERROR"<<endl;}return;}   //if station is not present then ERROR
              if((strcmp(J[i].sn1,key)==0)&&(st<=J[i].st)){cnt++;cout<<J[i].st<<" "<<J[i].sn2<<endl;}  //if station is found and having starting time >st then display starting time and destination
              }
      for(int i=0;i<probe;i++){
              if(J[i].pre==0) {if(cnt==0){cout<<"ERROR"<<endl;}return;}
              if((strcmp(J[i].sn1,key)==0)&&(st<=J[i].st)){cnt++;cout<<J[i].st<<" "<<J[i].sn2<<endl;}
              }
      if(cnt==0){cout<<"ERROR"<<endl;}   //if station is found but starting time< st then ERROR
      return;}

     
void Planner::display_journey(char key[],float st,char dest[]){
     int probe=hashValue(key);
     int cnt=0;
     int dir=0;
     float ftm=0;
     float stm=3.402823466E38; //highest  number float can store
     char interm[32];
     for(int i=probe;i<N;i++){
              if(J[i].pre==0) {if((cnt==0)&&(dir==0)){cout<<"ERROR"<<endl;return;}} //ERROR is station1 is not found 
              if((strcmp(J[i].sn1,key)==0)&&(st<=J[i].st)){
                 if(strcmp(J[i].sn2,dest)==0){if(J[i].st<stm){stm=J[i].st;dir++;}} //is station is found with destinatuon direct and if starting time is min upto now then change min
                 int probe1=hashValue(J[i].sn2);
                 for(int j=probe1;j<N;j++){
                 if(J[j].pre==0) {break;}
                 if((strcmp(J[j].sn1,J[i].sn2)==0)&&(strcmp(J[j].sn2,dest)==0)&&(J[j].st>=J[i].ft)) {
                     if(J[i].st<stm){ cnt++;dir=0;
                                      ftm=J[j].st;        //is station is found with intermediate station and if starting time is min upto now then change min                
                                      stm=J[i].st;
                                      strcpy(interm,J[j].sn1); }}}}}
     if(dir!=0){cout<<stm<<endl;return;}           //if direct is min                   
     else if(cnt==0){cout<<"ERROR"<<endl;return;}   //if nothing is found
     else{cout<<stm<<" "<<interm<<" "<<ftm<<endl;return;}}//if intermediate is min
               
               
      
bool Planner::put(struct Journey e){
           int probe=hashValue(e.sn1);
           for(int i=probe;i<N;i++){
                         if(J[i].pre==0) {J[i]=e;J[i].pre=1; return true;}    //if free index is found then insert e and update pre to 1(i.e it is occupied)
           }
           for(int i=0;i<probe;i++){
                        if(J[i].pre==0) {J[i]=e;J[i].pre=1; return true;}
           }
           return false;
}
