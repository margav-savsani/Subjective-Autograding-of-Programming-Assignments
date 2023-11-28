#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  if(pattern==""){
    return nullptr;
  }
  int* a;
  a=new int[pattern.size()];
  a[0]=0;
  int l=0;
  for(int i=1; i<pattern.size(); i++){
    if(pattern[i]==pattern[l]){
      a[i]=l;
      l++;
    }
  }
  return a;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {


  return 0;
}

#endif

