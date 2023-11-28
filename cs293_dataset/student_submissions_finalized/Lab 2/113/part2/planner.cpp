#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"planner.h"
using namespace std;

//this is just standard implementation to make interactive mode supporting given queries

int main(){

  cout<<"Welcome to RAIL PLANNER \n";
  cout<<"";
  Planner p;

  for(int i=0;i>=0;i++)
  {
    string input;
    cout << ">>> " ;
    cin>>input;
    if(input == "EXIT"){
      break;
    }

    if(input == "ADD"){

      Journey *e = new Journey;   //manually creating the journey pointer and passing it to add function
      cin >> e->start >> e->start_time >> e->finish >> e->finish_time;
      if (p.add(e)){
        cout << "Added Successfully" << endl;
      }
    }

    else if(input == "QUERY_JOURNEY"){
      string start,finish;
      float start_time;
      cin >> start >> start_time >> finish;
      p.optimal_jrny(start,start_time,finish);
    }

    else if(input == "QUERY_STATION"){
      string start;
      float start_time;
      cin >> start >> start_time;
      p.station(start, start_time);
    }
  }
}