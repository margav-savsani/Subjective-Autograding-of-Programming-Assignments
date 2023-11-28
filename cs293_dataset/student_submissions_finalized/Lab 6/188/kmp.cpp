#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  unsigned int len = pattern.length();
  int *hMatrix = new int[len];
  char text[len];
  hMatrix[0] = 0;
  pattern.copy(text, len);
  text[0] = '$';
  
  return nullptr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  return 0;
}

#endif
