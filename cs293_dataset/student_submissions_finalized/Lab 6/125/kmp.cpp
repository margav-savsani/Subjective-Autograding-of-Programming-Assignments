#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int *hMatrix = new int[pattern.length()];
  hMatrix[0]=0;
  string text = pattern;
  text[0]='$';
  int i = 1;
  int j = 0;
  while(i<pattern.length()){
    if(text[i]==pattern[j]){
      hMatrix[i]=j+1;
      i++;
      j++;
    }
    else{
      j = hMatrix[j-1];
      hMatrix[i]=0;
      if(j==0&&text[i]!=pattern[j]) i++;
    }
  }
  return hMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int i = 0;
  bool pattern_found = false;
  while(i <= text.length()-pattern.length()){
    int j = 0;
    while(j<pattern.length()&&text[i+j]==pattern[j]) j++;
    if(j==pattern.length()){
      pattern_found = true;
      break;
    }
    int shift;
    if(j!=0)shift = (j)-hMatrix[j-1];
    else shift = 1;
    i += shift;
  }
  if(pattern_found) return i;
  else return -1;
}

#endif
