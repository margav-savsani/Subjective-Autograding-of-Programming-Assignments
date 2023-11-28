#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
  int M = pattern.length();
  int len = 0;
  int *hArray;
  hArray[0] = 0; //always zero
  int i = 0;
  while (i < M)
  {
    if (pattern.at(i) == pattern.at(len))
    {
      len++;
      hArray[i] = len;
      i++;
    }
    else // (pat[i] != pat[len])
    {
      if (len != 0)
      {
        len = hArray[len - 1];
      }
      else // if (len == 0)
      {
        hArray[i] = 0;
        i++;
      }
    }
  }
  return hArray;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
  int M = pattern.length();
  int N = text.length();

  int i = 0;//index for text
  int j = 0;//index for pattern
  while ((N - i) >= (M - j))
  {
    if (pattern.at(i) == text.at(i))
    {
      j++;
      i++;
    }
    if (j == M)
    {
      return i - j; //index of first match
      j = hMatrix[j - 1];
    }
    else if (i < N && pattern.at(j) != text.at(i))
    {
      if (j != 0)
        j = hMatrix[j - 1];
      else
        i = i + 1;
    }
  }

  return 0;
}

#endif
