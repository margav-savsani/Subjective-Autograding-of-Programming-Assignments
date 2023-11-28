#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"planner.cpp"
using namespace std;

/*
In interactive mode you can give commands '
  EXIT
  ADD <StationStart> <TimeStart> <StationEnd> <TimeEnd>
  QUERY_STATION <StationStart> <TimeStart>
  QUERY_JOURNEY <Station Start> <TimeStart> <StationEnd>
*/

void dictionaryHandler(Dictionary &dictionary){         //Class for looping the input
  for(int i=0;i>=0;i++)
  {
    char input[32];
    cout << ">>> " ;
    cin>>input;
    if(strcmp(input,"EXIT") == 0){                      //End  loop if user inputs Exit
      break;
    }

    //ADD <StationStart> <TimeStart> <StationEnd> <TimeEnd>
    if(strcmp(input,"ADD") == 0){                                

      char StationStart[32];
      cin >> StationStart;
      int TimeStart;
      cin >> TimeStart;
      char StationEnd[32];
      cin >> StationEnd;
      int TimeEnd;
      cin >> TimeEnd;
      Entry data;
      strcpy(data.key,StationStart);                        //Copy the data entered by user into the value of cell
      (data.value).push_back(Journey (StationStart, TimeStart, StationEnd, TimeEnd));
      int hashValueData = dictionary.hashValue(data.key);
      int freeIndexData = dictionary.findFreeIndex(data.key);
      //cout << "Hash Value: " << hashValueData << endl;      //Removed because not asked in final spec
      //cout << "Free Location: "<< freeIndexData << endl;    //Modified findFreeIndex to accomadate a different use case
      if(freeIndexData >= 0){
        dictionary.put(data);
        cout << "Successfully Added " << endl;             
      }
      else{
        cout << "NO Available space " << endl;
      }
    }

    

    //Query_Station <StationStart> <TimeStart>
    else if(strcmp(input,"QUERY_STATION") == 0){
      char StationStart[32];
      cin >> StationStart;
      int TimeStart;
      cin >> TimeStart;
      Entry *entry = dictionary.get(StationStart);      
      
      if(entry != NULL){                                      //Condition to start the search in vector 
        bool b = true;
        for(int i = 0 ; i < (entry->value).size() ; i++ ){    //Loops through the vector
            if((entry->value)[i].TimeStart>=TimeStart){
                cout << (entry->value)[i].TimeStart << " " << (entry->value)[i].StationEnd << endl;
                b = false;
            }
        }
        if(b){                                               //If station doesn't have any other train
            cout   <<  "No trains found" << endl;
        }
      }
      else{
        cout << StationStart << " not Found" << endl;
      }
    }

    //QUERY_JOURNEY <Station Start> <TimeStart> <StationEnd>
    else if(strcmp(input,"QUERY_JOURNEY") == 0){
      char StationStart[32];
      cin >> StationStart;
      int TimeStart;
      cin >> TimeStart;
      char StationEnd[32];
      cin >> StationEnd;
      int earliest_time = 2400;

      Entry *entry = dictionary.get(StationStart);
      if(entry != NULL){                                              
        bool b = true;
        
        for(int i = 0 ; i < (entry->value).size() ; i++ ){            //Loop to find the minimum 
            if(  (entry->value)[i].TimeStart>=TimeStart   &&   strcmp((entry->value)[i].StationEnd,StationEnd)==0   ) { //For direct journeys
                if ( (entry->value)[i].TimeStart < earliest_time ){
                    earliest_time = (entry->value)[i].TimeStart;
                    b = false;
                }

            }
            
            if ( (entry->value)[i].TimeStart>=TimeStart   &&   strcmp((entry->value)[i].StationEnd,StationEnd)!=0 ){    //For Indirect Journeys
                Entry *inter = dictionary.get((entry->value)[i].StationEnd);
                if(inter != NULL){
                    for ( int j = 0 ; j < (inter->value).size() ; j++ ){
                        if( (entry->value)[i].TimeEnd<=(inter->value)[j].TimeStart && strcmp ((inter->value)[j].StationEnd,StationEnd)==0 ){ 
                            if ( (entry->value)[i].TimeStart < earliest_time ){
                                earliest_time = (entry->value)[i].TimeStart;
                                b = false;
                            }    
                        }
                    }
                }
            }
        }
        
        //This part of code is simply to print whatever is necessary
        if(b){
            cout << "No train leaves from " << StationStart << " to " << StationEnd << " after " << TimeStart << endl;
        }
        else{
            for(int i = 0 ; i < (entry->value).size() ; i++ ){    //The above code finds earliest_time, this part just checks when earliest_time was achieved and prints that case
                if(  (entry->value)[i].TimeStart>=TimeStart   &&   strcmp((entry->value)[i].StationEnd,StationEnd)==0   ) {
                    if ( (entry->value)[i].TimeStart == earliest_time ){
                        cout << earliest_time << endl;
                        break;
                    }

                }
            
                if ( (entry->value)[i].TimeStart>=TimeStart   &&   strcmp((entry->value)[i].StationEnd,StationEnd)!=0 ){      //The above code finds earliest_time, this part just checks when earliest_time was achieved and prints that case
                    Entry *inter = dictionary.get((entry->value)[i].StationEnd);
                    if(inter != NULL){
                        for ( int j = 0 ; j < (inter->value).size() ; j++ ){
                            if( (entry->value)[i].TimeEnd<=(inter->value)[j].TimeStart && strcmp ((inter->value)[j].StationEnd,StationEnd)==0 ){
                                if ( (entry->value)[i].TimeStart == earliest_time ){
                                    cout << earliest_time << " " << (entry->value)[i].StationEnd << " " << (inter->value)[j].TimeStart << endl;
                                    break;
                                }    
                            }
                        }
                    }
                }
            }
            }
        }
        else{
            cout << StationStart << " not Found" << endl;
        }
    }//Printing loops end here
  }
}

void automatic()          //Counts hash collisions
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

void interactive()        //wrapper function
{
  cout<<"Welcome to Railways \n";
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


