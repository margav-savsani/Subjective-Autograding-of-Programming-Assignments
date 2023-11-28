#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int len = 0;
  int *lps = new int[pattern.length()];
  lps[0] = 0;
  int i = 1;
  while (i<pattern.length())
  {
    if(pattern[i]==pattern[len]){
      len++;
      pattern[i] = len;
      i++;
    }
    else{
      if(len!=0){
        len = lps[len-1];
      }
      else{
        lps[i]=0;
        i++;
      }
    }
  }

  return lps;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  // hMatrix = computeHMatrixForKMP(pattern);
  int pos = -1;
  int i = 0 ;//for text
  int j=0; //for pattern
  while(i<text.length()){
    if(text[i]==pattern[j]){
      i++;
      j++;
    }
    else{
      if(j!=0){
        j = hMatrix[j-1];
      }
      else{
        i++;
      }
    }
    if(j==pattern.length())
    {
      pos = i-j;
      break;
    }
  }

  return pos;
}

#endif
