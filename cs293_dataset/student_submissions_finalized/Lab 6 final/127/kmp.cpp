#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {

  int pattern_length=pattern.length();
  int* hmatrix= new int[pattern_length];
  hmatrix[0]=0;
  int longest_suffix=0;
  int counter=1;

  while (counter<pattern_length) {
    if(pattern[counter]==pattern[longest_suffix]) {
      longest_suffix+=1;
      hmatrix[counter]=longest_suffix;
      counter+=1;
    }
    else {
      if(longest_suffix!=0) {
        longest_suffix=hmatrix[longest_suffix-1];
      }
      else {
        hmatrix[counter]=0;
        counter+=1;
      }
    }
  }


  return hmatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  int text_length=text.length();
  int pattern_length=pattern.length();
  int i=0, j=0;

  while(text_length-i>=pattern_length-j) {
    if(text[i]==pattern[j]) {
      i+=1;
      j+=1;
    }
    if(j==pattern_length) return i-j;

    else if(i<text_length && text[i]!=pattern[j]) {
      if(j!=0) j=hMatrix[j-1];
      else i+=1;
    }
  }

  return 0;
}

#endif
