#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int N = pattern.size();
  int *A=new int[N];
  int i=0;
  int j=1;
  while(j<N){
    if(pattern[j]==pattern[i]){
      i++;
      A[j]=i;
      j++;
    }
    else if(i==0){
      A[j]=0;
      j++;
    }
    else{
      i=A[i-1];
    }
  }
  return A;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  return 0;
}

#endif
