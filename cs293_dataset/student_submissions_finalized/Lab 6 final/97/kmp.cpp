#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;
//computes the H matrix and returns the array
int *Planner::computeHMatrixForKMP(string pattern) {
  int len = pattern.length();
  int *h = new int[len];
  int prev = 0, i = 1;
  while(i < pattern.length()){
    if(tolower(pattern[i]) == tolower(pattern[prev])){
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
//searches for the pattern in the text, returns the index of first letter if word found, else returns -1
int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int i = 0, j = 0;
  while(i < text.length()){
    if(tolower(text[i]) == tolower(pattern[j])){
      i++;
      j++;
    } 
    else{
      if(j == 0)
        i++;
      else
        j = hMatrix[j-1];
    }
    if(j == pattern.length()){
      return i - pattern.length();
    }
  }
  return -1;
}

#endif
