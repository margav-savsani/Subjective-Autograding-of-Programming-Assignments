#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int sz=pattern.length();
  int *hMatrix=new int[sz];
  int i=1;
  int preflen=0;
  hMatrix[0]=0;
  while(i<sz){
    if(pattern[i]==pattern[preflen]){
      preflen ++;
      hMatrix[i]=preflen;
      i++;
    }
    else{
      if(preflen == 0){
        hMatrix[i]=0;
        i++;
      }
      else{
        preflen=hMatrix[preflen-1];
      }
    }
  }
  return hMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int lentext=text.length();
  int lenpat=pattern.length();
  int textind=0,patind=0;
  int index=0;
  while(lentext-textind >= lenpat-patind){
    if(pattern[patind]==text[textind]){
      patind++;textind++;
    }
    if(patind==lenpat){
      index=textind-patind;
      patind=hMatrix[patind-1];
    }
    elseif(textind<lentext && pattern[patind]!=text[textind]) {
            if (patind!=0)
                patind= hMatrix[patind-1];
            else
                textind++;
        }
  }
  return index;
}

#endif
