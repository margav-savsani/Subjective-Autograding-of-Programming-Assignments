#include "string.h"
#include <bits/stdc++.h>
#include <iostream>
#include <cmath>
#include "planner.h"
using namespace std;

int Planner::hashValue(char station_one[]){
    long long unsigned int sum_ascii=0; //turning the string to int
    int x=33;//chosen
  double k=(sqrt(5)-1)/2;//fibonacci
    double ksum_asciimod1;
    double hashfunc;   // h(k)integral part of m*ksum_asciimod1 wanted
    int hashvalue;
    for(int i=0;station_one[i]!='\0';i++){
        sum_ascii=sum_ascii*x+int(station_one[i]);
    }
    ksum_asciimod1=fmod(k*sum_ascii,1);
    hashfunc=N* ksum_asciimod1;
    hashvalue=hashfunc;   //taking integer part alone
    return hashvalue;
}
int Planner::findFreeIndex(char station_one[]){
    int hv=hashValue(station_one);
    for(int i=hv;i>=0;i=(i+1)%N){
        if(A[i].value==0){
            A[i].value=1;
            return i;
        }
    }
    return -1;
}
Planner::Planner(){
        N=64;
        A=new Journey[64];
}
void Planner::func(Journey d){
    int i=hashValue(d.station_one);
    int kat=0;
    while((A[i].value!=0)){
        if((strcmp(d.station_one,A[i].station_one)==0)&&(A[i].start_time>=d.start_time)){
            kat=kat+1;   
            cout<<A[i].start_time<<"  "<<A[i].station_two<<endl;
            }
            i=(i+1)%64;
        }
    if(kat==0)cout<<"ERROR"<<endl;
}
void Planner::que(Journey d){
    int count1=0;
    int count2=0;
    int index1[30];  
    int index2[30];        
     
    int k=hashValue(d.station_one);
    for(int i=k; A[i].value!=0; i++){
        if(strcmp(A[i].station_one,d.station_one)==0){
            if (A[i].start_time >= d.start_time){
                index1[count1]=i;
                count1++;
            }
        }
    }  
    for(int i=0; A[i].value!=0; i++){
         if(strcmp(A[i].station_one,d.station_one)==0){
            if(A[i].start_time >= d.start_time){
                 index1[count1]=i;
                 count1++;               
            }
         } 
           
    }
    for(int p=0;p<count1;p++){ 
        if(strcmp(A[index1[p]].station_two,d.station_two)==0){
            index2[count2]=index1[p];
            count2++;
        }   
        else{
            for(int i=0;i<N;i++){
                if(A[i].value==0) continue;
                else{
                    if(strcmp(A[i].station_two,d.station_two)==0){
                        if(strcmp(A[index1[p]].station_two,A[i].station_one)==0){
                            index2[count2]=index1[p]; 
                            count2++;
                        }
                    } 
                }
            }  
        }
    }   
    for(int i=1;i<count2;i++){
        int k=index2[i];
        for(int j=i-1;j>=0;j--){
            if(A[index2[i]].start_time<A[index2[j]].start_time){   
            index2[j+1]=index2[j];     
            index2[j]=k;
            }
        }
    } 
    for(int j=0;j<count2;j++){
        if(strcmp(A[index2[j]].station_two,d.station_two)==0){
            cout<<A[index2[j]].start_time<<endl;  
            return;
        }
        else{
            for(int i=0;i<N;i++){
                if(A[i].value==0) continue;
                else{
                    if(strcmp(A[i].station_two,d.station_two)==0){
                        if(strcmp(A[index2[j]].station_two,A[i].station_one)==0){
                            cout<<A[index2[j]].start_time<<" "<<A[index2[j]].station_two<<" "<<A[i].start_time<<endl;
                            return;
                        }
                    }      
                }              
            } 
        }                     
    }
    
 cout<<"ERROR"<<endl;
 return;
 }


bool Planner::put(Journey e){
    if(findFreeIndex(e.station_one)==-1 )return false;
    else {
        A[findFreeIndex(e.station_one)]=e;
        A[findFreeIndex(e.station_one)].value=1;
        return true;
    }
}

