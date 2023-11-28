#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int m=pattern.size();
  int *h=new int[m];
  h[0]=0;
  int k=-1;
  for(int q=1;q<m;q++){
    while(k>-1 && h[k+1]!=h[q]){
      k=h[k];
    }
    if(h[k+1]==h[q]){
      k=k+1;
    }
    h[q]=k;
  }

  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int n = text.size();
  int m = pattern.size();
  int q=-1;
  for(int i=0;i<n;i++){
    while(q>-1 && pattern[q+1]!=text[i]){
      q=hMatrix[q];
    }
    if(pattern[q+1]==text[i]){
      q+=1;
    }
    if(q==m-1) return i-m;
  }
  return -1;
}

#endif
