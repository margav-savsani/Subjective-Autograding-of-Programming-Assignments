#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int i=0;
  while(pattern[i]!='/0'){
    i++;
  }
  int length=i;
  int arr[length];
  for(int j=0;j<length;j++){
    arr[j]=0;
    for(int k=0;k<j;k++){
      bool flag=false;
      for(int l=0;l<k;l++){
        if(pattern[l]!=pattern[j-k+l]){
          flag=true;
          break;
        }
      }
      if(flag){
        arr[j]=k;
      }
    }
  }
  return arr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  return 0;
}

#endif
