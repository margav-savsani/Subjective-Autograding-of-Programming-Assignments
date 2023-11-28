#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.h"
using namespace std;

void plannerHandler(Planner &planner){
    for(int i=0; i>=0; i++){
        char input[32];
        cout << ">>> " ;
        cin >> input;
        // EXIT
        if(strcmp(input,"EXIT") == 0){
            break;
        }
        // ADD <station_one> <start_time> <station_two> <finish_time>
        if(strcmp(input,"ADD") == 0){
            char inputKey[32], outputKey[32];
            cin >> inputKey;
            int value1, value2;
            cin >> value1 >> outputKey >> value2;
            Journey data;
            strcpy(data.key,inputKey);
            data.start_time = value1;
            data.end_time  = value2;
            int hashValueData = planner.hashValue(data.key);
            int freeIndexData = planner.findFreeIndex(data.key);
            cout << "Hash Value: " << hashValueData << endl;
            cout << "Free Location: "<< freeIndexData << endl;
            if(freeIndexData >= 0){
                planner.put(data);
                cout << "Successfully Added " << endl;
            }
            else{
                cout << "NO Available space " << endl;
            }
        }
        // QUERY_STATION <station_one> <start_time>
        else if(strcmp(input, "QUERY_STATION") == 0){
            char inputKey[32];
            double value;
            cin >> inputKey >> value;
            Journey *journey = planner.get(inputKey);
                query_station(inputKey, value, planner);
        }
        // QUERY_JOURNEY <station_one> <start_time> <station_two>
        else if(strcmp(input,"QUERY_JOURNEY") == 0){
            char inputKey[32], outputKey[32];
            double value;
            cin >> inputKey >> value >> outputKey;
            Journey *journey = planner.get(inputKey);
            if(journey == NULL){
                cout << "ERROR" << endl;
            }
            else{
                query_journey(inputKey, value, outputKey, planner);              
            }
        }
    }
}

void automatic(){
    Planner planner;
    freopen("sample.txt", "r", stdin);
    // dictionaryHandler(dictionary);
    // TODO
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

void interactive(){
    cout << "Welcome to Dictionary \n";
    cout << "";
    Planner planner;
    plannerHandler(planner);
}


int main(){
  cout << "Enter 1 for interactive testing and 0 for automatic" << endl;
  int which;
  cin >> which;
  if(which == 1){
    interactive();
  }
  else{
    automatic();
  }
  return 0;
}