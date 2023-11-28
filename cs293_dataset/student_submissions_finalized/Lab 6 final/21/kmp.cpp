#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int len = pattern.length();
  int* h = new int(0);
  for (int i = 1; i<len; i++){
    int t=0;
    int j = i;
    while(pattern[h[j-1]] != pattern[i]){
      if (h[j-1] == 0) {h[i]=0;t=1;break;};
      j = h[j-1];
    } 
    if (t==1) {
        continue;
    }
    h[i] = h[j-1] + 1;
  }
  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern){
  int i=0;
  int j=0;
  int lt = text.length();
  int lp = pattern.length();
 while(i+lp <= lt+j){
    if (j == lp - 1 && pattern[j] == text[i]){
      return (i-j);
    }
    else if (pattern[j] != text[i]){
      if (j == 0) i++; 
      else j = hMatrix[j-1];
    }
    else if (pattern[j] == text[i]){
      j++;
      i++;
    }
  }
  
  return -1;
}

#endif
