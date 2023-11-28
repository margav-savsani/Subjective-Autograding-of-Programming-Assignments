#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"railDict.cpp"
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

    // ADD <key> <value tuple>
    if(strcmp(input,"ADD") == 0){

      char inputKey[32];
      cin >> inputKey;
			
      float T_i;
      cin >> T_i;
      char reach[32];
      cin >> reach;
      float T_f;
      cin >> T_f;
      
      Data dt;
      dt.TI  = T_i;
      strcpy(dt.KEY,inputKey);
      dt.TF  = T_f;
      int hashValueData = dictionary.hashValue(dt.KEY);
      int freeIndexData = dictionary.findFreeIndex(dt.KEY);
      
      if(freeIndexData >= 0){
        dictionary.put(dt);
        cout << "Successfully Added " << endl;
      }
      else{
        cout << "NO Available space " << endl;
      }
    }

/*    // DEL <key>
    else if(strcmp(input, "DEL") == 0){
      char inputKey[32];
      cin >> inputKey;
      if(dictionary.remove(inputKey)){
        cout << "Entry removed Successfully" << endl;
      }
      else{
        cout << "Entry not present" << endl;
      }
    }*/

    // QUERY_JOURNEY <station_one> <start_time> <station_two>
    else if(strcmp(input,"QUERY_JOURNEY") == 0){
      char inputKey[32];
      cin >> inputKey;
      float T_i;
      cin >> T_i;
      char reach[32];
      cin >> reach;
      
      Entry *entry = dictionary.get(inputKey);
      if(entry != NULL)
      {
        // cout << inputKey << " has value: " << entry->value << endl;
      	for (int i=0; i<50; i++) {
      		if ((entry->Ti[i]>=T_i) && (strcmp(entry->dest[i], reach)==0)) {
      			cout << entry->Ti[i] << " " << entry->dest[i] << endl;
      			break;
      		}
      	}
      }
      else
        cout << "ERROR" << endl;
      
    }
    
    // QUERY_STATION <staion_one> <start_time>
    else if(strcmp(input, "QUERY_STATION") == 0) {
    	char inputKey[32];
    	cin>>inputKey;
    	float T_i;
    	cin>>T_i;
    	
    	Entry *entry=dictionary.get(inputKey);
    	
    	if (entry != NULL) {
    		/*for (int i=0; i<50; i++) {            // this nested if's and for's are to print 
    			if ((T_i > entry->Ti[i])&&(i!=49))  // the 'Ti' and 'dest' of key, if T_i < Ti's
    				continue;                         // else it prints ERROR
    			
    			if (i==49 && (T_i>entry->Ti[49]))
    				cout << "ERROR\n";

    			cout << entry->Ti[i] << " " << entry->dest[i] << endl;
    			
    			
    		}*/
    		cout << "true\n";
    	}
    	else
    		cout<<"ERROR\n";
    	
    }
  }
}

void automatic()
{
  Dictionary dictionary;
  freopen("sample-planner.txt", "r", stdin);
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
  Dictionary dictionary;
  dictionaryHandler(dictionary);
}


int main()
{
  //cout<<"Enter 1 for interactive testing and 0 for automatic"<<endl;
  int which=1;
  //cin>>which;
  
  if(which == 1){
    interactive();
  }
  else{
    automatic();
  }
  return 0;
}
