#include <iostream>
#include <string.h>
#include <cmath>

#ifndef PLANNER_H
#define PLANNER_H

using namespace std;

struct Station
{
  // define suitable fields here
  string start_st, end_st;
  float start_t, finish_t;
  bool check;
  Station()
  {
    start_st;
    end_st;
    start_t = 0;
    finish_t = 0;
    check = false;
  }
};

struct Journey
{
  // define suitable fields here
};

struct Query
{
  // define suitable fields here
};
class Planner
{
  // define suitable fields here
  int N = 64;
  Station *data;
  public:
  Planner(){
    data = new Station[64];
  }
  int hashvalue(string key)
  {
    int i = 0;
    int sum = 0;
    while (key[i] != 0)
    {
      sum = (sum + int(key[i])) * 37;
      i++;
    }
    double final_hash, a = (sqrt(5) - 1) / 2;
    final_hash = sum;
    final_hash *= a;
    final_hash = (final_hash - floor(final_hash)) * N;
    final_hash = floor(final_hash);
    return final_hash;
  }
  int findFreeIndex(string key)
  {
    int k = hashvalue(key);
    for (int i = 0; i < N; i++)
    {
      if(data[k].check == false)
        return -1;
      else
        k = (k +1)%N;
    
    }
  return -1;
  }

  bool add(string start, string end, float tstart, float tend){
    int i = findFreeIndex(start);
    if(i != -1)
      {
        data[i].start_st = start;
        data[i].end_st = end;
        data[i].start_t = tstart;
        data[i].finish_t = tend;
        data[i].check = true;
        return true;
      }
    return false;
  }
};


#endif