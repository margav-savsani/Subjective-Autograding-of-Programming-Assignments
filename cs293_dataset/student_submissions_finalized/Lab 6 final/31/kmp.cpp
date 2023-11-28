#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

// compute the hMatrix for given pattern
int *Planner::computeHMatrixForKMP(string pattern) {

  int *hMatrix = new int[pattern.length()];

  hMatrix[0]=0;

  for(int i=1; i<pattern.length(); i++){
    int a=i-1;
    while(a>=0){
      if(pattern[i]==pattern[hMatrix[a]]){
        hMatrix[i]=hMatrix[a]++;
        break;
      }
      else {
        a = hMatrix[a];
        if(a==0){
          a=-1;
          hMatrix[i]=0;
        }
      }
    }
  }
  return hMatrix;
}

// search for index where mismatch is happening
int searchind(string text, string pattern, int textind){
  assert(pattern.length() <= text.length());
  for(int i=0; i<pattern.length(); i++){
    if(text[textind+i]!=pattern[i])
      return i;
  }

  //if pattern matched, return -1
  return -1;
}
int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  int ind=0;
  while(ind<=text.length()-pattern.length()){
    int r = searchind(text,pattern,ind);

    if(r==-1) // if pattern matched return index 
      return ind;
    else {
      if(ind==0) 
        ind++;
      else  // increment the index according to the hMatrix
        ind=ind+r-hMatrix[r-1]+1;
    }

  }
  return -1;
}

#endif
