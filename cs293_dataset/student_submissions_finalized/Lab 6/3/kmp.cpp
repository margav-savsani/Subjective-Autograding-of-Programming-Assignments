#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int h[pattern.size()];
  h[0] = 0;
  for (int i = 1;i<pattern.size();i++) {
    if (pattern[i-1] == pattern[i-1-h[i-1]])
  }

  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  return 0;
}

#endif
