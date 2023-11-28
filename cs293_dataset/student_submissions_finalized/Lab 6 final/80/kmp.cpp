#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int * hmatrix = new int[pattern.length()];

  for(int i = 0; i<pattern.length(); i++){
    if (i == 0){
      hmatrix[i] = 0;
    }
    else{
      int term = hmatrix[i-1];

      while(pattern[term] != pattern[i]){
        if(term==0){
          term=-1;
          break;
        }
        term = hmatrix[term-1];
      }
      hmatrix[i] = term + 1;
    }
  }
  return hmatrix;
  //return nullptr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int text_ind = 0, pattern_index=0;
  string text2 = text, pattern2 = pattern;
	for (int i = 0; i < text2.length(); i++)
  	{
  		text2[i] = tolower(text2[i]);
  	}
	for (int i = 0; i < pattern2.length(); i++)
  	{
  		pattern2[i] = tolower(pattern2[i]);
  	}
  while (true){
    if(text2[text_ind] == pattern2[pattern_index]){
      text_ind+=1;
      pattern_index+=1;
    }
    else{
      //text_ind -= hMatrix[pattern_index];
      if(pattern_index==0){
        text_ind+=1;
      }
      else{
        pattern_index -= pattern_index - hMatrix[pattern_index-1];
      }
    }
    if(pattern_index>= pattern2.length()){
      return text_ind-pattern_index;
    }
    else if(text_ind >= text2.length()){
      return -1;
    }
  }

  return -1;
}

#endif


