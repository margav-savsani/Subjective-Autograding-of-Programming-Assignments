#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  if(pattern.size()==0)
    return nullptr;
  int arr[pattern.size()];//array to store the h function
  string pat=pattern;
  arr[0]=-1;
  for(int i=1;i<pattern.size();i++){
    arr[i]=arr[i-1]+1;
    while(toupper(pattern[i-1])!=toupper(pattern[arr[i]-1]) && arr[i]){
      arr[i]=arr[arr[i]-1]+1;
    }
  }
  return arr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int j=0;
  for(int i=0;i<text.size();i++,j++){
    if(text[i]==pattern[j]){
      if(j==pattern.size()-1)
        return i;
      continue;
    }
    while(j!=-1 && text[i]!=pattern[j]){
      j=hMatrix[j];
    }
  }
  return -1;
}

#endif
