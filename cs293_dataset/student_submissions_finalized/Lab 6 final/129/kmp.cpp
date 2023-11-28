#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif
#include<bits/stdc++.h>
using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) //algorithm for finding hmatrix
{
  int l = pattern.length();
  int *z = new int[l];
  int x = 0;
  if (l == 0)
    return nullptr;
  z[0] = 0;
  for (int i = 1; i < l; i++)
  {
    if (pattern[z[i - 1]] == pattern[i])
    {
      z[i] = z[i - 1] + 1; //just by observation
      x = z[i];
    }
    else
    {
      while (x != 0)
      {
        if (pattern[z[x - 1]] == pattern[i])  // we should now check for the prefixes of z[i-1]
        {
          z[i] = z[x - 1] + 1;
          x = z[i];
          break;
        }
        x = z[x - 1]; // decreasing x and looping continuously
      }
      if (x == 0)
      {
        if (pattern[0] == pattern[i])
        {
          z[i] = 1;
        }
        else
        {
          z[i] = 0;
        }
      }
    }
  }
  return z;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) 
{
  transform(text.begin(), text.end(), text.begin(), ::tolower);
  transform(pattern.begin(), pattern.end(), pattern.begin(), ::tolower);
  int s = 0;
  // int ans = 0;
  int *y = new int[pattern.length()];
  // y = computeHMatrixForKMP(pattern);
  y=hMatrix;
  if (text.length() >= pattern.length())
  {
    while (s <= text.length() - pattern.length())
    {
      // cout << "go" << endl; just for debugging 
      int k = -1;
      for (int i = s; i <= s + pattern.length() - 1; i++)
      {
        if (text[i] != pattern[i - s]) //normal checking
        {
          k = i;
          // cout<<k<<endl;
          break;
        }
      }
      if (k == -1) //meaning that the pattern matches
      {
        // ans += 1;
        // cout << ans << endl;
        return s;
        // s = s - y[pattern.length() - 1] + pattern.length();
      }
      else if (k - s == 0) //mismatch at first place itself
      {
        s = s + 1;
      }
      else
      {
        s = k - y[k - s - 1]; //increasing s
      }
    }
  }

  return -1;
}

#endif
