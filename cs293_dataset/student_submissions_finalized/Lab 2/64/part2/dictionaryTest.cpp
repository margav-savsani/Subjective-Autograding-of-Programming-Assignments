#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"dictionary.cpp"
using namespace std;

/*

In interactive mode you can give commands '
  QUIT
  INS <key> <value>
  DEL <key>
  FIND <key>

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

      char station1[32];
      cin >> station1;
      float start_time;
      cin >> start_time;
      char station2[32];
      cin>>station2;
      float finish_time;
      cin>>finish_time;
      Entry data;
      strcpy(data.station1,station1);
      data.start_time=start_time;
      data.finish_time=finish_time;
      strcpy(data.station2,station2);
      int hashValue = dictionary.hashValue(data.station1);
      int freeIndex = dictionary.findFreeIndex(data.station1);
      if(freeIndex >= 0){
        dictionary.put(data);
        cout << "Successfully Added " << endl;
        cout<< "Hash Value : "<<hashValue<<endl;
        cout<<"Inserted at index: "<<freeIndex<<endl;
      }
      else{
        cout << " NO Available space " << endl;
      }
    }

    else if(strcmp(input, "QUERY_STATION") == 0){
      char station1[32];
      cin >> station1;
      float start_time;
      cin>>start_time;
      dictionary.querystation(station1, start_time);
    }

    else if(strcmp(input, "QUERY_JOURNEY") == 0){
      char station1[32];
      cin >> station1;
      float start_time;
      cin>>start_time;
      char station2[32];
      cin>>station2;
      bool a = dictionary.queryjourney(station1, start_time, station2);
    }
    // FIND <key>
    // else if(strcmp(input,"FIND") == 0){
    //   char inputKey[32];
    //   cin >> inputKey;
    //   Entry *entry = dictionary.get(inputKey);
    //   if(entry != NULL){
    //     cout << inputKey << " has value: " << entry->value << endl;
    //   }
    //   else{
    //     cout << inputKey << " not Found" << endl;
    //   }
    // }
  }
}

void automatic()
{
  Dictionary dictionary;
  freopen("sample.txt", "r", stdin);
  // dictionaryHandler(dictionary);
  // TODO
  int frequency[64] = {0};

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
