#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#include <string.h>
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
  int len = pattern.size();
  int *Harray = new int[len];
  Harray[0] = 0;
  int check = 1;
  int match, temp;
  while (check < len)
  {
    for (match = check; match > 0; match--)
    {
      for (temp = 0; temp < match; temp++)
      {
        if (pattern[temp] != pattern[check - match + temp + 1])
          break;
      }
      if (temp == match)
      {
        if (pattern[match] != pattern[check + 1])
        {
          Harray[check++] = match;
          break;
        }
      }
    }
    if (match == 0)
    {
      Harray[check++] = 0;
    }
  }

  return Harray;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
  int plen = pattern.size(), tlen = text.size();
  int cur = 0, match = 0, count = 0;
  while (cur < tlen)
  {
    match = 0;
    if (text[cur] != pattern[match])
    {
      cur++;
      continue;
    }
    while (match < plen)
    {
      if (text[cur] != pattern[match])
        break;
      else
      {
        cur++;
        match++;
      }
    }
    if (match == plen)
    {
      return cur - plen;
    }
    else
    {
      cur = cur - hMatrix[match - 1];
    }
  }
  return -1;
}

#endif
