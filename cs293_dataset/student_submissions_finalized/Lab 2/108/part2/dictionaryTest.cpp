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
    string input;
    cout << ">>> " ;
    cin>>input;
    if(input == "QUIT"){
      break;
    }

    // INS <key> <value>
    if(input == "INS"){

      char inputKey[32];
      cin >> inputKey;
      int value;
      cin >> value;
      Entry data;
      data.key = inputKey;
      data.value = {};
      int hashValueData = dictionary.hashValue(data.key);
      cout << "Hash Value: " << hashValueData << endl;
      int freeIndexData = dictionary.findFreeIndex(data.key);
      cout << "Free Location: "<< freeIndexData << endl;
      if(freeIndexData >= 0){
        dictionary.put(data);
        cout << "Successfully Added " << endl;
      }
      else{
        cout << "NO Available space " << endl;
      }
    }

    // DEL <key>
    else if(input == "DEL"){
      char inputKey[32];
      cin >> inputKey;
      if(dictionary.remove(inputKey)){
        cout << "Entry removed Successfully" << endl;
      }
      else{
        cout << "Entry not present" << endl;
      }
    }

    // FIND <key>
    else if(input == "FIND"){
      char inputKey[32];
      cin >> inputKey;
      Entry *entry = dictionary.get(inputKey);
      if(entry != NULL){
        cout << inputKey << " has value: " << 0 << endl;
      }
      else{
        cout << inputKey << " not Found" << endl;
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
