#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int n=0;  
  int m=pattern.length();  //length of pattern
  int* HMatrix = new int[m];
  HMatrix[0]=0;
  for (int k=1; k<m; k++){   //calculating HMatrix for each k    
    if(pattern[HMatrix[k-1]]==pattern[k]){
      HMatrix[k]=HMatrix[k-1]+1;
    }
    else{
      string prefix="", suffix="";
      int t= HMatrix[k-1]-1;
      while(true){
        prefix="";
        suffix="";
        for (int a=0; a<=t; a++){
          prefix=prefix+pattern[a];
        }
        for (int a=k-t; a<=k; a++){
          suffix = suffix+pattern[a];
        }
        if ((prefix==suffix)||(t==-1)) {
          HMatrix[k]=t+1;
          break;
        }
        t--;
      }      
    }
  }
  return HMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int n=text.length(), m=pattern.length();
  int t=0, p=0;
  while(true){
    
  }
  return 0;
}

#endif
