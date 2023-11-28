#include<iostream>
#ifndef PLANNER_H
#define PLANNER_H
#include <string.h>
#include"dictionary.cpp"
using namespace std;


const int N = 64; 
float min( float a, float b){
  if( a < b)
    return a;
  return b;
}

class Planner {
  Dictionary station_one_list; //all the station_one as key and start_time, reach_time, destination as value will be stored
  Dictionary station_two_list; //all the station_two as key and start_time, reach_time, station where its coming from as value will be stored

  public:

 string queryHandler( char* query){
    // if(strcmp(query, "EXIT") == 0)
    //   return "";
    
    if(strcmp(query,"ADD") == 0){
      cout<<"add\n";
      char stn1[32], stn2[32];
      float start_time, reach_time;
      
      cin>>stn1>>start_time>>stn2>>reach_time;

      struct Entry e1, e2;

      strcpy(e1.key, stn1);
      strcpy(e2.key, stn2);

      e1.value[0].st_time = start_time;
      e1.value[0].rh_time = reach_time;
      strcpy(e1.value[0].stn , stn2); //for storing the destination station

      e2.value[0].st_time = start_time;
      e2.value[0].rh_time = reach_time;
 
      strcpy(e2.value[0].stn , stn1); //storing where the station coming from

      bool action1 = station_one_list.put(e1);
      bool action2 = station_two_list.put(e2);

      if(!(action1 && action2)){
        return "NOT ADDED";
      }
    }

    if(strcmp(query,"QUERY_STATION") == 0){
      cout<<"q-st\n";
      char stn1[32];
      float start_time;
      cin>>stn1>>start_time;
      
      struct Entry e1;
      strcpy(e1.key, stn1);
      
      e1.value[0].st_time = start_time;
      
      struct Entry *b ;
      b = station_one_list.get(e1.key);

      if(b==NULL)
        return "no such station exist";

      int i=0;
      bool flag = false; //to check if any train available after the given time
      while(b->value[i].filled==1 && i<DICT_SIZE){
        if(b->value[i].st_time >= e1.value[0].st_time){
          cout << b->value[i].st_time << " "<< b->value[i].stn<<endl;
          flag = true;
        }
        
        i++;
      }  
      if(!flag)
        return "NO TRAIN AVAILABLE";    
 
    }

    if(strcmp(query,"QUERY_JOURNEY") == 0){
      cout<<"q-j\n";
      char stn1[32], stn2[32];
      float start_time;
      cin>>stn1>>start_time>>stn2;

      struct Entry e1;
      strcpy(e1.key, stn1);
      e1.value[0].st_time = start_time;
      struct Entry *b ;
      b = station_one_list.get(e1.key);

      struct Entry *c ;
      c = station_two_list.get(stn2);

      if(b==NULL || c==NULL)
        return "no such station -- exist";
      
      int i=0;
      float mini=9999, newmini=9999;
      char dest[32];
      float time1, time2, epsilon=0.001;
      

      while(b->value[i].filled==1 && i<DICT_SIZE){
        if((strcmp(b->value[i].stn, stn2) == 0) && (b->value[i].st_time >= start_time)){//direct a to c
          mini = min(mini, b->value[i].st_time);
        
        }
        else{
          
          int  newi=0;
          while(c->value[newi].filled==1 && newi<DICT_SIZE){
            if((strcmp(c->value[newi].stn, b->value[i].stn) == 0)  && (b->value[i].st_time >= start_time) && (c->value[newi].st_time >= b->value[i].rh_time)){
              
              newmini = min(newmini, b->value[i].st_time);
                if(newmini <= b->value[i].st_time+epsilon && newmini >= b->value[i].st_time-epsilon ){
                  time1 = b->value[i].st_time;
                  time2 = c->value[newi].st_time;
                  strcpy(dest, b->value[i].stn);
                
                }
               
            }
            newi++;
          }

        }
        i++;
      }
      if (mini<=newmini){
        cout<<mini<<endl;
      }
      else{
        cout<<time1<<"     "<<dest<<"   "<<time2;
      }

    }


  return "\0";
  }

};

#endif