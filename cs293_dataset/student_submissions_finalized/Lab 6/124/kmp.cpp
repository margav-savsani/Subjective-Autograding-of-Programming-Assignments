#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
  int *hmatrix;
  int x=0;
  hmatrix[0] = 0;
  int i = 1;
  int count_pattern = 0;
  for (int i = 0; pattern[i] != '\0'; i++)
  {
    count_pattern++;
  }
  while (i < count_pattern)
  {
    if (pattern[i] == pattern[x])
    {
      x++;
      hmatrix[i] = x;
      i++;
    }
    else
    {

      if (x!= 0)
      {
        x= hmatrix[x - 1];
      }
      else
      {
        hmatrix[i] = 0;
        i++;
      }
    }
  }

  return nullptr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
  int count_text = 0;
  for (int i = 0; text[i] != '\0'; i++)
  {
    count_text++;
  }
  int count_pattern = 0;
  for (int i = 0; pattern[i] != '\0'; i++)
  {
    count_pattern++;
  }
  hMatrix[count_pattern];
  computeHMatrixForKMP(pattern);
  int i, j = 0;
  while ((count_text - i) >= (count_pattern - j))
  {
    if (pattern[j] == text[i])
    {
      j++;
      i++;
    }

    if (j == count_pattern)
    {
      return i;
      j = hMatrix[j - 1];
    }
    else if (i < count_text && pattern[j] != text[i])
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
