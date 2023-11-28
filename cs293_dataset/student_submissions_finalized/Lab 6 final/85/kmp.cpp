#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
  string p = pattern;
  int k = pattern.length();
  int *h = new int[k];
  h[0] = 0;
  int u;
  for (int i = 1; i < k; i++)
  {

    for (u = i; u > 0; u--)
    {
      int j = 0;

      while (j < u)
      {

        if (p[j] != p[i - u + 1 + j])
        {
          break;
        }
        else
        {
          j++;
        }
      }
      if (j == u)
      {
        if (p[j] != p[i + 1])
        {
          h[i] = j;
          break;
        }
      }
    }
    if (p[0] != p[i] && u == 0)
    {
      h[i] = 0;
    }
  }

  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
  int k = text.length();
  int m = pattern.length();
  int j = 0;
  for (int i = 0; i < k; i++)
  {
    if (text[i] != pattern[j])
    {
      continue;
    }
    if (text[i] == pattern[j])
    {
      j++;
      if (j == m)
      {
        return i - j + 1;
      }
      if (text[i + 1] != pattern[j])
      {
        i = i - hMatrix[i] + 1;
        j = 0;
        continue;
      }
    }
    else
    {

      continue;
    }
  }
  return -1;
}
#endif
