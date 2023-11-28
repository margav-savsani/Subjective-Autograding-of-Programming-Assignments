#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
  int match[pattern.length()];
  int len = 0;
  int l = pattern.length();
  match[0] = 0;
  int i = 1;
  while (i < l)
  {
    if (pattern[i] == pattern[len])
    {
      len++;
      match[i] = len;
      i++;
    }
    else
    {
      if (len != 0)
      {
        len = match[len - 1];
      }
      else
      {
        match[i] = 0;
        i++;
      }
    }
  }
  return match;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
  int T = text.length();
  int P = pattern.length();
  int i = 0;
  int j = 0;
  while (T - i >= P - j)
  {
    if (pattern[j] == text[i])
    {
      i++;
      j++;
    }
    if (j == P)
    {
      return i - j;
    }
    else if (i < T && pattern[j] != text[i])
    {
      if (j != 0)
      {
        j = hMatrix[j - 1];
      }
      else
      {
        i = i + 1;
      }
    }
  }
  return -1;
}

#endif
