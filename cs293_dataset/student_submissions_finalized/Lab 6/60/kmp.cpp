#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
  int M = strlen(pattern);
  int lps[M];
  computeHMatrixForKMP(pattern);

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
      return nullptr;
    }

    else if (i < N && pattern[j] != text[i])
    {
      if (j != 0)
        j = lps[j - 1];
      else
        i = i + 1;
    }
  }
  return nullptr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{

  return 0;
}

#endif
