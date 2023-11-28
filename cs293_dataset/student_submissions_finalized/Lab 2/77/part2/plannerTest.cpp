#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "dictionary.cpp"
using namespace std;

void dictionaryHandler(Dictionary &dictionary)
{
  for (int i = 0; i >= 0; i++)
  {
    char input[32];
    cout << ">>> ";
    cin >> input;
    if (strcmp(input, "EXIT") == 0)
    {
      break;
    }
    // ADD <station1> <time> <station2> <time2>
    if (strcmp(input, "ADD") == 0)
    {
      char startKey[32];
      cin >> startKey;
      double start_time;
      cin >> start_time;
      char finishKey[32];
      cin >> finishKey;
      double finish_time;
      cin >> finish_time;

      Journey data;
      strcpy(data.key, startKey);
      data.start_time = start_time;
      strcpy(data.station_two, finishKey);
      data.finish_time = finish_time;
      int hashValueData = dictionary.hashValue(data.key);
      int freeIndexData = dictionary.findFreeIndex(data.key);
      dictionary.put(data);
    }

    // QUERY_JOURNEY <key> <start_time> <station_two>
    else if (strcmp(input, "QUERY_JOURNEY") == 0)
    {
      char inputKey[32];
      cin >> inputKey;
      double time;
      cin >> time;
      char stat_two[32];
      cin >> stat_two;

      bool path = false;//indirect
      bool direct =  false ;
      int final_start_time=1000000 ;
      int final_inter_start_time = -1;
      char inter_station[32];
      int numTrains = dictionary.getTrains(inputKey);
      Journey *journey = dictionary.get(inputKey);
      for (int i = 0; i < numTrains; i++)
      {
        bool check = ((strcmp(journey[i].station_two, stat_two)) == 0);
        if ((journey[i].start_time >= time) && check)
        {
          path = false;
          direct=true;
          if(final_start_time > journey[i].start_time){
          final_start_time = journey[i].start_time;
          }
        }
      }

      for (int i = 0; i < numTrains; i++)
      {
        if (journey[i].start_time >= time)
        {
          Journey *inter = dictionary.get(journey[i].station_two);
          int num = dictionary.getTrains(journey[i].station_two);
          for (int k = 0; k < num; k++)
          {
            bool ch = ((strcmp(inter[k].station_two, stat_two)) == 0);
            if (ch && (journey[i].finish_time <= inter[k].start_time) && (!(strcmp(journey[i].station_two,inter[k].key))))
            { 
              if (final_start_time > journey[i].start_time)
              { 
                path = true;
                direct = false;
                final_start_time = journey[i].start_time;
                final_inter_start_time = inter[k].start_time;
                strcpy(inter_station, inter[k].key);
              }
            }
          }
        }
      }
    
    if (direct)
    {
      cout << final_start_time<<endl;path=false;direct=false; 
    }
    else if(path){
      cout << final_start_time << " " << inter_station << " " << final_inter_start_time << endl;path=false;direct=false; 
    }
    else cout<<"ERROR";
    }
    // QUERY_STATION <key> <start_time>
    else if (strcmp(input, "QUERY_STATION") == 0)
    {
      char inputKey[32];
      cin >> inputKey;
      double time;
      cin >> time;
      int numTrains = dictionary.getTrains(inputKey);
      
      int j = 0;
      Journey *journey = dictionary.get(inputKey);
      for (int i = 0; i < numTrains; i++)
      { 
        if (journey[i].start_time >= time)
        {
          cout << journey[i].start_time << " " << journey[i].station_two << endl;
          j++;
        }
      }
      if (j == 0)
      {
        cout << "No trains found" << endl;
      }
    }
  }
}

void automatic()
{
  Dictionary dictionary;
  freopen("sample-planner.txt", "r", stdin);
  dictionaryHandler(dictionary);
  // TODO
  int frequency[DICT_SIZE] = {0};

  char word[32];
  while(cin >> word){

  }

}
void interactive()
{
  cout << "Welcome to Dictionary \n";
  cout << "";
  Dictionary dictionary;
  dictionaryHandler(dictionary);
}

int main()
{
  cout<<"Enter 1 for interactive testing and 0 for automatic"<<endl;
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
