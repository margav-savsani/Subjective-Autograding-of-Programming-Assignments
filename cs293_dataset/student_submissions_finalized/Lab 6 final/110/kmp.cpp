#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;


int *Planner::computeHMatrixForKMP(string pattern) {
  int l= pattern.length();
  int* h=new int[l+1];
  int* h2=new int[l];
  int k;
  h[0] = -1;
  for (int i = 1; i <= l; i++)
  {
    k=h[i-1];
    while (k>=0)
    {
      if(pattern[k]==pattern[i-1]) break;
      else k=h[k];
    }
    h[i]=k+1;
  }

  for (int i = l-1; i >= 0; i--){
    h2[i] = h[i+1];
  }
  
  return h2;
}


int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int i=0;
  int t = text.length();
  int p = pattern.length();
  for(int q=0;q<p;q++){
    pattern[q]=toupper(pattern.at(q));  //used this to make it case insensitive
  }
  for(int q=0;q<t;q++){
    text[q]=toupper(text.at(q));
  }
  while(i<t-p){
    int j;
    for(j=0;j<p;j++){
      if(text[i+j]!=pattern[j]){
        if(hMatrix[j]==0){
          i=i+j+1;
          break;
        }
        else
        {
          i=i+j-hMatrix[j];
          break;
        } 
      }
    }
    if(j==p)  return i; //that means pattern is found
  }
  return -1;
}

#endif
