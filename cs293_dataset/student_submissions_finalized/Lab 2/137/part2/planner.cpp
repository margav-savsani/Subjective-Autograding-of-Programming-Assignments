#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.h"
using namespace std;

void queryHandler(Planner &planner){
  for(int i=0; i>=0; i++)
  {
    char input[32];
    cin>>input;
    if(strcmp(input,"EXIT") == 0)
    {
      break;
    }
    
    //ADD <station_one> <start_time> <station_two> <finish_time>
    else if(strcmp(input,"ADD") == 0)
    {
      char inputkey1[32],inputkey2[32];
      float start, end;
      cin>>inputkey1>>start>>inputkey2>>end;
      Journey data;
      strcpy(data.s1.B,inputkey1);
      strcpy(data.s2.B,inputkey2);
      data.start_time = start;
      data.finish_time = end; 
      if(planner.findFreeIndex(data.s1.B) >= 0)
      {
        planner.put(data);
      }
    }

    //QUERY_STATION <station_one> <start_time>
    else if(strcmp(input, "QUERY_STATION") == 0)
    {
      int count = 0;
      struct Query *E;
      char inputkey[32];
      float start;
      cin>>inputkey>>start;
      planner.query_station(inputkey, E, count, start);
      if(count == 0)
      {
        cout<<"ERROR"<<endl;
      }
      else
      {
        for(int i = 0; i<count; i++)
        {
          cout<<E[i].start_time<<" "<<E[i].s.B<<endl;
        }
      }
    }

    //QUERY_JOURNEY <station_one> <start_time> <station_two>
    else if(strcmp(input, "QUERY_JOURNEY") == 0)
    {
      char inputkey1[32],inputkey2[32];
      float start;
      cin>>inputkey1>>start>>inputkey2;
      char outputkey[32];
      float start1, start2;
      int n = planner.query_journey(inputkey1, start, inputkey2, outputkey, start1, start2);
      if(n == 0)
      {
        cout<<start1<<endl;
      }
      else if(n == 1)
      {
        cout<<"ERROR: FINISH TIME OF FIRST JOURNEY IS AFTER THE START TIME OF SECOND JOURNEY";
      }
      else if(n == 2)
      {
        cout<<start1<<" "<<outputkey<<" "<<start2<<endl;
      }
      else if(n == 3)
      {
        cout<<"ERROR: CURRENTLY NO TRAINS AVAILABLE CONNECTING "<<inputkey1<<" TO "<<inputkey2<<endl;
      }
    }
  }
}

void interactive()
{
  Planner planner;
  queryHandler(planner);
}

int main()
{
  interactive();
  /*else{
    automatic();
  }*/
  return 0;
}