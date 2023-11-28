#ifndef PLANNER_H
#define PLANNER_H
#include"dictionary2.h"

struct Station {
   string name;
   Station(string s){
     name=s;
   }
   Station(){}
};
struct Journey {
   Station station_1;
   Station station_2;
   float start_time;
   float end_time;
   Journey(string s1,float f1,string s2,float f2){
       station_1.name=s1;
       station_2.name=s2;
       start_time=f1;
       end_time=f2;
   }
};
struct Query{
   string operation;
   string s1;
   float t1;
   string s2;
   float t2;
   Query(string a1,float f1, string a2, float f2){
       s1=a1;  t1=f1;  s2=a2;  t2=f2;
   }
   Query(){}
};

class Planner{
   Query* q;
   Dictionary d1;
   Dictionary d2;
public:
   Planner(Query* a){
      q=new Query[20];
      q=a;
   }
   void Handling_queries(){
       for(int i=0;i<20;i++){
         if(q[i].operation=="ADD"){
           Entry station_1(q[i].s1,q[i].t1);
           Entry station_2(q[i].s2,q[i].t2);
           int a=d1.put(station_1);
           int b=d2.put(station_2);
           if(a==-1){
             cout<<"dictionary-1 is full"<<endl;
             continue;
           }
           if(b==-1){
             cout<<"dictionary-2 is full"<<endl;
             continue;
           }
           int c=d1.find(q[i].s1);
           int d=d2.find(q[i].s2);
           station_1.value=b;
           station_2.value=a;
           d1.A[a].t.QInsert(q[i].t1,b,q[i].t2);
           d2.A[b].t.QInsert(q[i].t2,a,q[i].t1);
         }
         else if(q[i].operation=="QUERY_STATION"){
           int a=d1.find(q[i].s1);
           if(a<0 || a==65) cout<<"station not found"<<endl;
           else{
              Entry b=d1.A[a];
              DynamicQueue c=b.t;
              int j=c.get_head(),size=c.get_N();
              while(j!=c.get_tail()){
                 if(c.A[j][0]>=q[i].t1){
                    int num=(int)c.A[j][1];
                    Entry d=d2.A[num];
                    string s=d.name;
                    cout<<c.A[j][0]<<" "<<s<<endl;
                 }
                 j=(j+1)%size;
              } 
           } 
         }
         else if(q[i].operation=="QUERY_JOURNEY"){
           int a=d1.get_index(q[i].s1);
           float e=0.001;
           if(a<0 || a==65) cout<<"station-1 not found"<<endl;
           else{
              int found=0;
              Entry b=d1.A[a];
              DynamicQueue c=b.t;
              int d=d2.get_index(q[i].s2);
              Entry z=d2.A[d];
              DynamicQueue g=z.t;
              int j=c.get_head(),size=c.get_N();
              float minimum=2500;
              while(j!=c.get_tail()){
                 if(abs(c.A[j][1]-d)<e){
                     if(c.A[j][0]>q[i].t1)minimum=min(minimum,c.A[j][0]-q[i].t1);
                     else minimum=min(minimum,24-q[i].t1+c.A[j][0]);
                     found=1;
                 }
                 j=(j+1)%size;
              }
              float min_1=minimum;
              j=c.get_head();
              float x;
              string s;
              float p,r;
              while(j!=c.get_tail()){
                 if(abs(c.A[j][1]-d)>1){
                    if(c.A[j][0]>q[i].t1) x=c.A[j][0]-q[i].t1;
                    else x=2400-q[i].t1+c.A[j][0];
                    int h=(int)c.A[j][1];
                    Entry y=d2.A[h];
                    int num1=d1.get_index(y.name);
                    if(num1>-1){
                       Entry v=d1.A[num1];
                       DynamicQueue u=v.t;
                       float k=d;
                       int num2=u.find_index(k);
                       if(x<minimum && num2!=-1){
                          minimum=x;
                          p=c.A[j][0];
                          s=y.name;
                          r=u.A[num2][0];
                          found=1;
                       }
                    }
                 }   
                 j=(j+1)%size;    
              }
              if(found==0) cout<<"ERROR"<<endl;
              else{
                 if(abs(minimum-min_1)<e){
                   int minima=(int)q[i].t1+minimum;
                   if(minimum+q[i].t1<2400)cout<<minima<<endl;
                   else cout<<(minima)%24<<endl;
                 }
                 else cout<<p<<" "<<s<<" "<<r<<endl;
              }
           } 
         }
         else if(q[i].operation=="EXIT"){
            break;                                                                                      
         }
      } 
   }
};

#endif
