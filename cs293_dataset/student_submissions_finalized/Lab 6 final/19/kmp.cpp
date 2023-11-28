#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int l = pattern.length();
  int* h;
  h = new int[l];
  for(int i = 0; i < l; i++){
    h[i] = 0;
  }
  int i = 0, j = 1;
  while(j < l){
    if(toupper(pattern[i]) == toupper(pattern[j])){
      h[j] = i + 1;
      i++; j++;
    }
    else if(toupper(pattern[i]) != toupper(pattern[j]) && i == 0){
      h[j] = 0;
      j++;
    }
    else{
      i = h[i-1];  
    }
  }
  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int j = 0, k = 0;
  int n = text.length();
  int m = pattern.length();
  while(k < n){
    if (toupper(pattern[j])== toupper(text[k])){
      if(j == m - 1){
        return k + 1 -m;
      }
      else{
        j++; k++;
      }
    }
  else if(toupper(pattern[j])!= toupper(text[k]) && j == 0){
    k++;
  }
  else
    j = hMatrix[j-1];
  }
  return -1; // IF NOT FOUND.
}
#endif
