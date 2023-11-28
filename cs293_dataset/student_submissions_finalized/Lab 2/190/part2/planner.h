#ifndef PLANNER_H
#define PLANNER_H

#include <iostream>
#include "dictionary.cpp"
using namespace std;

class Planner
{

  Dictionary Dict;

public:
  Planner()
  {
  }












  void add(string st1, int t1, string st2, int t2)
  {
    char key1[32];
    strcpy(key1, st1.c_str());
    Entry e;
    strcpy(e.key, key1);
    int k = Dict.hashValue(e.key);
    while (strcmp( Dict.A[k].key, Dict.emptyKey) != 0)
    { 
        if (strcmp(key1, Dict.A[k].key) == 0)
        {
          Journey j = {st1, t1, st2, t2};
          Dict.A[k].q.QInsert(j);
          return;
        }
        k = (k + 1) % Dict.N;
    }
    strcpy(Dict.A[k].key, key1);
    Journey j = {st1, t1, st2, t2};
    Dict.A[k].q.QInsert(j);
    return;
  }





















  void query_station(string s, int t)
  {
    char key1[32];
    strcpy(key1, s.c_str());
    int k = Dict.hashValue(key1);
    while (strcmp( Dict.A[k].key, Dict.emptyKey) != 0)
    { // Looping while slot is occupied, i.e. NOT EMPTY
        if (strcmp(key1, Dict.A[k].key) == 0)
        {
          Dict.A[k].q.display(0);
          return;
        }
        k = (k + 1) % Dict.N;
    }
    cout << "ERROR\n";
    return;
  }



















  void query_journey(string s1, int t, string s2)
  {
    char key_s1[32];
    strcpy(key_s1, s1.c_str());

    char key_s2[32];
    strcpy(key_s2, s2.c_str());

    int index_s1 = Dict.getint(key_s1);
    if(index_s1 == -1){
      cout << "ERROR\n";
      return;
    }
    
    Dict.A[index_s1].q.sort();

    for(int i=Dict.A[index_s1].q.head; i<Dict.A[index_s1].q.tail; i++){
      //Looping through the station 1 manual


      if(Dict.A[index_s1].q.A[i].start_time < t) continue;


      string sINTER = Dict.A[index_s1].q.A[i].station2;
      char key_sINTER[32];
      strcpy(key_sINTER, sINTER.c_str());

      if(strcmp(key_sINTER, key_s2)==0){
        cout << Dict.A[index_s1].q.A[i].start_time << endl;
        return;
      }

      //check if it is an intermediate station
      //Open log of sINTER
      int index_sINTER = Dict.getint(key_sINTER);
      if(index_sINTER == -1){
        continue;
      }

      Dict.A[index_sINTER].q.sort();

      for(int j=Dict.A[index_sINTER].q.head; j<Dict.A[index_sINTER].q.tail; j++){

        if(Dict.A[index_sINTER].q.A[j].start_time  < Dict.A[index_s1].q.A[i].end_time) continue;


        if(strcmp(Dict.A[index_sINTER].q.A[j].station2.c_str(), key_s2) == 0){
          cout << Dict.A[index_s1].q.A[i].start_time << " " << sINTER << " " << Dict.A[index_sINTER].q.A[j].start_time << endl;
          return;
        }
      }

    }




    // int k = Dict.hashValue(key1);
    // while (strcmp( Dict.A[k].key, Dict.emptyKey) != 0)
    // { // Looping while slot is occupied, i.e. NOT EMPTY
    //     if (strcmp(key1, Dict.A[k].key) == 0)
    //     {
          
    //       Dict.A[k].q.sort();

    //       for(int i= Dict.A[k].q.head; i<Dict.A[k].q.tail; i++){

    //           string dest = Dict.A[k].q.A[i].station1;
    //           char key2[32];
    //           strcpy(key2, dest.c_str());

    //           if( strcmp(key2, key3)){
    //             cout << Dict.A[k].q.A[i].start_time;
    //             return;
    //           }

    //           //dest is an intermediate station
    //           int kk = Dict.hashValue(key2);  // key2 == dest
    //           while (strcmp(Dict.A[kk].key, Dict.emptyKey) != 0)
    //           { // Looping while slot is occupied, i.e. NOT EMPTY
    //             if (strcmp(key2, Dict.A[kk].key) == 0)
    //             {
                  
    //               Dict.A[kk].q.sort();
    //               for(int p= Dict.A[kk].q.head; p<Dict.A[kk].q.tail; p++){
    //                 if(strcmp(key3, Dict.A[kk].q.A[p].station2.c_str())){
    //                   cout << Dict.A[k].q.A[i].start_time << " " << dest << " " << Dict.A[kk].q.A[p].start_time << endl;
    //                   return;
    //                 }
    //               }

    //               return;
    //             }
    //             k = (k + 1) % Dict.N;
    //           }
              
              


    //       }
          
    //     }
    //     k = (k + 1) % Dict.N;
    // }
    
    // cout << "ERROR\n";


    cout << "ERROR" << endl;
    return;
  }
};

#endif