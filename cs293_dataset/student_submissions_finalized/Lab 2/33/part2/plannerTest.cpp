#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.cpp"
using namespace std;

void plannerHandler(Planner &planner){
    for(int i=0;i>=0;i++)
    {
        char input[32] ;
        cout<<">>>";
        cin>>input ;
        if(strcmp(input,"EXIT")==0){
            break ;
        }

        // ADD <station_one> <start_time> <station_two> <finish_time>
        if(strcmp(input,"ADD")==0){

            char station_one[32];
            cin>>station_one ;
            float start_time ;
            cin>>start_time ;
            char station_two[32];
            cin>>station_two ;
            float finish_time ;
            cin>>finish_time ;
            Journey input_data ;
            strcpy(input_data.starting.Name,station_one);
            strcpy(input_data.stopping.Name,station_two);
            input_data.starting_time = start_time ;
            input_data.stopping_time = finish_time ;
            int hashValueData = planner.hashValue(input_data.starting.Name);
            int freeIndexData = planner.findFreeIndex(input_data.starting.Name);
            cout<<"Hash Value : "<<hashValueData<<endl ;
            cout<<"Free Location : "<<freeIndexData<<endl ;
            if(freeIndexData>=0){
                planner.add_journey(input_data) ;
                cout<<"Journey Successfully Added !! "<<endl ;
            }
            else{
                cout<<"NO Available Space :("<<endl ;
            }
        }

        // QUERY_STATION <station_one> <start_time>
        else if(strcmp(input,"QUERY_STATION")==0){
            char station_one[32];
            cin>>station_one ;
            float start_time ;
            cin>>start_time ;
            if(!planner.check_Station(start_time,station_one)){
                cout<<"Today , No trains are currently running from station_one after the start_time ."<<endl ;
            }
            
        }
        // QUERY_JOURNEY <station_one> <start_time> <station_two>
        else if(strcmp("QUERY_JOURNEY",input)==0){
            char station_one[32] ;
            char station_two[32] ;
            float start_time ;
            cin>>station_one ;
            cin>>start_time ;
            cin>>station_two ;
            if(!planner.check_Journey(station_one,station_two,start_time)){
                cout<<"Today , No trains are currently running from station_one after the start_time ."<<endl ;
            }
        }
        else{
            cout<<input<<"Command NOT Found "<<endl ;
        }
    }    
}
void interactive()
{
  cout<<"Welcome to Planner \n";
  cout<<"";
  Planner planner;
  plannerHandler(planner);
  return ;
}

void automatic()
{
  Planner planner;
  freopen("sample_planner.txt", "r", stdin);

  int frequency[DICT_SIZE] = {0};

  char word[32];
  while(cin >> word){
    int hash = planner.hashValue(word);
    frequency[hash]++;
  }

  for(int i = 0; i < DICT_SIZE; i++){
    cout << frequency[i] << endl;
  }

}

int main()
{
  cout<<"Enter 1 for interactive testing and 0 for automatic "<<endl;
  int which;
  cin>>which;
  
  if(which == 1){
    interactive();
  }
  else{
    automatic();
  }
  return 0;
}
