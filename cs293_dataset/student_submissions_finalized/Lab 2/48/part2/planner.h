#ifndef PLANNER_H
#define PLANNER_H
#include<iostream>
#include<cmath>
using namespace std;
#include<string.h>
#include<vector>
//struct of station
struct Station {
    string station;   
};
//struct of journey
struct Journey {
    Station s1;
    Station s2;
    int starttime;
    int endtime;
    bool occupied;
    Journey(){
        occupied=false;
    }
};
//class planner
class Planner {
    int N;
    int num;
    Journey* j;
    public:
    Planner(){
        N=64;
        num=0;
        j= new Journey[N];        
    }
    int hashValue(string s){
    double long fib=(sqrt(5)-1)/2;
    unsigned int hashvalue=0;
    for(int i=s.length()-1;i>=0;i--){
        hashvalue=hashvalue*37+s[i];
    }
    double long k=hashvalue*fib;
    double intPart;
    double fractPart = modf(k, &intPart);
    unsigned long long ans=N*(fractPart);
    return ans;
    }
    //ADD implementation as in the document
    void ADD(string key1,int time1,string key2,int time2){
        int probe=hashValue(key1);
        while(j[probe].occupied){
            probe=(probe+1)%N;
        }
        j[probe].s1.station=key1;
        j[probe].s2.station=key2;
        j[probe].starttime=time1;
        j[probe].endtime=time2;
        j[probe].occupied=true;
        num++;
    }
    //query station implementation as said in the document
    //print all journies with greater than or equal to the give time
    void QUERY_STATION(string key1,int time1){
        int count=0;
        int probe=hashValue(key1);
        for(int i=0;i<N;i++){
            if(j[(i+probe)%N].s1.station==key1 && j[(i+probe)%N].starttime>=time1){
                cout<<j[(i+probe)%N].starttime<<" "<<j[(i+probe)%N].s2.station<<" "<<endl;
                count++;
            }
        }
        if(count==0) cout<<"station not available"<<endl;
    }
    //query journey as said in the document
    //leat sooner time is fined 
    //first direct one is checked 
    //one stop ones also checked
    //both times are compared.
    void QUERY_JOURNEY(string key1,int time1,string key2){
        int s=0;
        string s1="\0";
        int kp=-1;
        for(int i=0;i<N;i++){
            if(j[i].s1.station==key1 && j[i].s2.station==key2 && j[i].starttime>=time1) s=j[i].starttime;
        } 
        for(int i=0;i<N;i++){
            if(j[i].s1.station==key1 && j[i].s2.station!=key2 && j[i].starttime>=time1){
                for(int l=0;l<N;l++){
                    if(j[l].s1.station==j[i].s2.station && j[l].s2.station==key2){
                        if(s==0) {s=j[i].starttime;s1=j[l].s1.station,kp=j[l].endtime;}
                        if(s>j[i].starttime) {s=j[i].starttime;s1=j[l].s1.station,kp=j[l].endtime;}
                    }                
                }
            }
        }
        if(s1!="\0" && kp!=-1 & s!=0) cout<<s<<" "<<s1<<" "<<kp<<endl;
        if(s!=0 && s1=="\0" && kp==-1) cout<<s<<endl;
        if(s==0) cout<<"no path exists"<<endl;

    }    

};

#endif