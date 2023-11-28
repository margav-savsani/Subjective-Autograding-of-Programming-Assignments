#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  //Computes H matrix recursively, thus it is very efficient
  int len  = pattern.length();
  int *H = new int[len];
  H[0]=0;
  for (int i = 0 ; i < len-1 ; i++ ){
    int j = H[i]; 
    do{
      if ( pattern[i+1] == pattern[j] ){
        H[i+1]=j+1;
        break;
      }
      else if ( j == 0 ){
        H[i+1] == 0;
        break;
      }
      j = H[j-1];
    }
    while(1);
  }
  return H;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  //Function which returns the index of first letter of pattern if matched, -1 otherwise
  int i = 0; 
  int j = 0;
  while(1){
    if ( i+j >= text.length() ){
      return -1;
    }
    while(text[i+j]==pattern[j]){
      if (j==pattern.length()-1){
        return i;
      }
      j++;
      if ( i+j == text.length()){
        return -1;
      }
    }
    i = i+j+1-hMatrix[j];
    j = hMatrix[j];
  }
  return 0;
}

#endif
