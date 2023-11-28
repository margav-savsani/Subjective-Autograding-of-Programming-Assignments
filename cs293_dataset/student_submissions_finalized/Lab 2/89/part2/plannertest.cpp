#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.h"
using namespace std;


void railwayplanner(Planner &planner){

for(int i=0;i>=0;i++)
 {
    char input[32];
    cin>>input;
    
   if(strcmp(input,"EXIT") == 0){
      break;
     }
     
  else if(strcmp(input,"ADD") == 0){
   
      Journey data;
      
      char stn1[32];
      cin>>stn1;
       strcpy(data.s1.stn,stn1);   
      float time1;
      cin>>time1;
   
      char stn2[32];
      cin>>stn2;
   
      float time2;
      cin>>time2;
    
     strcpy(data.s1.stn,stn1);
     data.t1=time1;
     strcpy(data.s2.stn,stn2);
     data.t2=time2;

 int hash=planner.hashValue(data.s1.stn);
 int freeIndex = planner.findFreeIndex(data.s1.stn);
      cout << "Hash Value: " << hash<< endl;
      cout << "Free Location: "<< freeIndex << endl;
      if(freeIndex >= 0){
        planner.add(data);
        cout << "Successfully Added " << endl;
      }
      else{
        cout << "NO Available space " << endl;
      }   
   
   }
   
  else if(strcmp(input,"QUERY_STATION") == 0){              
      
      char s[32];
      cin>>s;
      float time;
      cin>>time;
      
      planner.stnlist(s,time);
     }
     
   else if(strcmp(input,"QUERY_JOURNEY") == 0){
      
      char stn1[32];
      cin>>stn1;
      float time;
      cin>>time;
      char stn2[32];
      cin>>stn2;
      
     planner.soonest(stn1,time,stn2);
   }
   
 }     


} 
 
 
 void interactive()
{
  cout<<"Welcome to RailwayPlanner \n";
  cout<<"";
  Planner planner;
  railwayplanner(planner);
}
   
int main()
{
  
    interactive();
    return 0;
}               
    
                 
