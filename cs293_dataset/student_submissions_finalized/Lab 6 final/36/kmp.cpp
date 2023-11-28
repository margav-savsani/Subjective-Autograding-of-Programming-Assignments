#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
  int n = pattern.size();
  int *h;
  h = new int[n];
  h[0] = 0;
  int i = 1, hh = 0;
  while (i < n)
  {
    if (pattern[i] == pattern[hh])
    {
      h[i] = hh + 1;
      hh++;
      i++;
    }
    else if (hh == 0)
    {
      h[i] = 0;
      i++;
    }
    else
    {
      hh = h[hh - 1];
    }
  }
  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
  int l=text.size();
  int i=0;  //text
  int j=0;  //harray

  while(i<l) {
    if (pattern[j]==text[i]) {
      i++;
      j++;
    }
    else {
      if (j==0) {
        i++;
      }
      else {
        j=hMatrix[j-1]; 
      }
    }
    if (j==pattern.size()) {
      return i-pattern.size();
    }
  }
  return -1;
}

#endif
