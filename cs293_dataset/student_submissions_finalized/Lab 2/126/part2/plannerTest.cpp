#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include "planner.cpp"
using namespace std;

/*
In interactive mode you can give commands '
  EXIT
  ADD <station_one> <start_time> <station_two> <finish_time>
  QUERY_STATION <station_one> <start_time>
  QUERY_JOURNEY <station_one> <start_time> <station_two>

*/

void dictionaryHandler(Dictionary &dictionary){
  for(int i=0;i>=0;i++)
  {
    char input[32];
    cout << ">>> " ;
    cin>>input;
    if(strcmp(input,"EXIT") == 0){
      break;
    }

    // INS <key> <value>
    if(strcmp(input,"ADD") == 0){

      string inputKey;
      cin >> inputKey;
      float start_time;
      cin >> start_time;
      string inputKey1;
      cin>>inputKey1;
      float end_time;
      cin>>end_time;
      Entry data;
      data.key=inputKey;
      if(dictionary.put(data, start_time, inputKey1, end_time))
        cout<<"Successfully added the journey"<<endl;
      else{
        cout<<"No available space"<<endl;
      }
    }
    //QUERY_STATION
    else if(strcmp(input, "QUERY_STATION")==0){
        string inputKey;
        cin>>inputKey;
        float start_time;
        cin>>start_time;
        if(!dictionary.getAfterTime(inputKey, start_time)){
            cout<<"Sorry! No available journeys from this station"<<endl;
        }
    }
    //QUERY_JOURNEY
    else if(strcmp(input, "QUERY_JOURNEY")==0){
        string inputKey;cin>>inputKey;
        float start_time;
        cin>>start_time;
        string inputKey1;
        cin>>inputKey1;
        if(!dictionary.getJourney(inputKey, start_time, inputKey1, 1, 1)){
            cout<<"No journeys available"<<endl;
        }
    }
  }
}

void interactive()
{
  cout<<"Enter ADD to add train journeys, QUERY_STATION to check journeys from a certain station after a given time and EXIT to quit \n";
  cout<<"";
  Dictionary dictionary;
  dictionaryHandler(dictionary);
}


int main()
{
  cout<<"Welcome to the train scheduling service"<<endl;
  
    interactive();
  return 0;
}
