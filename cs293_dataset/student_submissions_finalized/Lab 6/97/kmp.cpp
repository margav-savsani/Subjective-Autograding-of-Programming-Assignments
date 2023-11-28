#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int len = pattern.length();
  int h[len] = {0};
  int prev = 0, i = 1;
  while(i < pattern.length()){
    if(pattern[i] == pattern[prev]){
      h[i] = prev + 1;
      prev++;
      i++;
    }
    else if(prev == 0){
      h[i] = 0;
      i++;
    }
    else
      prev = h[prev - 1];
  }
  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int i = 0, j = 0;
  while(i < text.length()){
    if(text[i] == pattern[i]){
      i++;
      j++;
    }
    else{
      if(j == 0)
        i++;
      else
        j = hMatrix[j-1]
    }
  }
  return 0;
}

#endif
