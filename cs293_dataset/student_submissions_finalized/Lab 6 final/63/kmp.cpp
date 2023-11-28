#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {  
/* computing the h[i] matrix. h[i] denotes the shift if match/mismatch is at i+1 */  
  int len = pattern.length();
  int *a = new int[len];
  a[0] = 0;
  int i = 0;
  for (int j = 1; j < len; j++){
    while (i > 0 && pattern[i] != pattern[j-1]){
      i = a[i];
    }
    if (pattern[i] == pattern[j-1]){
      i += 1;
    }
    a[j] = i-1;
  }
  return a;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern){
  // normal KMP algorithm
  int m = pattern.length();
  int n = text.length();
  int j = 0;
  int num = 0;
  for (int i = 0; i < n; i++){
    if (i+m >= n){
      break;
    }
    while (j > 0 && pattern[j] != text[i]){
      j = hMatrix[j];
    }
    if (pattern[j] == text[i]){
      j += 1;
    }
    if (j == m-1){
      num += 1;
      return i-m+2;   // returns the start index of the first match
    }
  }
  return -1;
}

#endif
