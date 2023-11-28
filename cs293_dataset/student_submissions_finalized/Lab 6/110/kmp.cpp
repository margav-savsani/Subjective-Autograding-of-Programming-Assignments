#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *computeHMatrixForKMP2(string pattern){
  //defined a new function here, so that it can be useful in future
  //as the computematrix function is inside the Planner
  int* h=new int[pattern.length()];
  if(pattern.length()==0) return nullptr;
  else{
    int l=pattern.length();
    int k;
    h[0] = -1;
    for (int i = 1; i < l; i++)
    {
      k=h[i-1];
      while (k>=0)
      {
        if(pattern[k]==pattern[i-1]) break;
        else k=h[k];
      }
      h[i]=k+1;
    }
  }
  return h;
}
int *Planner::computeHMatrixForKMP(string pattern) {
  return computeHMatrixForKMP2(pattern);
}


int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  return 0;
}

#endif
