#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int len = pattern.length();
  int *x=new int[len];
  x[0] = 0;
  int k = 0;
  for(int i=1; i < len; i++){
    while(k>0 && pattern[k] != pattern[i]){
      k = x[k];
    }
    if ( pattern[k] == pattern[i]){
      k++;
    }
    x[i] = k;
  }
  return x;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int n = text.length();
  int m = pattern.length();
  int *x=new int[m];
  x = hMatrix;
  int q = 0;
  for ( int i=1; i < n; i++){
    while( q>0 && pattern[q+1] != text[i]){
      q = x[q];
    }
    if (pattern[q+1] = text[i]){
      q++;
    }
    if( q = m ){
      q = x[q];
    }
  }
  return q;
}

#endif
