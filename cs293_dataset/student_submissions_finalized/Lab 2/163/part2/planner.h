#ifndef PLANNER_H
#define PLANNER_H
#define INT_MAX 2147483647

#include <iostream>
#include <bits/stdc++.h>
#include <string>
using namespace std;

char *null = new char[32];

struct Journey
{
  // define suitable fields here
  string station_one = null, station_two; // station_one is our key
  float start_time, finish_time;
};

struct Query
{
  // define suitable fields here
  float time1, time2; // query to print required data
  string stop;
};

bool compare(Query a, Query b)
{
  return a.time1 < b.time1; // defineing sort function to sort according to time
}

class Planner
{
  // define suitable fields here
private:
  int N;
  struct Journey *jour;

  float train_exist(string start, float time, string end, struct Query *ans, int &j)
  {
    int hash = hashValue(start);
    float min = INT_MAX;
    for (int i = hash; true; i = (i + 1) % N)
    {
      if (jour[i].station_one == start && jour[i].station_two == end && jour[i].start_time >= time)
      {
        if (min > jour[i].start_time) // searches all possible train from start to end after given time
          min = jour[i].start_time;   // and returns the start time of the earliest one
      }
      if (jour[i].station_one == null || i == (hash - 1 + N) % N)
        return min;
    }
  }

  void train_nostop(string start, float time, string end, struct Query *ans, int &j)
  {
    int hash = hashValue(start);
    for (int i = hash; true; i = (i + 1) % N)
    {
      if (jour[i].station_one == start && jour[i].station_two == end && jour[i].start_time >= time)
        ans[j++].time1 = jour[i].start_time; // all trains directly from start to end after given time are stored in the given array
      if (jour[i].station_one == null || i == (hash - 1 + N) % N)
        return;
    }
    return;
  }

public:
  Planner(int n = 100)
  {
    N = n; // by default max 100 journeys are allowed
    jour = new Journey[N];
  }

  int hashValue(string key)
  {
    long p = 31, pow = 1;
    int hash = 0;
    for (int i = 0; i < key.length(); i++)
    {
      hash = (hash + (key[i] - 'A') * pow) % N;
      pow = pow * p;
    }
    return hash; // hash value is calculated using polynomial accumulation method
  }
  int findFreeIndex(string key)
  {
    int hash = hashValue(key);
    for (int i = hash; true; i = (i + 1) % N)
    {
      if (jour[i].station_one == null)
        return i;
      if (i == (hash - 1 + N) % N)
        return -1;
    } // free slot is found and returned using linear probing
  }
  bool add(struct Journey e)
  {
    int index = findFreeIndex(e.station_one);
    if (index == -1)
      return false;
    jour[index] = e; // the journey is added the free index
    return true;
  }
  void query_station(string key, float time)
  {
    int j = 0, hash = hashValue(key);
    struct Query ans[N];
    bool found = false;
    for (int i = hash; true; i = (i + 1) % N)
    {
      if (jour[i].station_one == key && jour[i].start_time >= time)
      {
        ans[j].time1 = jour[i].start_time;
        ans[j++].stop = jour[i].station_two; // for the given station, info of all trains is stored as a query array
        // cout << jour[i].start_time << " " << jour[i].station_two << endl;
        found = true;
      }
      if (jour[i].station_one == null || i == (hash - 1 + N) % N)
      {
        if (!found)
          cout << "Station not Found." << endl;
        break;
      }
    }
    if (j == 0)
      return;
    sort(ans, ans + j, compare); // the query array is sorted according to start time
    for (int i = 0; i < j; i++)
      cout << ans[i].time1 << " " << ans[i].stop << endl; // all trains are listed in arranged order.
    return;
  }
  void query_journey(string start, float time, string dest)
  {
    struct Query ans[N];
    int j = 0, hash = hashValue(start);
    train_nostop(start, time, dest, ans, j); // direct trains info is added in the array

    for (int i = hash; true; i = (i + 1) % N)
    {
      if (jour[i].station_one == start && jour[i].station_two != dest && jour[i].start_time >= time)
      { // all journeys to other stations are considered
        float time2;
        time2 = train_exist(jour[i].station_two, jour[i].finish_time, dest, ans, j); // searches if train from the other station to thee destination exists
        if (time2 != INT_MAX)
        {
          ans[j].time1 = jour[i].start_time;
          ans[j].stop = jour[i].station_two;
          ans[j++].time2 = time2; // the data of all routes is stored
        }
      }
      if (jour[i].station_one == null || i == (hash - 1 + N) % N)
        break;
    }
    if (j == 0)
    {
      cout << "ERROR" << endl; // if no route found, error is printed
      return;
    }
    sort(ans, ans + j, compare); // the array is sorted according to start time

    cout << ans[0].time1 << " ";
    if (ans[0].stop != "")
      cout << ans[0].stop << " " << ans[0].time2;
    cout << endl; // the earliest route would be now at index 0, so it is printed
    return;
  }
};

#endif