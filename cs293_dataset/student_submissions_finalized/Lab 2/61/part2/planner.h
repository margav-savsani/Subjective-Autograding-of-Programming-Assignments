#ifndef PLANNER_H
#define PLANNER_H
#include<iostream>
using namespace std;
//Note for TA: I have not explicitly used the dictionary created in the inlab. Instead, I have implemented the dictionary within the planner class itself.
#include<vector>
#include<string>
#include<cmath>
struct station {
  string name;
    vector<struct train> trains;
    bool null;
    station(){
        null=true;
    }
};

struct train{
    string stn1;
    int st_time;
    string stn2;
    int end_time;
};

struct Query{
  // define suitable fields here
};


class planner {

    private:
    station stations[64];
    const int N=64;
    public:
      int hashValue(string s);
      bool findlocation_insert(train t);
      vector<train> query1(string stn, int start);
      void query2(string begin,int start,string end);
};

#endif
