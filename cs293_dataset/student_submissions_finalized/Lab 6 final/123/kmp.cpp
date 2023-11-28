#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int l =pattern.length();
  int* hMatrix = new int[l];
  hMatrix[0]=0;
  int i = 1;
  int len = 0;
  while(i<l){
    if(pattern[i] == pattern[len]){
      len++;
      hMatrix[i] = len;
      i++;
    }
    else{
      if ( len != 0)
      {
        len = hMatrix[len-1];
      }
      else{
        hMatrix[i] = 0;
        i++; 
      }
    }
  }
  return hMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int m = pattern.size();
  int n = text.size();
  int i = 0;
  int j = 0;
  while((n-i)>=(m-j)){
    if(pattern[j] == text[i]){
      j++;
      i++;
    }
    if(j == m){
      //j = hMatrix[j-1];
      return i-j;
    }
    else if(i<n && pattern[j] != text[i]){
      if(j != 0){
        j = hMatrix[j-1];
      }
      else{
        i++;
      }
    }
  }
  return -1;
}

#endif
