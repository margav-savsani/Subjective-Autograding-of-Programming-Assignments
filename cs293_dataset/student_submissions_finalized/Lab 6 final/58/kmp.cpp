#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

// This function is for calculating the failure function 'h' as discussed in class.
// The process workson the principle of induction.
// If we know h[0] to h[i] , we can calculate h[i+1].

int *Planner::computeHMatrixForKMP(string pattern) {

  int len = pattern.length();
  int * h =new int[len];

  for(int i=0;i<len;i++){
    if(i == 0) h[i]=0;continue;

    int k = h[i-1];
    while(k!=0 && pattern[i]!=pattern[k]){
      k = h[k-1];
    }

    if(pattern[i] == pattern[k]){
      k = k+1;
    }

    h[i] = k;
  }

  return h;
}

// This function returns the index of the text from where the text first matches the pattern.

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  int l1 = text.length();
  int l2 = pattern.length();
  int sum = 0;

  for(int i=0;i<l1;i++){
    while(text[i]!=pattern[sum] && sum!=0){
      sum = hMatrix[sum-1];
    }

    if(text[i] == pattern[sum]) sum++;

    if(sum == l2){
      return (i+1-sum);
    }
  }  

  return -1;
}

#endif
