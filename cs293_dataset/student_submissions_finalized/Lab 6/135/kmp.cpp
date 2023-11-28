#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int len = pattern.size();
  int* h = new int[len];
  // for(int i=0; i<len; i++){
  //   h[i]=0;
  // }
  h[0] = 0;
  for(int i=1; i<len; i++){
    if(pattern[i] == pattern[h[i-1]+1]){
      h[i] = h[i-1]+1;
    }
    else{
      int j = h[i-1];
      while(j>1){
        if(pattern[i] == pattern[j+1]){
          h[i] = j+1;
          break;
        }
        else{
          j = h[j];
        }
      }
    }
  }
  // for(int i=0; i<len; i++){
  //   cout << h[i] << " ";
  // }
  // cout << "\n";
  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int lenpattern = pattern.size();
  int lentext = text.size();
  int *h = computeHMatrixForKMP(pattern);
  int i=0;
  while(i<lentext-lenpattern){
    bool found = 1;
    for(int j=0; j<lenpattern; j++){
      if(pattern[j] != text[i+j]) break;
    }
    if(found) return i;
    i++;
    i += h[i];
  }
  return -1;
}

#endif 
