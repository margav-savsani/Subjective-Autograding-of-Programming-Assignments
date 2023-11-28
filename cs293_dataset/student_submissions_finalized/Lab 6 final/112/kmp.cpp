#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
  int M = pattern.length();
  int *h = new int[M]; // h[i] = h(i+1)

  h[0] = 0;
  int i = 1;
  int prev = 0;
  while (i < M) // compute h[1 to M-1]
  {
    if (pattern[i] == pattern[prev])
    {
      h[i] = prev + 1;
      prev++;
      i++;
    }
    else if (prev == 0)
    {
      h[i] = 0;
      i++;
    }
    else
    {
      prev = h[prev - 1];
    }
  }
  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
  int loc = 0; // location of the text where the pattern currently is. loc <= text.length()-m
  while (loc <= text.length() - pattern.length())
  {
    int i = 0;
    while (pattern[i] == text[loc + i])
    {
      i++;
    }
    if (i == pattern.length())
    {
      return loc;
    }
    // pattern[0...i-1] matches and pattern[i] is mismatched
    // shift forward by i-h[i-1] if i is nonzero
    if (i == 0)
    {
      loc += 1;
    }
    else
    {
      loc += i - hMatrix[i - 1];
    }
  }
  return -1; // not found
}

#endif
