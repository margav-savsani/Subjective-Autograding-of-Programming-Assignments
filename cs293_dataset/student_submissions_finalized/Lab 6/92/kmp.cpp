#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
int* a;
  int b;
  b=pattern.length();
  if(b>0){
  a=new int[b];
  a[0]=0;
  int i=1;
  int j=0;
  while(i<b){
  if(pattern[j]==pattern[i]){
    a[i]=1+a[j];
    i=i+1;
    j=j+1;
  }
  else{
    int s;
    if(j>=1){
      s=j-a[j-1];
      j=j-s;
    }
    else{
      a[i]=0;
      i=i+1;
    }
  }
}
  return a;
}
else{
  return nullptr;
  return nullptr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  return 0;
}

#endif
