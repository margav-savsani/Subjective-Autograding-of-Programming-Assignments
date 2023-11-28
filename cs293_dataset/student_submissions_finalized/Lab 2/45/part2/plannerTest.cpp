#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.h"
using namespace std;

/*

In interactive mode you can give commands 
  EXIT
  ADD <station_one> <start_time> <station_two> <finish_time>
  QUERY_STATION <station_one> <start_time>
  QUERY_JOURNEY <station_one> <start_time> <station_two>
*/

void plannerHandler(Planner &planner){
  for(int i=0;i>=0;i++)
  {
    string input;
    cout << ">>> " ;
    cin>>input;
    if(input=="EXIT"){
      break;
    }

    // ADD <station_one> <start_time> <station_two> <finish_time>
    if(input=="ADD"){

      string station1;
      cin >> station1;

      float start_time;
      cin >> start_time;

      string station2;
      cin >> station2;

      float finish_time;
      cin >> finish_time;
    
      planner.insert(station1,start_time,station2,finish_time);      
   
    }

    //QUERY_STATION <station_one> <start_time>
    if(input=="QUERY_STATION"){

        string station1;
        float start_time;

        cin>>station1;
        cin>>start_time;

        planner.stn_qry(station1,start_time);
    }

    //QUERY_JOURNEY <station_one> <start_time> <station_two>
    if(input=="QUERY_JOURNEY"){

        string station1;
        cin>>station1;

        float start_time;
        cin>>start_time;

        string station2;
        cin>>station2;

        jrny_qry y = planner.soonest(station1,start_time,station2);
        
        if(y.path_exist==false){
            cout<<"No train available "<<endl;
        }
        else{
            cout<<y.start<<" ";
            if(y.intmdt_loc!="direct"){
                cout<<y.intmdt_loc<<" "<<y.intmdt_start<<endl;
            }
            else{
                cout<<endl;
            }
        }                
    }

  }
}

void interactive()
{
  cout<<"Welcome to Rail Planner \n";
  cout<<"";
  Planner planner;
  plannerHandler(planner);
}


int main()
{
    cout<<"In interactive mode you can give the following commands \n"<<
    ">>>EXIT \n"">>>ADD <station_one> <start_time> <station_two> <finish_time> \n"<<
    ">>>QUERY_STATION <station_one> <start_time>  \n"<<
    ">>>QUERY_JOURNEY <station_one> <start_time> <station_two>"<<endl;
    interactive();
  
  return 0;
}