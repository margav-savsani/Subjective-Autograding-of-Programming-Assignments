#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{

  int M = pattern.length();
  int L[M];
  L[0] = 0;
  int len = 0;
  int i = 1;
  while (i < M)
  {
    if (pattern[i] == pattern[len])
    {
      len++;
      L[i] = len;
      i++;
    }
    else
    {
      if (len != 0)
      {
        len = L[len - 1];
      }
      else
      {
        L[i] = 0;
        i++;
      }
    }
  }

  return L;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
  int M = pattern.length();
  int N = text.length();
  hMatrix = computeHMatrixForKMP(pattern);

  int i = 0;
  int j = 0;

  while ((N - i) >= (M - j))
  {
    if (pattern[j] == text[i])
    {
      j++;
      i++;
    }

    if (j == M)
    {
      return i - j;
      j = hMatrix[j - 1];
    }

    // mismatch after j matches
    else if (i < N && pattern[j] != text[i])
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
