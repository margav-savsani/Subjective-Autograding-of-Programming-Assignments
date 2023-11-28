#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string>
#include<fstream>
#include"planner.cpp"
using namespace std;

/*

  EXIT 
  ADD <station_one> <start_time> <station_two> <finish_time>
  QUERY_STATION <station_one> <start_time>
  QUERY_JOURNEY <station_one> <start_time> <station_two>

*/

void dictionaryHandler(Planner &dictionary){
    for(int i=0;i>=0;i++)
    {
        string input;
        // cout << ">>> " ;
        cin>>input;
        if(input == "EXIT"){
            break;
        }

        // ADD <station_one> <start_time> <station_two> <finish_time>
        if(input == "ADD"){

          char inputStation1[32], inputStation2[32];
          float startTime, finishTime;
          cin >> inputStation1;
          cin >> startTime;
          cin >> inputStation2;
          cin >> finishTime;
          Entry data;
          data.station = inputStation1;
          data.trains[0].destination = inputStation2;
          data.trains[0].start_time = startTime;
          data.trains[0].end_time = finishTime;
          int hashValueData = dictionary.hashValue(data.station);
          int freeIndexData = dictionary.findFreeIndex(data.station);
          if(freeIndexData >= 0){
              dictionary.ADD(data);
          }
        }

        // QUERY_STATION <station_one> <start_time>
        else if(input == "QUERY_STATION"){
          char inputStation1[32];
          float startTime;
          cin >> inputStation1;
          cin >> startTime;
          dictionary.QUERY_STATION(inputStation1,startTime);
        }

        // QUERY_JOURNEY <station_one> <start_time> <station_two>
        else if(input == "QUERY_JOURNEY"){
          char inputStation1[32], inputStation2[32];
          float startTime;
          cin >> inputStation1;
          cin >> startTime;
          cin >> inputStation2;
          dictionary.QUERY_JOURNEY(inputStation1,startTime,inputStation2);
        }
    }
}

/*
void automatic()
{
  Planner dictionary;
  freopen("sample.txt", "r", stdin);
  // TODO
  int frequency[DICT_SIZE] = {0};

  char word[32];
  while(cin >> word){
    int hash = dictionary.hashValue(word);
    frequency[hash]++;
  }

  for(int i = 0; i < DICT_SIZE; i++){
    cout << frequency[i] << endl;
  }

}
*/

void interactive()
{
  //cout<<"Welcome to Dictionary \n";
  //cout<<"";
  Planner dictionary;
  dictionaryHandler(dictionary);
}


int main()
{
  //cout<<"Enter 1 for interactive testing and 0 for automatic"<<endl;
  //int which;
  //cin>>which;
  
  interactive();
  //else{
  //   automatic();
  //}
  return 0;
}
