#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
  int m = pattern.size();
  int *h;
  h = new int[m];
  h[0] = 0;
  int l = 0, i = 1;
  while (i < m)
  {
    if (pattern[i] == pattern[l])
    {
      l++;
      h[i] = l;
      i++;
    }
    else
    {
      if (l != 0)
      {
        l = h[l - 1];
      }
      else
      {
        h[i] = 0;
        i++;
      }
    }
  }
  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
  int n = text.size();
  int m = pattern.size();
  int i = 0;
  int j = 0;
  for (int i = 0; i < m; i++)
  {
    cout << hMatrix[i] << " ";
  }
  cout << endl;
  while (m - 1 < n - i)
  {
    int ini = j;
    for (; ini < m; ini++)
    {
      // cout << text[i+ini] << " " << pattern[ini] << endl;
      if (text[i + ini] == pattern[ini])
      { // cout << "Text Character " << text[i+ini] << endl;
        // cout << "Pattern Character " << pattern[ini] << endl;
        continue;
      }
      else
        break;
    }
    if (ini == m)
      return 0;
    else
    {
      if (j == 0)
      {
        i++;
      }
      else
      {
        i = i + ini - j;
        j = hMatrix[ini - 1];
      }
      // std::cout << i << endl;
    }
  }
  return -1;
}

#endif
