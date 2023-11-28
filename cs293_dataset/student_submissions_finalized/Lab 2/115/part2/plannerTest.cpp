#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.h"
#include"planner.cpp"
using namespace std;

/*
In interactive mode you can give commands '
  EXIT
  ADD <station_one> <start_time> <station_two> <finish_time>
  QUERY_STATION <station_one> <start_time>
  QUERY_JOURNEY <station_one> <start_time> <station_two>
*/

void PlannerHandler(Planner &planner){
  for(int i=0;i>=0;i++)
  {
    char input[32];
    cout << ">>> " ;
    cin>>input;
    if(strcmp(input,"EXIT") == 0){
      break;
    }

    // ADD <station_one> <start_time> <station_two> <finish_time>
    if(strcmp(input,"ADD") == 0){
      char inputKey[32];
      cin >> inputKey;
      float t1,t2;
      cin >> t1;
      char input2Key[32];
      cin >> input2Key;
      cin >> t2;
      Station S1,S2;
      Train T;
      for(int i=0;i<32;i++)
      {
        S1.Station_Name[i]=inputKey[i];
        S2.Station_Name[i]=input2Key[i];
      }
      T.Station_1=S1;
      T.Station_2=S2;
      T.Start_time=t1;
      T.Finish_time=t2;
      int hashValueData = planner.hashValue(T.Station_1.Station_Name);
      cout << "Hash Value: " << hashValueData << endl;
      bool b=planner.add(T);
      if(b){
        cout << "Successfully Added " << endl;
      }
      else{
        cout << "NO Available space " << endl;
      }
    }

    // QUERY_STATION <station_one> <start_time>
    else if(strcmp(input, "QUERY_STATION") == 0){
      char inputKey[32];
      cin >> inputKey;
      float time;
      cin >> time;
      Station S;
      strcpy(S.Station_Name,inputKey);
      planner.Query_Station(S,time);
    }

    // QUERY_JOURNEY <station_one> <start_time> <station_two>
    else if(strcmp(input,"QUERY_JOURNEY") == 0){
      char inputKey[32];
      cin >> inputKey;
      float time;
      cin>> time;
      char input2Key[32];
      cin >> input2Key;
      My_Journey J;
      for(int i=0;i<32;i++)
      {
        J.Station_1.Station_Name[i]=inputKey[i];
        J.Station_2.Station_Name[i]=input2Key[i];
      }
      J.Start_time=time;
      Train* b=planner.Query_Journey(J);
      Train* c=NULL;
      bool direct=false;
      if(b==NULL)
      {
        cout << "ERROR\n";
      }
      else
      {
        if(planner.check(input2Key,b->Station_2.Station_Name))
        {
          direct=true;
        }
        else
        {
          for(int i=0;i<32;i++)
          {
            J.Station_1.Station_Name[i]=b->Station_2.Station_Name[i];
          }
          J.Start_time=b->Finish_time;
          c=planner.Query_Direct_Journey(J);
        }
        if(b != NULL && direct){//if its direct
          cout << b->Start_time<< endl;
        }
        else if(b !=NULL)
        {//if it is not direct
          cout << b->Start_time <<" "<<c->Station_1.Station_Name<<" "<<c->Start_time<<endl;
        }
      }
    }
  }
}
void interactive()
{
  Planner planner;
  PlannerHandler(planner);
}

int main()
{
  interactive();
  return 0;
}
