#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int k = pattern.length();
  int* h;
  h = new int[k+1];
  int i ;
  for(i=0;i<k+1;i++){
    h[i] = 0 ;
  }
  for(int m=1;m<k;m++){
    int j = h[m+1];
    while(j>0 && pattern[m]!=pattern[j]){
      j = h[j];
    }
    if(j>0||pattern[m]==pattern[j]){
      h[m+1] = j+1 ;
    }
  }

  if(k==0)return nullptr;
  else return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int k = pattern.length();
  int l = text.length();
  if(k==0)return -1 ;
  if(k > l)return -1 ;
  int j = 0 ;
  for (int i = 0; i < l; i++){
    if (text[i] == pattern[j]){
      if (++j == k) {
        return (i-j+1);
      }
    }
    else if (j > 0){
            j = hMatrix[j];
            i--;    
    }
    if(i==l-1)return -1 ;
  }
}

#endif
