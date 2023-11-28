#ifndef PLANNER_H
#define PLANNER_H
#include <string>
#include <iostream>
using namespace std;

const int journs = 64;                  //size of every station

int hashValue(string key)
{
  int i = key.length() - 1;
  int temp = key[i] % 500;
  while (i > 0)
  {
    int p = (temp * 37) % 500 + key[i - 1] % 500;
    temp = p % 500;
    i--;
  }

  double a = 0.618;                                  // using fibonacci hashing
  double ka = a * temp;
  int KA = a * temp;
  double rem = ka - KA;
  int final_key = rem * journs;
  return final_key;
}

struct journey                    
{
  // define suitable fields here
  float strt_time;
  float end_time;
  string final_dest;
};

struct pairs
{
  float late_time;
  string code;
};

class container                                             // this will contain last(by time) trian between any two stations
{
  pairs mytime[journs];

public:
  container()
  {
    for (int i = 0; i < journs; i++)
    {
      mytime[i].code = "null";
    }
  }

  void update(string strt, string end, float timing)
  {
    pairs p_ = {timing, strt + end};
    int n = hashValue(strt + end);                                  // hash using name of both the stations
    int p = n;
    while (true)
    {
      if (mytime[n].code == "null")
      {
        mytime[n] = p_;
        return;
      }
      else if (mytime[n].code == strt+end) 
      {
        if (timing > (mytime[n]).late_time)
        {
          mytime[n] = p_;
        }
        return;
      }
      n = (n + 1) % journs;
      if (n == p)
      {
        cout << "cannot be added ..list full" << endl;
        break;
      }
    }
  }

  bool is_available(string strt, string end, float timing)              //checks if there is any train after given time between two stations
  {
    pairs p_ = {timing, strt + end};
    int n = hashValue(strt + end);
    int p = n;
    while (true)
    {
      if (mytime[n].code == "null")
      {
        return false;
      }
      else if (mytime[n].code == strt+end)
      {
        if ((mytime[n]).late_time >= timing)
        {
          return true;
        }
        else
        {
          return false;
        }
      }
      n = (n + 1) % journs;
      if (n == p)
      {
        break;
      }
    }
    return false;
  }

  float timings(string strt, string end, float timing)              // if train exist in check available function!! this function returns time
  {
    {
      pairs p_ = {timing, strt + end};
      int n = hashValue(strt + end);
      int p = n;
      while (true)
      {
        if (mytime[n].code == "null")
        {
          return 0.5;
        }
        else if (mytime[n].code == strt+end)
        {
          if ((mytime[n]).late_time >= timing)
          {
            return (mytime[n]).late_time;
          }
          else
            return 0.5;
        }
        n = (n + 1) % journs;
        if (n == p)
        {
          break;
        }
      }
      return false;
    }
    return 0.5;
  }
};

container c;                                    //made the container accessible by both class sttion and station_grp

class station
{
  struct journey arr[journs];
  int filled;

public:
  station()
  {
    filled = 0;
  }
  void add(journey &j)
  {
    bool breaked = false;
    int i;
    for (i = 0; i < filled; i++)
    {
      if (j.strt_time < arr[i].strt_time)
      {
        breaked = true;
        break;
      }
    }

    if (breaked == false)
    {
      arr[i].strt_time = j.strt_time;
      arr[i].final_dest = j.final_dest;
      arr[i].end_time = j.end_time;
    }
    else
    {
      struct journey temp = arr[i];
      arr[i].strt_time = j.strt_time;
      arr[i].final_dest = j.final_dest;
      arr[i].end_time = j.end_time;
      int p;
      for (p = filled; p > i + 1; p--)
      {
        arr[p] = arr[p - 1];
      }
      arr[p] = temp;
    }
    filled++;
  }

  void display(float &min)
  {
    for (int i = 0; i < filled; i++)
    {
      if (arr[i].strt_time >= min)
      {
        cout << arr[i].strt_time << "  " << arr[i].final_dest << endl;
      }
    }
  }

  bool find(string st1, float strt, string st2)                                //find function for Query_journey
  {
    for (int i = 0; i < filled; i++)
    {
      if (arr[i].strt_time >= strt)
      {
        if (arr[i].final_dest == st2)
        {
          cout << arr[i].strt_time << endl;
          return true;
        }
        if (c.is_available(arr[i].final_dest, st2, arr[i].end_time))
        {
          cout << arr[i].strt_time << " " << arr[i].final_dest << " " << c.timings(arr[i].final_dest, st2, arr[i].end_time) << endl;
          return true;
        }
      }
    }
    return false;
  }
};

struct station_pair
{
  string name;
  station mystation;
};

class station_grp                  
{
  station_pair stat_grp[64];                       // array ciontaining all stations ie journeys starting from that station 

public:
  station_grp()
  {
    for (int i = 0; i < 64; i++)
    {
      stat_grp[i].name = "null";
    }
  }

  void add(string start_, float start, string end_dest, float end)                     // final add function
  {
    journey j = {start, end, end_dest};
    int n = hashValue(start_);
    int p = n;
    c.update(start_, end_dest, start);
    while (true)
    {
      if (stat_grp[n].name == "null")
      {
        stat_grp[n].name = start_;
        stat_grp[n].mystation.add(j);
        return;
      }
      else if (stat_grp[n].name == start_)
      {
        stat_grp[n].mystation.add(j);
        return;
      }
      n = (n + 1) % journs;
      if (n == p)
      {
        cout << "cannot be added ..list full" << endl;
        break;
      }
    }
  }

  void display(string strt, float min)                                                // final query_station function
  {
    int n = hashValue(strt);
    int p = n;
    while (true)
    {
      if (stat_grp[n].name == "null")
      {
        cout << "staion do  not exist" << endl;
        return;
      }
      else if (stat_grp[n].name == strt)
      {
        stat_grp[n].mystation.display(min);
        return;
      }
      n = (n + 1) % journs;
      if (n == p)
      {
        break;
      }
    }
  }

  bool journey_(string s1, float timess, string s2)                              // final query journy function
  {
    int n = hashValue(s1);
    int p = n;
    while (true)
    {
      if (stat_grp[n].name == "null")
      {
        cout << "station do not exist for this journey" << endl;
        return false;
      }
      else if (stat_grp[n].name == s1)
      {
        if (stat_grp[n].mystation.find(s1, timess, s2))
        {
          return true;
        }
        else
        {
          cout << "ERROR" << endl;
          return false;
        }
      }
      n = (n + 1) % journs;
      if (n == p)
      {
        break;
      }
    }
    return false;
  }
};

#endif