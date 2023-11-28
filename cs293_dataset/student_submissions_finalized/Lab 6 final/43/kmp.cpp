#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int* arr = new int[pattern.length()];
  arr[0] = 0;
  int i = 1;
  int j = 0;
  while(i < pattern.length()){
    if(pattern[i] == pattern[j]){
      arr[i] = j+1;
      i = i+1;
      j = j+1;
    }
    else if(j==0){
      arr[i] = 0;
      i = i+1;
    }
    else{
      j = arr[j-1];
    }
  }
  return arr;
}
int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int i = 0;
  int j = 0;
  for(int k = 0;k< text.length()-pattern.length()+1;k++){
      if(pattern[i] == text[j]){
        if(i == pattern.length()-1){
          return (j-i+1);
        }
        else{
          i++;
          j++;
        }
      }
      else if(i==0){
        j++;
      }
      else if(i>0){
        i = hMatrix[i-1];
      }
  }
  return -1;
}

#endif
