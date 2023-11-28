#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif
#include <algorithm>
using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  string text = pattern;
  text[0] = '$';
  bool isMatched = false;
  int length = pattern.size(), *h = new int[length], j = 0;
  for (int i = 0; i < length; ++i)
  {
    if (isMatched) {
      if (text[i] == pattern[j]) {
        h[i] = j + 1;
        j++;
      }
      else {
        i --;
        j = h[h[i - 1]];
        isMatched = (j != 0);
      }
    }
    else {
      j = 0;
      if (pattern[j] == text[i])
      {
        isMatched = true;
        h[i] = 1;
        j ++;
      }
      else {
        h[i] = 0;
        isMatched = false;
      }
    }
  }
  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
 int i = 0;
 transform(pattern.begin(), pattern.end(), pattern.begin(), ::toupper);
 transform(text.begin(), text.end(), text.begin(), ::toupper);
  while (i < text.length())
  {
    if(text[i]!=pattern[0]){
      i++;
      continue;
    }
    int j;
    for (j = 1 ; j < pattern.length(); j++) {
      if ( pattern[j] == text[i+j] ) continue;
      i += (j-hMatrix[j-1]);
      if(j+i >= text.length()) return -1;
      break;
    }
    if (j >= pattern.length()) return i;
  }
  return -1;
}

#endif
