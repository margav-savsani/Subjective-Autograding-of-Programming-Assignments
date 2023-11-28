#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;
//Function to compute the H-Matrix for a given pattern
//Returns the h-matrix
int *Planner::computeHMatrixForKMP(string pattern) {
  int len=pattern.length();
  int *h=new int[len];
  h[0]=0;
  int j=0;
  for(int i=1;i<len;i++){
    while(j>0 && pattern[j]!=pattern[i]){
      j=h[j-1];
    }
    if(pattern[j]==pattern[i]){
      j++;
    }
    h[i]=j;
  }
  return h;
}
//KMP Matcher Function
//Matches the given pattern within the text and returns the first occurence index
//and -1 otherwise 
int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int n=text.length();
  int m=pattern.length();
  int i=0,j=0;
  while(i<n){
    if(pattern[j]==text[i]){
      i++;
      j++;
    }
    if(j==m){
      return (i-m);
    }
    else if(i<n && pattern[j]!=text[i]){
      if(j==0){
        i++;
      }
      else{
        j=hMatrix[j-1];
      }
    }
  }
  return -1;
}

#endif
