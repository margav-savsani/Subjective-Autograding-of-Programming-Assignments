#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

// Returns HMatrix for given pattern
int *Planner::computeHMatrixForKMP(string pattern) {

  for (int i = 0; i < pattern.length(); i++){
    pattern[i] = toupper(pattern[i]);
  }
  

  int patternLength = pattern.length();
  if(patternLength == 0) return nullptr;
  int* h = new int[patternLength];  // hmatrix

  int j = 0;

  h[0] = 0;
  for (int i = 1; i < patternLength-1; i++){
    while(true){
      if(pattern[i] == pattern[j] && pattern[i+1] != pattern[j+1]){
        // If it matches then h[i] is decided
        h[i] = j + 1;
        j = h[i];
        break;
      }
      else{
        // Else keep reducing prefix length
        if(j == 0){
          // If it doesnt match till 0 then h[i] is 0
          h[i] = 0;
          break;
        }
        else{
          // else reduce and try again
          j = h[j-1];
        }
      }
    }
  }
  
  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  for (int i = 0; i < text.length(); i++){
    text[i] = toupper(text[i]);
  }
  for (int i = 0; i < pattern.length(); i++){
    pattern[i] = toupper(pattern[i]);
  }
  int textLength = text.length();
  int patternLength = pattern.length();


  int i = 0, j = 0;
  while( i<textLength ){
    if(pattern[j] == text[i]){
      // If match then increment both
      i++; j++;
    }
    else{
      // else keep reducing till it matches or becomes 0
      if(j == 0){
        // if 0 then move ahead
        i++;
      }
      else{
        // else keep trying shorter prefixes
        j = hMatrix[j-1];
      }
    }
    
    if(j == patternLength) return i-patternLength;
  }

  return -1;
}

#endif
