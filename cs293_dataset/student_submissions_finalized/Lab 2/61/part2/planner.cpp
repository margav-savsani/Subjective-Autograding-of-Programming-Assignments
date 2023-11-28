#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<cmath>
#include"planner.h"
//Note for TA: I have not explicitly used the dictionary created in the inlab. Instead, I have implemented the dictionary within the planner class itself.
float frac(float a){
    return a-floor(a);
}
    
     int planner::hashValue(string s){ 
    int a,x=33;
    float value=int(s[0]),f=(pow(5,0.5)-1)/2;
   
    for(int i=0;i<s.length();i++){
        
        a=int(s[i]);
        value=frac(frac(((value*x)*f))+frac(a));
        i++;

    }
    return value;
    
 }
   bool planner::findlocation_insert(train t){
         int hash=hashValue(t.stn1);
         int i=hash;
         while(!stations[i].null && stations[i].name!=t.stn1 && i!=hash-1){
            i=(i+1)%N;
        
         }  
         if(i==hash-1){
            return false;
         }    
         else if(stations[i].null){
            stations[i].null=false;
            stations[i].name=t.stn1;
            stations[i].trains.push_back(t);
            return true;
         } 
         else{
            stations[i].trains.push_back(t);
            return true;
         }  
         
              
    }
  
  vector<train> planner::query1(string stn, int start){       
        vector<train> ans;
        int hash=hashValue(stn);
        int i=hash;
        while(!stations[i].null && stations[i].name!=stn && i!=hash-1){
            i=(i+1)%N;
         }  
         if(stations[i].name==stn){
            for (auto tr:stations[i].trains){
                if(tr.st_time>=start){
                    ans.push_back(tr);
                    
                    
                }
            }
         } 
         return ans;   
                      //searches for the station name
                                        //if it exists, then stores all the entries with value gr bbeater than given time in a vector and returns i
    }
    void planner::query2(string begin,int start,string end){
        train ans,ans_p;
        bool indirect=false,direct=false;
        vector<struct train> set1=query1(begin,start),set2;
        int min=100000;
        for (auto tr:set1){
                if(tr.st_time>=start){
                    set2.push_back(tr);
                    if(tr.stn2==end && tr.end_time-tr.st_time<=min){
                        ans=tr;
                        direct=true;
                        min=tr.st_time;
                    }
                }
        }
        vector<struct train> v1;
        for(auto tr:set2){
            v1=query1(tr.stn2,tr.end_time);
            for(auto tr2:v1){
                if(tr2.stn2==end && tr.st_time<=min){
                    ans_p=tr;
                    ans=tr2;
                    indirect=true;
                    direct=false;
                    min=tr2.end_time-tr.st_time;

                }
            }
        }
        if(!indirect && !direct){
          cout<<"ERROR\n";
        }
        if(indirect){
            cout<<ans_p.st_time<<" ";
            cout<<ans.stn1<<" ";
            cout<<ans.st_time<<endl;
            return;
        }
        if(direct){
          cout<<ans.st_time<<endl;
        }
    }
    
