#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int size = pattern.size();
  int *array = new int [size];
  array[0] = 0;
  int length = 0;
  for (int i = 1; i < size ; ){
    if (pattern[i] == pattern[length] ){
      length++;
      array[i]=length;
      i++;
    }
    else{
      if (length==0){
        array[i]=0;
      }
      else{
        length = array[length-1];
      }
    }
  }
  return nullptr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int start = 0;
  int mismatch = -1;
  
  while(start < text.size()){
	  for (int i = start ; i < start + pattern.size() ; i++){
  	if ( text[i]!=pattern[i-start] ){
		mismatch = i;
		break;
	}
  }
  if (mismatch==-1){
	  return start;
  }
  else{
	  start = start +  h[mismatch-start];
  }
}
	
  return 0;
}

#endif
