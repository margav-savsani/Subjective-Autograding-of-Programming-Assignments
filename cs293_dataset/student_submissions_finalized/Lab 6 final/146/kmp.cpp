#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int s = pattern.size();
  int k;
  int* hMatrix;
  hMatrix = new int[s];
  hMatrix[0] = 0;
  for(int i = 2; i<=s ; i++){
      k = hMatrix[i-2];
      while(k>0 && pattern[i-1]!=pattern[k]){
          k = hMatrix[k-1];
      }
      if(k==0){
          if(pattern[0] == pattern[i-1]) hMatrix[i-1] = 1;
          else hMatrix[i-1] = 0;
      }
      else {
          hMatrix[i-1] = k+1;
      }
  }
  return hMatrix; 
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int ans=0; //number of matches
  int x=0; //string index
  int y=0; //pattern index
  int patternSize=pattern.size(); // size of pattern
  while(text[x]!='\0'){
    if(text[x]==pattern[y]){
      //It matches, so there can be two cases, first that we have found a complete patter match incase y=patternsize-1 and otherwise we increment y
      if(y == patternSize-1){
        return x-patternSize+1;
        y = hMatrix[y];
      }
      else{
        y++;
      }
    }
    else{
      //If it doesn't match we go down 
      if(y==0) {
        x++;
        continue;
      }
      while(y>=0 && text[x] != pattern[y]){
        if(hMatrix[y-1]==0){
          y = -1;
          break;
        }
        y = hMatrix[y-1];
      }
      y++;
    }
    x++;
  }

  return -1;
}

#endif
