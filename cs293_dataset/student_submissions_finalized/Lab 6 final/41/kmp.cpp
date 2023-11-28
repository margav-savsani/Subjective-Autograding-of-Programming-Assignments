#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) 
{
  int size = pattern.length();
  int* A = new int[size];
  for (int i = 1; i < size; i++){
    int j = A[i-1];
    while(j>0 && pattern[i] != pattern[j]){
      j = A[j-1];
    }
    if(pattern[i] == pattern[j]) j++;
    A[i] = j;
  }
  return A;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  int position = -1, i = 0, j = 0;

  while(i < text.length()){
    if(tolower(text[i]) == tolower(pattern[j])){
      j++; i++;
    }
    else{
      if(j != 0) j = hMatrix[j-1];
      else i++;
    }
    if(j == pattern.length()){
      position = i - pattern.length();
      break;
    }
  }

  return position;
}

#endif
