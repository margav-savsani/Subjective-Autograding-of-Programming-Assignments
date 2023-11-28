#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{

  int *h = new int[pattern.length()];

  h[0] = 0;
  int i = 1;

  while(i<pattern.length()){
    
  }

  return nullptr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{

  return 0;
}

#endif
