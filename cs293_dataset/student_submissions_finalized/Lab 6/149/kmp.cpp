#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
  int n = pattern.length();
  int i = 1, j = 0;
  int h[n];
  h[0] = 0;
  for (i = 1; i < n; i++)
  {
    if (pattern[i] == pattern[j]) h[i] = j++;
    else{
      if(j != 0){
        j = h[j-1];
        i--;
      }
      else h[i] = 0;
    }
  }

  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
  
  return 0;
}

#endif
