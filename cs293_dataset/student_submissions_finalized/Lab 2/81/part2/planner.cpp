#include <bits/stdc++.h>
#include<string.h>
using namespace std;
#include "planner.h"
int indexofSmallestElement(float array[], int size)
{    int index = 0;
	for (int i = 1; i < size; i++)
	{if (array[i] < array[index])
     index = i;
	}
	return index;
}
int Planner::hashValue(char key[]){
    int hash=0;
    int x=31;
    long x_pow = 1;
    int i=0;
    while(int(key[i]!=0)) {
        hash = (hash + (int(key[i])) * x_pow);
        x_pow = (x_pow * x) % N;// to sustain the over flow
        i++;
    }
    double a=0.618;
    hash=N*((hash*a)-floor(hash*a));
    return floor(hash);
}
int Planner::findFreeIndex(char key[]){
    int probe;
    probe=hashValue(key);
    int check=0;
    while(journey[probe].arri!=0){
        probe=(probe+1)%N;
        check++;
        if(check==N){return -1;}
    }
    return probe;
}
bool Planner::Query_Station(char key[],float time){
int probe;
probe=hashValue(key);
int check=0;int present=0;
    while(journey[probe].arri!=0){
if(strcmp(key,journey[probe].from)==0){
    if(journey[probe].arri>=time){cout<<"Starts at "<<journey[probe].arri<<" destination "<<journey[probe].to<<endl;present++;}
}
    probe=(probe+1)%N;
    check++;
    if(check==N){break;}
    }
if(present==0)return false;
else return true;
}
bool Planner::Query_Journey(char key1[],float time,char key2[]){
int probe;
Journey j[N];
float time1[N];
probe=hashValue(key1);
int check=0;int present=0;
    while(journey[probe].arri!=0){
if(strcmp(key1,journey[probe].from)==0){
    if(journey[probe].arri>=time){
        if(strcmp(key2,journey[probe].to)==0){time1[present]=(journey[probe].dept-journey[probe].arri);
        j[present]=journey[probe];present++;}
        else {int probe1;
             probe1=hashValue(journey[probe].to);
             while(journey[probe1].arri!=0){
             if(strcmp(journey[probe].to,journey[probe1].from)==0){
             if(journey[probe1].arri>=journey[probe].dept){
             if(strcmp(key2,journey[probe1].to)==0){time1[present]=(journey[probe1].dept-journey[probe].arri);
             j[present]=journey[probe1];present++;}}}
             probe1=(probe1+1)%N;}
             }}}
probe=(probe+1)%N;
check++;
if(check==N){break;}
    }
int  x=indexofSmallestElement(time1,present);
if(strcmp(j[x].from,key1)==0){cout<<"From "<<key1<<" at "<<j[x].arri<<" to "<<key2<<" "<<time1[x]<<" hrs"<<endl;;}
else{cout<<"From "<<key1<<" to "<<j[x].from<<" to "<<key2<<" "<<time1[x]<<" hrs"<<endl;}


if(present==0)return false;
else return true;
}
bool Planner::insert(Journey j){
if(findFreeIndex(j.from)!=-1){
    int x;
     x=findFreeIndex(j.from);
    journey[x].arri=j.arri;
    journey[x].from=j.from;
    journey[x].to=j.to;
    journey[x].dept=j.dept;
    return true;}
    else return false;
}
