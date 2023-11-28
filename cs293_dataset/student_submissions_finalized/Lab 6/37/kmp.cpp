#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;
int count_sim(string text,string pattern,int i){
  int j=0;
  for(j;j<pattern.length();j++){
    if(text[i+j]!=pattern[j]) return j;
  }
  return pattern.length();
}

int *Planner::computeHMatrixForKMP(string pattern) {

  return nullptr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int i=0,j;
  while(i< text.length()){
    if(text[i]==pattern[0]){
      j=count_sim(text,pattern,i);
      i+=hMatrix[j];
    }
    else i++;


  }
  return 0;
}

#endif
