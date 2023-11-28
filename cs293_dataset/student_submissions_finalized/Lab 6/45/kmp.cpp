#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  
  int* h;
  int n=pattern.size();
  h=new int[n+1];
  h[0]=-1;
  h[1]=0;
  if(pattern[0]==pattern[1]){
    h[2]=1;
  }
  else{
    h[2]=0;
  }
  for(int j=3;j<=n;j++){
    if(pattern[j-1]==pattern[h[j-1]]){
      h[j]=1+h[j-1];
    }
    else{
      h[j]1+h[h[j-1]];
    }
  }
  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  return 0;
}

#endif
