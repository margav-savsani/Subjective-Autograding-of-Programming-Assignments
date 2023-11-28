#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include <string.h>
#include"planner.cpp"
using namespace std;

int main(){
 Planner planner;
 while(true){
    char input[32];
    cout << ">>> " ;
    cin>>input;
    if(strcmp(input,"EXIT") == 0){
      break;
    }
    
    if(strcmp(input,"ADD")==0){
      char s1[32];
      cin>>s1;
      float t1;
      cin>>t1;
      char s2[32];
      cin>>s2;
      float t2;
      cin>>t2;
      Journey j;
      strcpy(j.sn1,s1);
      strcpy(j.sn2,s2);
      j.st=t1;
      j.ft=t2;
      int hashValueData = planner.hashValue(j.sn1);
      int freeIndexData = planner.findFreeIndex(j.sn1);
      if(freeIndexData >= 0){
        planner.put(j);
      }
      else{
        cout << "NO Available space " << endl;
      }
     }
    else if(strcmp(input,"QUERY_STATION")==0){
     char s1[32];
     cin>>s1;
     float st;
     cin>>st;
     planner.display_station(s1,st);
    }
    else if(strcmp(input,"QUERY_JOURNEY")==0){
      char s1[32];
      cin>>s1;
      float t1;
      cin>>t1;
      char s2[32];
      cin>>s2;
      planner.display_journey(s1,t1,s2);
  
    }
     else{
        cout << input << " not Found" << endl;
      }
   
   }
   return 0;}
