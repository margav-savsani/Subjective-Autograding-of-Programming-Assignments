#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
//#include "planner-help.cpp"
#include "planner.cpp"

using namespace std;

/*
In interactive mode you can give commands '
  QUIT
  INS <key> <value>
  DEL <key>
  FIND <key>

*/

void plannerHandler(Planner &planner)
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

        // INS <key> <value>
        else if (strcmp(input, "ADD") == 0)
        {
            //cout <<"Entered Add statement"<<endl;
            // Entry start_station;
            // Entry destination;

            char inputKey1[32];
            cin >> inputKey1;
            float value1;
            cin >> value1;
            char inputKey2[32];
            cin >> inputKey2;
            float value2;
            cin >> value2;

            planner.AddJourney(inputKey1, value1, inputKey2, value2);
            /*strcpy(data.key,inputKey);
            data.value  = value;
            int hashValueData = dictionary.hashValue(data.key);
            int freeIndexData = dictionary.findFreeIndex(data.key);
            cout << "Hash Value: " << hashValueData << endl;
            cout << "Free Location: "<< freeIndexData << endl;
            if(freeIndexData >= 0){
              dictionary.put(data);
              cout << "Successfully Added " << endl;
            }
            else{
              cout << "NO Available space " << endl;
            }*/
        }

        // DEL <key>
        else if (strcmp(input, "QUERY_STATION") == 0)
        {
            char inputKey[32];
            cin >> inputKey;
            float time1;
            cin >> time1;
            planner.query_station(inputKey, time1);
            /*if(dictionary.remove(inputKey)){
              cout << "Entry removed Successfully" << endl;
            }
            else{
              cout << "Entry not present" << endl;
            }
          }*/
        }

        // FIND <key>
        else if (strcmp(input, "QUERY_JOURNEY") == 0)
        {
            char inputKey1[32];
            cin >> inputKey1;
            float time1;
            cin >> time1;
            char inputKey2[32];
            cin >> inputKey2;
            // Entry *entry = dictionary.get(inputKey);
            /*if(entry != NULL){
              cout << inputKey << " has value: " << entry->value << endl;
            }
            else{
              cout << inputKey << " not Found" << endl;
            }*/
            Query result = planner.query_journey(inputKey1, time1, inputKey2);
            if (result.time1 == 9999)
            {
                cout << "No JOURNEY between two stations given" << endl;
            }
            else
            {
                if (result.time2 == 9999)
                {
                    cout << result.time1 << endl;
                }
                else
                {
                    cout << result.time1 << " " << result.name << " " << result.time2 << endl;
                }
            }
        }
    }
}

/*void automatic()
{
  Dictionary dictionary;
  freopen("sample.txt", "r", stdin);
  // dictionaryHandler(dictionary);
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

}*/

void interactive()
{
    cout << "Welcome to Railway Planner \n";
    cout << "";
    Planner railway_planner;
    plannerHandler(railway_planner);
}

int main()
{
    cout << "Enter 1 for interactive testing and 0 for automatic" << endl;
    int which;
    cin >> which;

    if (which == 1)
    {
        interactive();
    }
    /*else{
      automatic();
    }*/
    return 0;
}
