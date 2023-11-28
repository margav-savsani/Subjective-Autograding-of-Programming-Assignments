#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  
  return nullptr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  int len_pattern = pattern.length();
  int len_text = text.length();

  int index_text = 0;
  int index_pattern = 0;

  while(len_text >= len_pattern - index_text + index_pattern){
      if (pattern[index_pattern] == text[index_text]){
          index_pattern++;
          index_text++;
      }
      if (index_pattern == len_pattern){
          return 1;
      }
      else if ((index_text < len_text) && pattern[index_pattern] != text[index_text]){
          if (index_pattern != 0){
            index_pattern = hMatrix[index_pattern - 1];
          }
          else index_text++;
      }
  }

  return 0;
}

#endif
