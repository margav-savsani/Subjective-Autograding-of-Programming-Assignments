#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif
#include <iostream>
#include <cstring>

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int *h_i = new int [pattern.length()];
  h_i[0] = 0;
  int match_len = 0;
  int index = 1;
  while (index < pattern.length()){
    if(pattern[index] != pattern[match_len]){
      if(match_len != 0){
        match_len = h_i[match_len - 1];
      }
      else{
        h_i[index] =0;
        index++;
      }
    }
    else{
      match_len++;
      h_i[index] = match_len;
      index ++;
    }
  }
  return h_i;
}


int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  int pat_len = pattern.length();
  int txt_len = text.length();
  int pat_ind = 0;
  int txt_ind = 0;
  while(txt_len - txt_ind >= pat_len - pat_ind){
    if(text[txt_ind] == pattern[pat_ind]){
      txt_ind++;
      pat_ind++;
    }

    if(pat_ind == pat_len){                         //THIS MAY BE WRONG
      cout << "pattern match found at : " << txt_ind - pat_ind << endl;
      pat_ind = hMatrix[pat_ind - 1];  
    }
    else if(text[txt_ind] != pattern[pat_ind] && txt_ind < txt_len){
      if(pat_ind == 0){
        txt_ind ++;
      }
      else{
        pat_ind = hMatrix[pat_ind-1];
      }
    }
  }
  return 0;
}
#endif
