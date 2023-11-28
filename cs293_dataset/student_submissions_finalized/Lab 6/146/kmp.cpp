#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int s = pattern.size();
  int k;
  int hMatrix[s];
  hMatrix[0] = 0;
  for(int i = 2; i<=s ; i++){
      k = hMatrix[i-2];
      while(k>0 && pattern[i-1]!=pattern[k]){
          k = hMatrix[k-1];
      }
      if(k==0){
          if(pattern[0] == pattern[i-1]) hMatrix[i-1] = 1;
          else hMatrix[i-1] = 0;
      }
      else {
          hMatrix[i-1] = k+1;
      }
  }
  return hMatrix; 
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  
  return 0;
}

#endif
