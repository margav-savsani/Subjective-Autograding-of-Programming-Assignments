#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int n=0;  
  int m=pattern.length();  //length of pattern
  int* HMatrix = new int[m];  //declaration of output array
  HMatrix[0]=0;  //first element is ofcourse 0
  for (int k=1; k<m; k++){   //calculating HMatrix for each k    
    if(pattern[HMatrix[k-1]]==pattern[k]){  //if pattern values keep on matching, we can just increment h value by 1
      HMatrix[k]=HMatrix[k-1]+1;
    }
    else{   //else we start by using largest possible k and keep on matching strings until we finally are able to get equal suffix and prefix strings
      string prefix="", suffix="";
      int t= HMatrix[k-1]-1;
      while(true){
        prefix="";
        suffix="";
        for (int a=0; a<=t; a++){  //creating prefix string
          prefix=prefix+pattern[a];
        }
        for (int a=k-t; a<=k; a++){  //creating suffix string
          suffix = suffix+pattern[a];
        }
        if ((prefix==suffix)||(t==-1)) {  //if prefix and suffix string match
          HMatrix[k]=t+1;
          break;
        }
        t--;  //finally t is reduced by one if suffix and prefix strings don't match
      }      
    }
  }
  return HMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int n=text.length(), m=pattern.length();  //storing lengths of text and pattern
  int t=0, p=0;  //value of indices of text and pattern we are matching
  while(true){
    if(p==m) return t-p; //if whole pattern is matched, returns the index of text at which first match is found
    if(t==n) break; //if we are at the end of text break loop
    if(pattern[p]==text[t]){  //if current indices match, we simply increase them by one
      p+=1;
      t+=1;
    }
    else{
      if(p>=1) p=hMatrix[p-1]; //if they don't match we shift p to new position if it is not at the beginning of pattern
      else t++; //if p is at beginning of pattern, we have to shift t
    }
  }
  return -1;  //error code : pattern not found
}

#endif
