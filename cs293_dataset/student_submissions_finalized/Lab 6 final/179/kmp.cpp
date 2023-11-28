#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int n = pattern.length();
  int lps[n];
  int len = 0;
  lps[0] = 0;
  int i = 1;
  while (i < n) {
      if (pattern[i] == pattern[len]) {
          len++;
          lps[i] = len;
          i++;
      }
      else 
      {
          if (len != 0) {
              len = lps[len - 1]; 
          }
          else
          {
              lps[i] = 0;
              i++;
          }
      }
  }
  return lps;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int n = text.length();
  int m = pattern.length();
  int i = 0;
  int j = 0;
  int count = 0;
  int k;
  while(i<n){
    while(j<m && text[i]==pattern[j]){
      i++;
      j++;
      if(i>=n) break;
    }
    if(i>=n) break;
    if(j==m){
      count++;
      j=0;
      continue;
    }
    else {
      if(j==0){
        i++;
        continue;
      }
      else {
        k = hMatrix[j-1];
        i = i-j+k;
        j = k;
        continue;
      }
    }
  }
  return count;
}

#endif
