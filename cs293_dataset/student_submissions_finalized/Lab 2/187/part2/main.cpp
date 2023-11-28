#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include "planner.h"
using namespace std;

/*

In interactive mode you can give commands '
  EXIT
  ADD

  QUERY_STATION
  QUERY_JOURNEY 
*/

void PlanHandler(Planner &p1){
  for(int i=0;i>=0;i++)
  {
    string input;
    cin>>input;
    if(input=="QUIT"){
      break;
    }

    // ADD
    if(input == "ADD"){
      string stat1;
      cin >> stat1;
      float a;
      cin >> a;
      string stat2;
      cin >> stat2;
      float b;
      cin >> b;
      p1.add(stat1,a,stat2,b);
    }

    // QUERY_SELECTOR 
     if(input == "QUERY_STATION"){
      string s1;
      float a1;
      cin >> s1;
      cin >> a1;
      p1.querystation(s1,a1);
    }
     if(input == "QUERY_JOURNEY"){
      string s1;
      float t3;
      string s2;
      cin >> s1;
      cin >> t3;
      cin >> s2;
      p1.query_journey(s1,t3,s2);
      }
  }
}
void interactive()
{
  cout<<"Welcome to Dictionary \n";
  cout<<"";
  Planner plan;
  PlanHandler(plan);
}
int main()
{
    interactive();
     return 0;
}