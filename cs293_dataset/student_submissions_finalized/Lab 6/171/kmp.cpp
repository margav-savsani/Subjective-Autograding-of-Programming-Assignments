#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int l=pattern.length();
  int h[l],len=0;
  h[0]=0;
  for(int i=0;i<l;i++){
    if(pattern[i]==pattern[len]){
      len++;
      h[i]=len;
    }
    else{
      if(len!=0){
        len=h[len-1];
        i--;
      }
      else
        h[i]=0;
      
    }
  }

  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  int t=text.lenght();
  int p=pattern.lenght();
  int h[p],i=0,j=0;
  h=computeHMatrixForKMP(pattern);
  while((N-i)>=(M-j)){
    if(pat[j]==txt[i]){
      j++;
      i++;
    }
    if(j==M){
      j=h[j-1];
      return i-j;
    }
    else if(i<N && pat[j]!=txt[i]){
      if(j!=0)
        j=h[j-1];
      else
        i++;
    }

  }
  return -1;
}

#endif
