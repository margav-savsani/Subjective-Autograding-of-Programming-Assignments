#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int Length = pattern.length();
  int longest_suffix_length=0;
  int *longest_suffix = new int[Length];
  int i=1;
  while(i<Length){
    if(pattern[i]==pattern[longest_suffix_length]){
      longest_suffix_length++;
      longest_suffix[longest_suffix_length] = longest_suffix_length;
      i++;
    }
    else{
      {
            if (longest_suffix_length != 0) {
                longest_suffix_length = longest_suffix[longest_suffix_length - 1];
            }
            else 
            {
                longest_suffix[i] = 0;
                i++;
            }
        }
    }
  }
  return longest_suffix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  return 0;
}

#endif
