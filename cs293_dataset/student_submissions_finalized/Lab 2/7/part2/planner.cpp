#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.h"
using namespace std;

/*

In interactive mode you can give commands '
  ADD <station_one> <start_time> <station_two> <finish_time>
  QUERY_STATION <station_one> <start_time>
  QUERY_JOURNEY <station_one> <start_time> <station_two>
  EXIT

*/

void plannerhandler(Planner &p){
  for(int i=0;i>=0;i++)
  {
    char input[32];
    cout << ">>> " ;
    cin>>input;
    if(strcmp(input,"EXIT") == 0){
      break;
    }

    
    if(strcmp(input,"ADD") == 0){

        string station_one;
        cin >> station_one;
        
        float start_time;
        cin >> start_time;
        
        string station_two;
        cin >> station_two;
        
        float finish_time;
        cin>> finish_time;
        
        
        
        
        

        p.dictionary(station_one,start_time,station_two,finish_time);
        

    }
      
      

    // QUERY_STATION <station_one> <start_time>
    if(strcmp(input, "QUERY_STATION") == 0){
        
        string station_one;
        cin >> station_one;
        
        float start_time;
        cin >> start_time;
        
        
        p.query_station(station_one,start_time);
        

    }

    // QUERY_JOURNEY <station_one> <start_time> <station_two>
    else if(strcmp(input,"QUERY_JOURNEY") == 0){
      
        string station_one;
        cin >> station_one;
        
        float start_time;
        cin >> start_time;
        
        string station_two;
        cin >> station_two;
        
        
        p.query_journey(station_one,start_time,station_two);
        
    }
  }
}

//void automatic()
//{
//  Planner planner;
//  freopen("sample-planner.txt", "r", stdin);
//  plannerhandler(planner);
//  // TODO
//  int frequency[DICT_SIZE] = {0};
//
//    string word;
//    while(cin >> word){
//    int hash = dictionary.hashValue(word);
//    frequency[hash]++;
//  }
//
//  for(int i = 0; i < DICT_SIZE; i++){
//    cout << frequency[i] << endl;
//  }

//}

void interactive()
{
  cout<<"Welcome to Rail Planner \n";
  cout<<"";
  Planner p;
  plannerhandler(p);
}


int main()
{
//  cout<<"Enter 1 for interactive testing and 0 for automatic"<<endl;
//  int which;
//  cin>>which;
//
//  if(which == 1){
//    interactive();
//  }
//  else{
//    automatic();
//  }
    
    interactive();
    
  return 0;
}
