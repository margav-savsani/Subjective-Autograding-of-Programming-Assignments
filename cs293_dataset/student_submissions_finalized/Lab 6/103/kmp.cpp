#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int prevLen = 0;
  int* hMatrix = new int[pattern.length()];
  hMatrix[0] = 0;

  int idx = 1;
  while(idx < pattern.length()){
    if(pattern[idx] == pattern[prevLen]){
      prevLen++;
      hMatrix[idx] = prevLen;
      idx++;
    } else{
      if(prevLen != 0){
        prevLen = hMatrix[prevLen-1];
      } else{
        hMatrix[idx] = 0;
        idx++;
      }
    }
  }

  return hMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int idxTxt = 0;
  int idxPat = 0;

  while((text.length() - idxTxt) >= (pattern.length() - idxPat)){
    if(pattern[idxPat] == text[idxTxt]){
      idxTxt++;
      idxPat++;
    }
    if(idxPat == pattern.length()){
      return idxTxt - idxPat;
    } else if(idxTxt < text.length() && pattern[idxPat] != text[idxTxt]){
      if (idxPat != 0)
        idxPat = hMatrix[idxPat - 1];
      else
        idxTxt += 1;
    }
  }

  return -1;
}

#endif
