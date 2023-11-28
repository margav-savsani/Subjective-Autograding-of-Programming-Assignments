#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int* hArr = new int [pattern.length()];
  hArr[0] = 0;
  int lengthOfPrefix=0;
  for(int i = 1; i < pattern.length();i++){
    while(true){
      if(pattern[i] == pattern[lengthOfPrefix]){
        lengthOfPrefix++;
        hArr[i] = lengthOfPrefix;
        break;
      }
      else{
        if(lengthOfPrefix == 0){
          hArr[i] = 0;
          break;
        }
        else{
          lengthOfPrefix = hArr[lengthOfPrefix-1]; 
        }
      }
    }
  }
  return hArr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int numcount = 0;
  for(int i ; i < numcount; i++)
  return numcount;
}

#endif
