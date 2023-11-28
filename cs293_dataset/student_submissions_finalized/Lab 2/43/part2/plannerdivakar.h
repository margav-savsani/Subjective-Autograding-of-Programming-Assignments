#ifndef PLANNER_H
#define PLANNER_H
#include<iostream>
#include<cmath>
#include<string.h>
using namespace std;

class Station {
  // define suitable fields her
};

class Journey {
    public:
    string station1;
    string station2;
    float strttm;
    float endtm;
  // define suitable fields here
};

struct Query{
  // define suitable fields here
};

class Planner {
  private:
    Journey jou[64];
  public:
   Planner(){
     for(int i=0;i < 64;i++){
        jou[i].station1 = "!";
     }
   } 
   const float M=(sqrt(5)-1)/2;

   int hashfunction(string s){
       float a=0;int i=0;
       while(s[i]!='\0'){
       a=((int)(a*33+s[i]))%217;
       i++;
       }
    a=a*M;
    a=(a-(int)a)*64;
    int b=a;
    return b;
   }
 void add(Journey j){
    int p = hashfunction(j.station1);
    for(int i=p; i<64;i++){
        if(jou[i].station1 == "!"){
             jou[i] = j;
             break;
        }
    }
    return;
 }

 void Querystation(Journey j){
    int p = hashfunction(j.station1);
    int q = 0;
   while((jou[p].station1 !="!")&&(p<64)){
      if((jou[p].station1==j.station1)&&(jou[p].strttm >= j.strttm)){
           cout<<jou[p].strttm<<" "<<jou[p].station2<<endl;
           q++;
      }
      p++;
   }
   if(q==0){
    cout<<"ERROR"<<endl;
   }
 }

 
 void Queryjourney(Journey j){
  int p =hashfunction(j.station1);
  float m = 0;
  float mintime=0;
   for(int i = p;i< 64;i++){
      if(jou[i].station1 == "!")
         break;
      if((jou[i].station1 == j.station1)&&(jou[i].station2 == j.station2)&&(jou[i].strttm>=j.strttm) ){
          if(m==0){
              mintime = jou[i].strttm;
          }
          else if(mintime>jou[i].strttm){
                  mintime = jou[i].strttm; 
          }
          m++;
     }
   }
   float t=0,time2,time1=0;
   string middle;
   for(int i = p;i<64;i++){
        if(jou[i].station1 == "!")
             break;
         if((jou[i].station1 == j.station1)&&(jou[i].strttm>=j.strttm)){
              int r = hashfunction(jou[i].station2);
                  for(int k=r;k<64;k++){
                    if(jou[k].station1 == "!") break;
                        if((jou[k].station2 == j.station2)&&(jou[k].strttm >= jou[i].endtm)){
                            if(t==0){
                                time1 = jou[i].strttm;
                                time2 = jou[k].strttm;
                                middle = jou[k].station1;
                            }
                            else if(time1 >  jou[i].strttm){
                                time1 = jou[i].strttm;
                                time2 = jou[k].strttm;
                                middle = jou[k].station1;
                            }
                            t++;
                        }
                  }
             }
        }
      if(t==0 && m==0){
        cout<<"ERROR"<<endl;
      }
      else if(t==0 && m != 0){
        cout<<mintime<<endl;
      }
      else if(t != 0&& m == 0){
        cout<<time1<<" "<<middle<<" "<<time2<<endl;
      }
      else if(t != 0&& m != 0){
          if(mintime<time1){
              cout<<mintime<<endl;
            }
        else{
            cout<<time1<<" "<<middle<<" "<<time2<<endl;
          }
      }
  } 
  
};

 
 
  // define suitable fields here


#endif