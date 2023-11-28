#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  //computes the prefix array the length of longest prefix matching with a proper prefix
  //if we have value from 1 to i in the table we can computr value of i+1
  //if next word matches it will be h(i)+1
  //else h(h(i))+1
  int N = pattern.size();
  int *A=new int[N];
  int i=0;
  int j=1;
  while(j<N){
    if(pattern[j]==pattern[i]){
      i++;
      A[j]=i;
      j++;
    }
    else if(i==0){
      A[j]=0;
      j++;
    }
    else{
      i=A[i-1];
    }
  }
  return A;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  hMatrix=computeHMatrixForKMP(pattern);
  int i = 0;
  int j = 0;
  int k=-1;
  while (i<text.length()) {
    if (pattern[j] == text[i]) {
      j++;
      i++;
    }
    if (j == pattern.length()){
      k=i-j;
      break;
    }
    else if (i < text.length() && pattern[j] != text[i]) {
      if (j > 0)
          j = hMatrix[j - 1];
      else
        i++;
    }
  }  
  return k;
}

#endif
