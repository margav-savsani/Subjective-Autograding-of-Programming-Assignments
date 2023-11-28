#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.cpp"
using namespace std;

//Handles queries interactively, enter commands one by one
void queryHandler(){
    Planner planner;

    for(int i=0;i>=0;i++)
  {
    char input[32];
    cout << ">>> " ;
    cin>>input;
    if(strcmp(input,"EXIT") == 0){
      break;
    }
    // INS <key> <value>
    else if(strcmp(input,"ADD") == 0){

      char start_station[32];
      cin >> start_station;
      float stime;
      cin >> stime;
      char end_station[32];
      cin >> end_station;
      float etime;
      cin >> etime;

      planner.add(start_station, stime, end_station, etime);

    }
    else if(strcmp(input,"QUERY_STATION") == 0){
      char start_station[32];
      cin >> start_station;
      int stime;
      cin >> stime;
      planner.query_station(start_station, stime);
    }

    else if(strcmp(input,"QUERY_JOURNEY") == 0){

      char start_station[32];
      cin >> start_station;
      int stime;
      cin >> stime;
      char end_station[32];
      cin >> end_station;

      planner.query_journey(start_station, stime, end_station);

    }
    // if incorrect command entered, show error
    else{
      cout<<"Incorrect command, try again" << endl;
      continue;
    }
  }
}
void interactive()
{
  cout<<"Rail Planner System: \n";
  cout<<"";
  queryHandler();
}

// runs program automatically, taking input from a txt file, and giving desired output
void automatic()
{
  Planner planner;

  // enter name of file here
  freopen("sample-planner.txt", "r", stdin);
  //
  
  char input[32];
  while(cin >> input){
    if(strcmp(input,"EXIT") == 0){
      break;
    }
    // INS <key> <value>
    else if(strcmp(input,"ADD") == 0){

      char start_station[32];
      cin >> start_station;
      float stime;
      cin >> stime;
      char end_station[32];
      cin >> end_station;
      float etime;
      cin >> etime;

      planner.add(start_station, stime, end_station, etime);

    }
    else if(strcmp(input,"QUERY_STATION") == 0){
      char start_station[32];
      cin >> start_station;
      int stime;
      cin >> stime;
      planner.query_station(start_station, stime);
    }

    else if(strcmp(input,"QUERY_JOURNEY") == 0){

      char start_station[32];
      cin >> start_station;
      int stime;
      cin >> stime;
      char end_station[32];
      cin >> end_station;

      planner.query_journey(start_station, stime, end_station);

    }

    else{
      cout<<"Incorrect command, try again" << endl;
      continue;
    }
  }
}

int main()
{
  cout<<"Enter 1 for interactive testing and 0 for automatic:"<<endl;
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
