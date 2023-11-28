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
}
}
int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
hMatrix=computeHMatrixForKMP(pattern);
int x=text.length();
int y=pattern.length();
int i=0;
int j=0;
while(i<x){
  if(text[i]==pattern[j]){
    i=i+1;
    j=j+1;
    if(j==y){
      break;
    }
  }
else{
  int d;
  if(j>=1){
  d=j-hMatrix[j-1];
  j=j-d;
  }
  else{
    i=i+1;
  }
}
}
  if(i==x){
    return 0; 
  }
  else{
    return i-j;
  }
}

#endif
