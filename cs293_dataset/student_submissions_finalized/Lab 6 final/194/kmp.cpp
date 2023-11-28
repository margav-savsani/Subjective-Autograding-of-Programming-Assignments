#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int patternLength = pattern.length();
  int len=0;
  int *longest_prefix = new int[patternLength];
  longest_prefix[0]=0;
  int i=1;
  while(i<patternLength){
    if(pattern[i]==pattern[len]){
      len++;
      longest_prefix[len] = len;
      i++;
    }
    else{
      {
        if (len != 0) {
          len = longest_prefix[len - 1];
        }
        else 
        {
          longest_prefix[i] = 0;
          i++;
        }
      }
    }
  }
  return longest_prefix;
 // return nullptr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int patt_len = pattern.length();
  int txt_len = text.length();
  int patt_ind=0;
  int txt_ind=0;
  while(txt_len >= patt_len - patt_ind + txt_ind){
    if(text[txt_ind] == pattern[patt_ind]){
      txt_ind++;
      patt_ind++;
    }
    if(patt_ind==patt_len){
      return txt_ind-patt_ind;
    }
    else{
      if((text[txt_ind]<txt_len) && (pattern[patt_ind]!=text[txt_ind])){
        if (patt_ind==0){
          txt_ind++;
        }
        else{
          patt_ind==hMatrix[patt_ind-1];
        }
      }
    }
  }

  return 0;
}

#endif
