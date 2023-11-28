#include<iostream>
using namespace std;
#include<fstream>
#include "planner.h"

int main(){
   fstream f;
   f.open("input3.in");
   string s;
   Query* a;
   a=new Query[20];
   int i=0;
   while(f>>s){
      if(s=="ADD"){
         a[i].operation="ADD";
         f>>s;
         a[i].s1=s;
         float t;
         f>>t;
         a[i].t1=t;
         f>>s;
         a[i].s2=s;
         f>>t;
         a[i].t2=t;
         i++;
      }
      else if(s=="QUERY_STATION"){
         a[i].operation="QUERY_STATION";
         f>>s;
         a[i].s1=s;
         float t;
         f>>t;
         a[i].t1=t;
         i++;
      }
      else if(s=="QUERY_JOURNEY"){
         a[i].operation="QUERY_JOURNEY";
         f>>s;
         a[i].s1=s;
         float t;
         f>>t;
         a[i].t1=t;
         f>>s;
         a[i].s2=s;
         i++;
      }
      else if(s=="EXIT"){
         a[i].operation="EXIT";
         break;
      }
   }
   Planner P(a);
   P.Handling_queries();
}
