#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include "planner.cpp"
using namespace std;

/*

In interactive mode you can give commands '
  QUIT
  INS <key> <value>
  DEL <key>
  FIND <key>

*/

void plannerHandler(Planner &planner){
  for(int i=0;i>=0;i++)
  {
    char input[32];
    cout << ">>> " ;
    cin>>input;
    if(strcmp(input,"EXIT") == 0){
      break;
    }

    // ADD <key> <value>
    if(strcmp(input,"ADD") == 0){

        char start_station[32];
        cin >> start_station;
        double start_time;
        cin >> start_time;
        char end_station[32];
        cin >> end_station;
        double end_time;
        cin >> end_time;
        bool a = planner.add(start_station, start_time, end_station, end_time);
        if (a) cout<<"Entry added successfully"<<endl;
        else cout<<"Entry not added successfully"<<endl;
    }

    // QUERY_STATION <key>
    else if(strcmp(input, "QUERY_STATION") == 0){
        char start_station[32];
        cin >> start_station;
        double start_time;
        cin >> start_time;
        returnDetails r1 = planner.query_station(start_station, start_time);
        for(int j = 0;j<r1.len;j++){
            cout << r1.details[j].stime << " " << r1.details[j].dest << " ";
        }
        cout<<endl;
    }

    // QUERY_JOURNEY <key>
    else if(strcmp(input,"QUERY_JOURNEY") == 0){
        char start_station[32];
        cin >> start_station;
        double start_time;
        cin >> start_time;
        char end_station[32];
        cin >> end_station;
        Info inf = planner.query_journey(start_station, start_time, end_station);
        if ((strcmp(inf.dest,"") == 0) && (inf.etime == -1)){
            if (inf.stime != -1){
                cout<<inf.stime<<endl;
            }
        }
        else{
            cout<<inf.stime<<" "<<inf.dest<<" "<<inf.etime<<endl;
        }
    }
  }
}

void automatic()
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

}

void interactive()
{
  cout<<"Welcome to Dictionary \n";
  cout<<"";
  Planner planner;
  plannerHandler(planner);
}


int main()
{
  interactive();
  return 0;
}
