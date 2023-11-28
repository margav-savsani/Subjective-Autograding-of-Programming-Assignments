#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
  //Creating array
  int* matching=new int[pattern.length()];
  int len = 0;
  int l = pattern.length();
  matching[0] = 0;
  int i = 1;
  //Checking condition of i<l
  while (i < l)
  {
    //letters matching
    if (pattern[i] == pattern[len])
    {
      len++;
      matching[i] = len;
      i++;
    }
    else
    {
      if (len != 0)
      {
        len = matching[len - 1];
      }
      else
      {
        matching[i] = 0;
        i++;
      }
    }
  }
  //Returns matching
  return matching;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
  int T = text.length();
  int P = pattern.length();
  int i = 0;
  int j = 0;
  //Checks condition
  while (T - i >= P - j)
  {
    if ((pattern[j] == text[i] )||(toupper(pattern[j]) == toupper(text[i]) ))
    {
      i++;
      j++;
    }
    if (j == P)
    {
      return i - j;
    }
    else if (i < T && toupper(pattern[j]) != toupper(text[i]))
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
  //if nothing is there returns -1
  return -1;
}

#endif
