#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int l = 0;
  int N = pattern.size();
  int *h;
  h = new int(N);
  h[0]=0;
  int i=1;
  while(i<N){
    if(pattern[i]==pattern[l]){
      l++;
      h[i] = l;
      i++;
    }
    else{
      if(l!=0){
        l = h[l-1];
      }
      else{
        h[i]=0;
        i++;
      }
    }
  }


  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int M = pattern.size();
  int N = text.size();
 
  int *h;
  h= new int(M);
  h=computeHMatrixForKMP( pattern);
  int k = 0;
  int i = 0;
  int j = 0;
  while((N-1) >= (M-1)){
    if (pattern[j] == text[i]){
      j++;
      i++;
    }
    if(j == M){
      k= i-j;
      break;
      j = h[j-1];
    }
    else if(i<N && pattern[j] != text[i]){
      if(j!=0){
      
        j = h[j-1];
      }
      else{
        i=i+1;
      }
    }
  }
  return k;
}

#endif
