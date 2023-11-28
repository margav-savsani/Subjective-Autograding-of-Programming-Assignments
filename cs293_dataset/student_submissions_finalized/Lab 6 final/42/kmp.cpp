#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  
    int len_pattern = pattern.length();
    int* hmatrix = new int[len_pattern];
    hmatrix[0] = 0;
    int prev_len = 0;
    int index = 1;
    while (index < len_pattern){
        if (toupper(hmatrix[index]) == toupper(hmatrix[prev_len])){
            prev_len++;
            hmatrix[index] = prev_len;
            index++;
        }
        else if (prev_len != 0) prev_len = hmatrix[prev_len - 1];
        else {
            hmatrix[index] = 0;
            index++;
        }
    }
    return hmatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  int len_pattern = pattern.length();
  int len_text = text.length();

  int index_text = 0;
  int index_pattern = 0;

  while(len_text >= len_pattern + index_text - index_pattern){
      if (toupper(pattern[index_pattern]) == toupper(text[index_text])){
          index_pattern++;
          index_text++;
      }
      if (index_pattern == len_pattern){
          return index_text - index_pattern;
      }
      else if ((index_text < len_text) && toupper(pattern[index_pattern]) != toupper(text[index_text])){
          if (index_pattern != 0){
            index_pattern = hMatrix[index_pattern - 1];
          }
          else index_text++;
      }
  }
  return -1;
}

#endif
