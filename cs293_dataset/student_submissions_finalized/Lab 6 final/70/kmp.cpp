#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int *hMatrix = new int [pattern.size()];
  hMatrix[0] = 0;
  for(int i = 1; i < pattern.size(); i++){
    int patternEndIndex = hMatrix[i - 1];
    while (patternEndIndex >= 0){
      if(pattern[patternEndIndex] != pattern[i] && patternEndIndex > 0){
        patternEndIndex = hMatrix[patternEndIndex - 1];
      }
      else if(pattern[patternEndIndex] != pattern[i] && patternEndIndex == 0){
        hMatrix[i] = 0;
        break;
      }
      else{
        hMatrix[i] = patternEndIndex + 1;
        break;
      }   
    }        
  }
  return hMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  if(text.size() == 0) return -1;
  int firstMisMatch;
  for (firstMisMatch = 0; firstMisMatch < pattern.size(); firstMisMatch++){
    if(pattern[firstMisMatch] != text[firstMisMatch]){
      break;
    }
  }
  if(firstMisMatch == pattern.size()){
    return 0;
  }
  else{
    int shift;
    if(firstMisMatch == 0){
      shift = 1;
    }
    else{
      shift = firstMisMatch - hMatrix[firstMisMatch - 1];
    }
    string newText = text.substr(shift);
    int match = KMPMatch(newText, hMatrix, pattern);
    if(match != -1){
      return shift + match;
    }
    else{
      return -1;
    }    
  }
}

#endif
