#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "PLANNER.h"
using namespace std;

void dictionaryHandler(Dictionary &dictionary)
{
  for (int i = 0; i >= 0; i++)
  {
    char input[32];
    cin >> input;
    if (strcmp(input, "EXIT") == 0)
    {
      break;
    }

    // ADD <station_one> <start_time> <station_two> <end_time>
    if (strcmp(input, "ADD") == 0)
    {
      char startstation[32];
      cin >> startstation;

      float starttime;
      cin >> starttime;

      char endstation[32];
      cin >> endstation;

      float endtime;
      cin >> endtime;

      JOURNEY data;
      strcpy(data.start, startstation);
      strcpy(data.end, endstation);

      data.start_t = starttime;
      data.end_t = endtime;

      int hashValueData = dictionary.hashValue(data.start);
      int freeIndexData = dictionary.findFreeIndex(data.start);
      if (freeIndexData >= 0)
      {
        dictionary.put(data);
      }
      else //If the size becomes full
      {
        cout << "NO Available space for JOURNEY" << endl;
      }
    }
    
    // QUERY_STATION <station_one> <start_time> 
    else if (strcmp(input, "QUERY_STATION") == 0)
    {
      char inputKey[32];
      cin >> inputKey;

      float inputstart;
      cin >> inputstart;

      DynamicQueue<JOURNEY> list = (dictionary.getall(inputKey, inputstart)); 
      // returns an array of entries having the required stations and respective time of departure.
      if (list.size()!=0)
      {
        list.print();
      }
      else
      {
        cout << "ERROR" << endl;
      }
    }
    
    // QUERY_JOURNEY <station_one> <start_time> <station_two>
    else if (strcmp(input, "QUERY_JOURNEY") == 0)
    {
      char inputKeystart[32];
      cin >> inputKeystart;

      float inputstart;
      cin >> inputstart;

      char inputKeyend[32];
      cin >> inputKeyend;

      JOURNEY output = dictionary.searchjourney(inputKeystart,inputKeyend,inputstart);
     
      if (strcmp(output.end,inputKeyend) == 0) //If end station returned is the actual end station 
                                              //then only print time to leave from start station.
      {
        cout <<output.start_t<<endl;
      }
      else if(strcmp(output.end,"NULL")==0) //If no such station then return ERROR
      {
        cout << "ERROR" <<endl;
      }
      else { //Case when there is intermediate station.
        cout<< output.start_t <<" "<<output.end<< " "<< output.end_t<<endl;
      }
    }
  }
}
void interactive()
{
  Dictionary dictionary;
  dictionaryHandler(dictionary);
}

int main()
{

  interactive();
  return 0;
}
