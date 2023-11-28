#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int len=0;
  int *harr=new int[pattern.length()];
  harr[0]=0;
  for(int i=1;i<pattern.length();){
    if(pattern[i]==pattern[len]){
      len++;
      harr[i]=len;
      i++;
    }
    else{
      if(len!=0){
        len=harr[len-1];
      }
      else{
        harr[i]=0;
        i++;
      }
    }
  }
  return harr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int n=text.length(),m=pattern.length();
  int i=0,j=0;
  while(n-i>=m-j){
    if(pattern[j]==text[i]){
      i++;
      j++;
    }
    if(j==m){
      return i-j;
    }

  }
  return 0;
}

#endif
