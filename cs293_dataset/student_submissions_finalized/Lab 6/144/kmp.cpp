#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {

  int patternSize = pattern.size();
  if(patternSize == 0) return nullptr;

  int* hmatrix = new int[patternSize];

  hmatrix[0] = 0;

  for(int i = 1; i < patternSize; i++){
    int matchPrefixSuffix = hmatrix[i-1];

    while(true){
      if(matchPrefixSuffix == 0){
        pattern[0] == pattern[i] ? hmatrix[i] = 1 : hmatrix[i] = 0;
        break;
      }

      else{
        if(pattern[i] == pattern[matchPrefixSuffix]){
          hmatrix[i] = matchPrefixSuffix + 1;
          break;
        }

        else{
          matchPrefixSuffix = hmatrix[matchPrefixSuffix - 1];
        }
      }
    }
  }

  return hmatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  return 0;
}

#endif
