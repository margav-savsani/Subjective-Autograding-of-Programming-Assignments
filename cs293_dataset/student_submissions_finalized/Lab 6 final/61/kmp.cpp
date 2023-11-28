#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int *ans= new int[pattern.length()];
  int len=0;
  int i=1;
  ans[0]=0;
  while(i<pattern.length()){
    if (pattern[len]==pattern[i]){
      ans[i]=len+1;
      len++;
      i++;
    }
    else{
      if(len!=0){
        len=ans[len-1];
      }
      else{
        ans[i]=0;
        i++;
      }
    }
  }
  return ans;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int i=0,j=0;
  while(i<text.length()+pattern.length()+1){
    if(text[i]==pattern[j]){
      i++;
      j++;

    }
    else{
      if(j==0){
        i++;
      }
      else{
        j=hMatrix[j-1];
      }
    }
    if(j==pattern.length()){
      return i-j;
    }
  }
  return -1;
}

#endif
