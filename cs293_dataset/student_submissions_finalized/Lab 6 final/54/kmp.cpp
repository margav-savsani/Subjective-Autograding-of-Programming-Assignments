#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int j,k;
  int n=pattern.size();
  int H[n];
  for (int i=0;i<n;i++){
    for(k=1;k<i;k++){
      for(j=0;j<i-k+1;j++){
         if (pattern[k+j]!=pattern[j]) break;
      }
      if (j==i-k+1){
        if (pattern[i-k+1]!=pattern[i+1]) {H[i]=i-k+1;break;}
      }
    }
    if (k==i+1){H[i]=0;}
 }
  return H;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int l1=text.size();
  int l2=pattern.size();
  int i=0;
  int j;
  while(i<l1){
    for(j=0;j<l2;j++){
    if(text[i+j]!=pattern[j]){break;}
    }
    if(j==l2){return i;}
    else if (j==0){i=i+1;}
    else i=i+j-hMatrix[j-1];

 }
  return -1;
}


#endif
