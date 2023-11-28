#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int* H=new int[pattern.length()];
  int M=pattern.length();
  int x=0;
  H[0]=0;

  int i=1;
  while(i<M){
    if(pattern[i] == pattern[x]){
      x++;
      H[i]=x;
      i++;
    }
    else{
      if(x!=0){
        x=H[x-1];
      }
      else{
        H[i]=0;
        i++;
      }
    }
  }
  return H;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int M=pattern.length();
  int N=text.length();
  int i=0,j=0;
  while((N-i)>=(M-j)){
    if(pattern[j]==text[i]){
      i++;j++;
    }
    if(j==M){
      return i-j;
    }
    else if(i<N && pattern[j]!=text[i]){
      if(j!=0) j=hMatrix[j-1];
      else i++;
    }
  }
  return 0;
}

#endif
