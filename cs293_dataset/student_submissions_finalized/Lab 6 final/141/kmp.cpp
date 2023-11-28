#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  // length of the previous longest prefix suffix
  int len = 0;
  int *hmatrix = new int[pattern.length()];
  int length = pattern.length();
  hmatrix[0] = 0; // hmatrix[0] is always 0

  // the loop calculates lps[i] for i = 1 to M-1
  int i = 1;
  while (i < length) {
    if (pattern[i] == pattern[len]) {
        len++;
        hmatrix[i] = len;
        i++;
    }
    else 
    {
        
      if (len != 0) {
        len = hmatrix[len - 1];
      }
      else 
      {
          hmatrix[i] = 0;
          i++;
      }
    }
  }
  return hmatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int M = pattern.length();
  int N = text.length();

  int i = 0; // index for text
  int j = 0; // index for pattern
  while ((N - i) >= (M - j)) {
    if (pattern[j] == text[i]) {
      j++;
      i++;
    }

    if (j == M) {
      return i - j;
      
    }

    // mismatch after j matches
    else if (i < N && pattern[j] != text[i]) {
      // Do not match lps[0..lps[j-1]] characters,
      // they will match anyway
      if (j != 0)
          j = hMatrix[j - 1];
      else
          i = i + 1;
    }
  }
  return -1;
}

#endif
