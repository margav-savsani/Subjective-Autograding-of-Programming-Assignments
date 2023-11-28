#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.cpp"
using namespace std;
void plannerHandler(Planner &planner){
  for(int i=0;i>=0;i++)
  {
    char input[32];
    cout << ">>> " ;
    cin>>input;
    if(strcmp(input,"EXIT") == 0){
      break;
    }
   if(strcmp(input,"ADD") == 0){
      char inputKey1[32];
      cin >> inputKey1;
      float value1;
      cin >> value1;
      char inputKey2[32];
      cin >> inputKey2;
      float value2;
      cin >> value2;
      Journey j;
      strcpy(j.from,inputKey1);
      j.arri  = value1;
      strcpy(j.to,inputKey2);
      j.dept  = value2;
      int hashValueData = planner.hashValue(j.from);
      int freeIndexData = planner.findFreeIndex(j.from);
      cout << "Hash Value: " << hashValueData << endl;
      cout << "Free Location: "<< freeIndexData << endl;
      if(freeIndexData >= 0){
        planner.insert(j);
        cout << "Successfully Added " << endl;
      }
      else{
        cout << "NO Available space " << endl;
      }
    }
    else if(strcmp(input,"QUERY_STATION") == 0){
      char inputKey3[32];
      cin >> inputKey3;
      float value3;
      cin >> value3;
      if(!planner.Query_Station(inputKey3,value3)){
        cout<<"No trains are currently running at the specified station after the specified time today"<<endl;
      }

    }
    else if(strcmp(input,"QUERY_JOURNEY") == 0){
     char inputKey4[32];
      cin >> inputKey4;
      float value4;
      cin >> value4;
      char inputKey5[32];
      cin >> inputKey5;
      if(!planner.Query_Journey(inputKey4,value4,inputKey5)){
        cout<<"No trains are currently running at the specified station after the specified time today"<<endl;
      }

    }}}
    void automatic()
{
  Planner planner;
  freopen("sample_planner.txt", "r", stdin);

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

void interactive()
{
  cout<<"Welcome to Indian Railways \n";
  cout<<"";
  Planner planner;
  plannerHandler(planner);
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
