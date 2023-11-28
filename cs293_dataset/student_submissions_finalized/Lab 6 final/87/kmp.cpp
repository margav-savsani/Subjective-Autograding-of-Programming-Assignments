#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int *h, l=pattern.length(), i=1, f=0;
  h = new int[l];
  h[0]=0;
  while (i<l){
    if (pattern[i] == pattern[f]) { 
      f++;
      h[i] = f;
      i++;
    }
    else {
      if (f != 0){
        f = h[f-1];
      }
      else {
        h[i] = 0;
        i++;
      }
    }
  }
  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
int i=0, k=0, m=text.length(), n=pattern.length();
  while ((k+i)<=m-1 && i<=n-1){
    if (pattern[i] == text[k+i]){
      i++;
    }
    else {
      if(i==0){
        k++;
      }
      else{
        k += (i-hMatrix[i-1]);
        i=0;
      }
    }
  }
  if (i==n) return k;
  return -1;
}
#endif  