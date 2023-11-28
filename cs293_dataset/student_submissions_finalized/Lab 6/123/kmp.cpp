#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {

  return nullptr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int m = pattern.size();
  int n = text.size();
  int i = 0;
  int j = 0;
  while((n-i)>=(m-j)){
    if(pattern[j] == text[i]){
      j++;
      i++;
    }
    if(j == m){
      j = hMatrix[j-1];
    }
    else if(i<n && pattern[j] != text[i]){
      if(j != 0){
        j = hMatrix[j-1];
      }
      else{
        i++;
      }
    }
  }
}

#endif
