#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;
int *Planner::computeHMatrixForKMP(string pattern)
{
  int M = size(pattern);
  int *lps;
  int len = 0;
  lps[0] = 0;
  int i = 1;
  while (i < M)
  {
    if (pattern[i] == pattern[len])
    {
      len++;
      lps[i] = len;
      i++;
    }
    else
    {
      if (len != 0)
      {
        len = lps[len - i];
      }
      else
      {
        lps[i] = 0;
        i++;
      }
    }
  }
  return lps;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{

  int m = size(text);
  int n = size(pattern);
  hMatrix = computeHMatrixForKMP(pattern);
  int i = 0;
  int j = 0;
  while ((m - i) >= (n - j))
  {
    /* code */
    if(pattern[j] == text[i])
    {
      i++;
      j++;
    }
    if(j == n)
    {
      j = hMatrix[j - 1];
    }
    else if(i < m && pattern[j] != text[i])
    {
      /* code */
      if(j != 0)
        j = hMatrix[j-1];
      else
        i = i + 1;
    }
  }
  return j;
}

#endif

