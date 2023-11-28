#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include "dictionary_part2.cpp"
using namespace std;

void queryHandler(Dictionary &dictionary){
while (true)
  { 
    char input[32];
    cout << ">>> " ;
    cin>>input;
    if(strcmp(input,"EXIT") == 0){
      break;
    }

    // INS <key> <value>
    if(strcmp(input,"ADD") == 0){
      string s_one;
      cin >> s_one;
      float start_time;
      cin >> start_time;
      string s_two;
      cin >> s_two;
      float finish_time;
      cin >> finish_time;
      Entry data;
    // //   const char a=start_time;
    // //   const char* p=&a;
    // //   const char b=finish_time;
    // //   const char* q=&b;
    // //   strcat(station_one, station_two);
    // //   strcat(station_one,p);
    // //   strcat(station_one,q);  
      data.key = &s_one[0];
      data.station_two=strcpy(new char[s_two.length() + 1], s_two.c_str());
      data.station_one = strcpy(new char[s_one.length() + 1], s_one.c_str());
      data.start_time=start_time;  
      data.finish_time=finish_time;
      int hashValueData = dictionary.hashValue(data.key);
      int freeIndexData = dictionary.findFreeIndex(data.key);
      cout << "Hash Value: " << hashValueData << endl;
      cout << "Free Location: "<< freeIndexData << endl;
      if(freeIndexData >= 0){
        dictionary.put(data);
        cout << "Successfully Added "<< endl;
      }
      else{
        cout << "NO Available space " << endl;
      }
    }

    // DEL <key>
    else if(strcmp(input,"QUERY_STATION") == 0){
   	char station_one[32];
    cin >> station_one;
    int start_time;	
    cin>>start_time;  
    dictionary.query_one(station_one,start_time);
    }

    else if(strcmp(input,"QUERY_JOURNEY") == 0){
      	char station_one[32];
      	cin >> station_one;
      	float start_time;
      	cin >> start_time;
      	char station_two[32];
      	cin >> station_two;
        dictionary.query_two(station_one,start_time,station_two);
    }
    }
    }



int main()
{
	Dictionary dictionary;
	queryHandler(dictionary);
  return 0;
}
