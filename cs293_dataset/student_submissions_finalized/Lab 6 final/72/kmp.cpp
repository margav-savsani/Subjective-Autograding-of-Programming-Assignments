#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  //Changing the pattern such that It works for case insensitive cases also.
  string Np = pattern;
  for(int k = 0;k<pattern.length();k++){
    Np[k] = toupper(pattern.at(k));
  }
  int l = Np.length();
  if(l == 0)return nullptr;
  int *A = new int[l];
  A[0] = 0;
  int len = 0;
  int i = 1;

  //Computing the Longest Prefix Suffix(lsp) array
  while(i < l){
    if(Np[i] == Np[len]){
      len += 1;
      A[i] = len;
      i++;
      continue;
    }else{
      if(len == 0){
        A[i] = 0;
        i++;
        continue;
      }else{
        len = A[len -1];
        continue;
      }
    }
  }
  return A;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int i = 0,j = 0;
  int m = pattern.length();
  int n = text.length();
  string Nt = text;
  string Np = pattern;
  //Processing the text and pattern such that It works for case insensitive cases also.
  for(int k = 0;k<pattern.length();k++){
    Np[k] = toupper(pattern.at(k));
  }
  for(int k = 0;k<text.length();k++){
    Nt[k] = toupper(text.at(k));
  }

  while((n+j)>=(m+i)){
    //Matching element by element
    if(Nt[i] == Np[j]){
      i++;j++;
    }
    if(j==m){
      //Returning the index if the pattern is found for the first time.
      return i-j;
    }
    else if(i<n && Np[j] != Nt[i]){
      //Shifting the pattern accordingly
      if(j==0)i++;
      else{j=hMatrix[j-1];}
    }
  }
  //If the pattern is not found in the text
  return -1;
}

#endif
