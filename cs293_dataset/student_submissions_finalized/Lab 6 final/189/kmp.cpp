#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int *H;
  int patternLength=pattern.length();
  if(patternLength==0) return nullptr;
  else {
    for(int i=0;i<patternLength;i++) {
      int kmax=-1;
      for(int k=0;k<i;k++){
        bool suffixFound=true;
        for(int j=0;j<=k;j++){
          if(pattern[j]!=pattern[i-k+j]) {
            suffixFound=false;
            break;
          }
          else{
            continue;
          }
        }
        if(suffixFound) {
          kmax=k;
          continue;
        }
        else{
          continue;
        }
        }
      if(kmax!=-1&&pattern[kmax+1]!=pattern[i+1]){
        H[i]=kmax;
      }
      else{
        H[i]=i;
      }
      
      }
    }

  return H;
  
  
}
//we will move forward by i-h[i] indices
int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  
  int textLength=text.length();
  int patternLength=pattern.length();
  if(textLength<patternLength) return 0;
  else{
    int j=0;
    int matchCount=0;
    while(j+patternLength<=textLength){
      int i=0;
      while(i<patternLength) {
        if(pattern[i]!=text[j+i]) {
          break;
        }
        else{
          i++;
        }
      }
      if(i==patternLength) {
        matchCount++;
        j=j+(i-hMatrix[i-1]);
      }
      else if(i==0) {
        j++;
      }
      else{
        j=j+(i-hMatrix[i-1]);
      }


      
    }
  return matchCount;
  }
}


#endif
