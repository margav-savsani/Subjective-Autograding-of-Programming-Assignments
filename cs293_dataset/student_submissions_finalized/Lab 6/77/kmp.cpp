#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int size=pattern.length();
  int failureArray[size];
  failureArray[0]=0;
  int len=0;
  int i=1;
  
  while(i<size){
    if(pattern[i]==pattern[len]){
        len++;
        failureArray[i]=len;
        i++;
    }
    else{
      if(len !=0){
        len = failureArray[len-1];
      }
      else{
        failureArray[i]=0;
        i++;
      }
    }
  }
  return failureArray;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int textSize= text.length();
  int patternSize=pattern.length();
  int t=0;
  int p=0;
  while((textSize-t) >= (patternSize-p)){
    if(pattern[p]==text[t]){
      t++;
      p++;
    }
    if(p==patternSize){
      return (t-p);
    }
    else if(t<textSize && pattern[p]!=text[t]){
      if(p!=0){
        p=hMatrix[p-1];
      }
      else{
        t++;
      }
    }
  }

  return -1;
}

#endif
