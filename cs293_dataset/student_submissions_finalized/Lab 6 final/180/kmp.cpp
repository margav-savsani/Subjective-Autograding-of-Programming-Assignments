#ifndef KMP_CPP
#define KMP_CPP
#include <algorithm>

#ifndef PLANNER_H
#include "planner.h"
#endif
#include <iostream>
#include <cstring>

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) { // this function will calculate Hmatrix. for this it will use prefix-suffix property
  transform(pattern.begin(), pattern.end(), pattern.begin(), ::toupper);
  int *h_i = new int [pattern.length()];
  h_i[0] = 0;
  int match_len = 0;
  int index = 1;
  //go through the string and for every character find length of longest prefix
  while (index < pattern.length()){
    if(pattern[index] != pattern[match_len]){
      if(match_len != 0){                      //as per naveen garg's slide
        match_len = h_i[match_len - 1];
      }
      else{
        h_i[index] =0;
        index++;
      }
    }
    else{
      match_len++;
      h_i[index] = match_len;                 //1 + previous's h index 
      index ++;
    }
  }
  return h_i;
}


int Planner::KMPMatch(string text, int *hMatrix, string pattern) {//returns the index of 1st occurence of the tree
  transform(pattern.begin(), pattern.end(), pattern.begin(), ::toupper);
  transform(text.begin(), text.end(), text.begin(), ::toupper);
  //strings converted to uppercase 
  int pat_len = pattern.length();
  int txt_len = text.length();
  int pat_ind = 0;
  int txt_ind = 0;
  int ret_index = -1;
  while(txt_len - txt_ind >= pat_len - pat_ind){                //until text ends search
    if(text[txt_ind] == pattern[pat_ind]){
      txt_ind++;
      pat_ind++;
      if(pat_ind == pat_len){                     //full pattern matches
        if(ret_index == -1){
          ret_index = txt_ind - pat_ind ;
        }                   
        pat_ind = hMatrix[pat_ind - 1];  
      }
    }

    else if(text[txt_ind] != pattern[pat_ind]){                 //shift if pattern do not match
      if(pat_ind == 0){
        txt_ind ++;
      }
      else{
        pat_ind = hMatrix[pat_ind-1];
      }
    }
  }
  return ret_index;
}
#endif
