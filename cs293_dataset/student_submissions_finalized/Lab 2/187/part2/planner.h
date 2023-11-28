#ifndef PLANNER_H
#define PLANNER_H
#include<string>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct station{
  string s;
  float t;
};
struct query{
  float t1;
string intermediate;
float t2;
};
struct Journey {
  station st1,st2;
};
class Planner{
  private:
    Journey *j;
    int nos=0;
  public:
    Planner(){
      j = new Journey[64];
      
    }
    void add(string s1, float a, string s2, float b){
      j[nos].st1.s = s1;
      j[nos].st1.t = a;
      j[nos].st2.s = s2;
      j[nos].st2.t = b;
      nos++;
    }
    void querystation(string s1, float a){
     int  count = 0;
      for(int i=0;i<nos;i++){
        if(j[i].st1.s == s1 && j[i].st1.t > a){
          cout << j[i].st1.t << " " << j[i].st2.s  << endl;
          count++;
        }
    }
    if(count == 0){
      cout << "ERROR" << endl;
    }
  }
 float min_time(string s1, float a, string s2){
    vector<float> v;
    for(int i=0;i<nos;i++){
      if(j[i].st1.s == s1 && j[i].st2.s == s2){
        v.push_back(j[i].st1.t);
      }
    }
    for(int i=0;i<v.size();i++){
      if(v[i] < a) v.erase(v.begin()+i);
    }
    return *min_element(v.begin(),v.end());
  }
  void query_journey(string s1,float a,string s2){
  query q;
  for(int i=0;i<nos;i++){
    float b;
    if(j[i].st1.s == s1){
      if(j[i].st2.s == s2) {b = min_time(j[i].st1.s,a,j[i].st2.s); q.t1 = b; q.intermediate = "-1"; q.t2 = -1;}
      for(int j1 = 0;j1<nos;j1++){
        if(j[i].st2.s == j[j1].st1.s && j[j1].st2.s == s2){
          if(j[i].st1.t > a && j[i].st1.t < b){
            b = j[i].st1.t;
            q.t1 = b;
            q.intermediate = j[j1].st1.s;
            q.t2 = j[j1].st1.t;
        }
        }

 }
}
}
 cout << q.t1<<" ";
 if(q.intermediate!="-1"){
  cout<<q.intermediate<<" "<<q.t2;
 }
 cout<<endl;

}
};
#endif
