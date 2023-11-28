#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;
int i = 0;

int *Planner::computeHMatrixForKMP(string pattern) {
  int *hMatrix;
  int(pattern[i]);
  for(int i = 0; i < strlen(pattern); i++){
    hMatrix[i] = ;
  }
  return hMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int pattern_length = strlen(pattern);
  int text_length = strlen(text);
  while((text_length-i)>= (pattern_length-j)){
    if(pattern[j]==text[i]){
      j++;
      i++;
    }
    if(j == pattern_length){
      j = 
    }
  }
  while(i == strlen(pattern))return i;
  computeHMatrixForKMP(text,hMatrix,pattern);
  while(!strcmp(text[i],pattern[i])){
    i++;
  }
  i += i - hMatrix[i];
  KMPMatch(text[i],hMatrix,pattern);
  return i;
}

#endif
