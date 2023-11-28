#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;
//1879 - admin code
//0 - exit
//all else - normal
int *Planner::computeHMatrixForKMP(string pattern) {
  int length = pattern.length();
  int* h = new int[length];
  for(int i = 0; i < length; i++){
    h[i] = 0;
  }
  //0 corresponds to 1 and so on.
  h[0] = 0;
  for(int i = 1; i < length; i++){
    if(pattern[h[i-1]] == pattern[i])h[i] = h[i-1] + 1;
    else{
      for(int j = h[i-1]; j > 0; j--){
        if(pattern.substr(0,j) == pattern.substr(i-j+1,j)){
          h[i] = j;
          break;
        }
      }
    }
  }
  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  //here returning total frequency of pattern in the text
  int match = 0;
  int total_shift = 0, total_match = 0;
  for(int i = 0; i < text.length(); i++){
    if(i - total_shift == pattern.length()){
      cout << "match found at place : " << i - pattern.length(); 
      total_match++;
      int shift = i - total_shift - hMatrix[i - total_shift - 1];
      total_shift += shift;
      i--;
      match = 0;
    }
    if(pattern[i - total_shift] == text[i]){
      match++;
      continue;
    }
    else{
      int shift = i - total_shift - hMatrix[i - total_shift - 1];
      total_shift += shift;
      i--;
      match = 0;
    }
  }
  return 0;
}

#endif
