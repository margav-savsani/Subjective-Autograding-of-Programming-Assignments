#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern){
  int* a;
  int l=pattern.length();
  if (l==0){
    return nullptr;
  }
  a=new int[l];
  int p=0;
  a[0]=0;
  int k=1;
  while(k<l){
    if(pattern[k]==pattern[p]){
      p++;
      a[k]=p;
      k++;
    }
    else{
      if(p==0){
        a[k]=0;
        k++;
      }
      else{
        p=a[p-1];
      }
    }
  }
  return a;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int t=text.length();
  int p=pattern.length();
  int x=0;
  int y=0;
  if(p>t){
    return -1;
  }
  while(true){
    if (text[x]==pattern[y]){
      y++;
      x++;
    }
    if(y==p){
      return x-p;
    }
    if(text[x]!=pattern[y]){
      if (y==0)
        x++;
      else
        y = hMatrix[y-1];
    }
    if(x>t-p+y){
      break;
    }
  }
  return -1;
}

#endif
