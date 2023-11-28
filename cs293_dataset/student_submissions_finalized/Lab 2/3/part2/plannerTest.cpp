#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include<math.h>
#include"planner.cpp"
#include"planner.h"

using namespace std;

void PlannerHandler(Planner &Planner){
  for(int i=0;i>=0;i++)
  {
    char input[100];
    cout << ">>> " ;
    cin>>input;
    if(strcmp(input,"EXIT") == 0){
      break;
    }

    // ADD <station_one> <start_time> <station_two> <finish_time>
    if(strcmp(input,"ADD") == 0){

      char sn1[32];
      cin >> sn1;
      int st;
      cin >> st;
      char sn2[32];
      cin >> sn2;
      int ft;
      cin >> ft;
      int id1 =Planner.stations.find(sn1);
      if(id1==-1)
      {
        Planner.stations.QInsert(sn1);
        id1 = Planner.stations.size()-1+10;
      }

      int id2 =Planner.stations.find(sn2);
      if(id2==-1)
      {
        Planner.stations.QInsert(sn2);
        id2 = Planner.stations.size()-1+10;
      }
      Journey route;
      strcpy(route.start.name,sn1);
      strcpy(route.start.name,sn1);
      route.st=st;
      route.ft=ft;
      Entry data;
      data.key=*Planner.makekey(route);
      int hashValueData = Planner.railways.hashValue(Planner.makekey(route));
      int freeIndexData = Planner.railways.findFreeIndex(Planner.makekey(route));
      if(freeIndexData >= 0){
        Planner.railways.put(data);
        Planner.paths[freeIndexData] = route;
      }
    }

    // QUERY_STATION <station_one> <start_time>
    else if(strcmp(input, "QUERY_STATION") == 0){
      char sn1[32];
      cin >> sn1;
      int st;
      cin >> st;
      int id1 = Planner.stations.find(sn1);
      if(id1==-1)
      cout<<"train doest exits";
      else
      {
      char k1[13];
      sprintf(k1,"%f", id1*pow(10,4)+ st);
      for(int i=0;i<DICT_SIZE;i++)
      {
        if((Planner.railways.A[i].key[0]==k1[0])&&(Planner.railways.A[i].key[1]==k1[1]) && (Planner.railways.A[i].key[2]*1000+Planner.railways.A[i].key[3]*100+Planner.railways.A[i].key[4]*10+Planner.railways.A[i].key[5]>=k1[2]*1000+k1[3]*100+k1[4]*10+k1[5]))
        {
          cout<<Planner.paths[i].st<<endl;
        }
      }

      }
    }

    // QUERY_JOURNEY <station_one> <start_time> <station_two>
    else if(strcmp(input,"QUERY_JOURNEY") == 0){
      char sn1[32];
      cin >> sn1;
      int st;
      cin >> st;
      char sn2[32];
      int id1 = Planner.stations.find(sn1);
      int id2 = Planner.stations.find(sn2);
      char k1[13];
      sprintf(k1,"%f", id1*pow(10,6)+ st*pow(10,2)+id2);
      for(int i=0;i<DICT_SIZE;i++)
      {
        if(id1==-1 || id2 ==-1)
        {
          cout<<"there is some error";
        }
        else
        {
          if((Planner.railways.A[i].key[0]==k1[0])&&(Planner.railways.A[i].key[1]==k1[1]) && (Planner.railways.A[i].key[2]*1000+Planner.railways.A[i].key[3]*100+Planner.railways.A[i].key[4]*10+Planner.railways.A[i].key[5]>=k1[2]*1000+k1[3]*100+k1[4]*10+k1[5]))
          {
            if((Planner.railways.A[i].key[5]==k1[5])&&(Planner.railways.A[i].key[6]==k1[6]))
            {
              cout<<Planner.paths[i].st<<endl;
            }
            else
            {
              char k2[13];
              for(int i =0;i<6;i++)
              {
                k2[i]=k1[i+6];
              }
              for(int i =6;i<12;i++)
              {
                k2[i]=k1[i-6];
              }
              for(int i=0;i<DICT_SIZE;i++)
              {
                if(Planner.com1(k2,Planner.paths[i]) != -1)
                {

                }
              }

            }
          }
        


        }
      
      }
    }
    
  }
}

void interactive()
{
  cout<<"Welcome to planner \n";
  cout<<"";
  Planner Rsystem;
  PlannerHandler(Rsystem);
}

int main()
{
    interactive();
}
