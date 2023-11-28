#ifndef PLANNER_H
#define PLANNER_H
#include "dictionary.cpp"
#include <iostream>
#include <string.h>
#include <climits>
using namespace std;
class Planner
{
public:
  Dictionary D;

public:
  void add_root(char starting_station[32], float starting_time, char ending_station[32], float ending_time)
  {
    Entry e;
    for (int i = 0; i < 32; i++)
    {
      e.starting_station[i] = starting_station[i];
    }
    for (int i = 0; i < 32; i++)
    {
      e.ending_station[i] = ending_station[i];
    }
    e.starting_time = starting_time;
    e.ending_time = ending_time;
    D.put(e);
  }
  bool compare(char a[32], char b[32])
  {
    for (int i = 0; i < 32; i++)
    {
      if (a[i] != b[i])
        return false;
    }
    return true;
  }
  void Query_Staion(char station_one[32], float start_time)
  {
    int a = D.hashValue(station_one);

    int r = 0;
    for (int i = a; i != (a - 1); i = (i + 1) % (D.N))
    {
      if (D.A[i].ending_time == -1 || D.A[i].starting_time == -1)
      {
        break;
      }
      else if (compare(D.A[i].starting_station, station_one) && D.A[i].starting_time >= start_time)
      {
        cout << D.A[i].starting_time << "  " << D.A[i].ending_station << endl;
        r++;
      }
    }
    if (r == 0)
    {
      cout << station_one << "is not exist " << endl;
    }
  }

  void QUERY_JOURNEY(char station_one[32], float start_time, char station_two[32])
  {
  
    int p, q, r = INT_MAX,a=0,m=0,t,n;
    for ( int i = 0; i < D.N; i++)
    {
      if (D.A[i].starting_time == -1 || !(compare(D.A[i].ending_station, station_two)))
      {
        continue;
      }
      int j = D.hashValue(station_one);
      
      for (p = j; p != (j - 1); p = (p + 1) % (D.N))
      {
        if (compare(D.A[p].starting_station, station_one) && D.A[p].starting_time >= start_time && compare(D.A[p].ending_station, D.A[i].starting_station))
        {
          if ((D.A[p].starting_time - start_time) < r)
          {
            r = D.A[p].starting_time - start_time;
            t=i;
            q = p;
          }
          a++;
        }
      }
    }
    int s=D.hashValue(station_one);
  for(int i=s;i!=(s-1);i++){
    if(D.A[i].starting_time==-1){
      break;
    }
    else if(D.A[i].starting_time>=start_time&&compare(D.A[i].starting_station,station_one)&&compare(D.A[i].ending_station,station_two)){
      if(D.A[i].starting_time-start_time<r){
        r=D.A[i].starting_time-start_time;
        n=i;
        m++;
      }
    }
  }
  if(m>0){cout<<D.A[n].starting_time<<endl;}
    if (a > 0&&m==0)
    {
      cout << D.A[q].starting_time << "  " << D.A[q].ending_station << "  " << D.A[t].starting_time << endl;
    }
  
  if (a == 0&&m==0)
  {
    cout << "ERROR" << endl;
  }}
 ~Planner()
{
}
// define suitable fields here
}
;

#endif