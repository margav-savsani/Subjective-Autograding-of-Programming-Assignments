#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  
  int len = 0; // length of the previous longest prefix suffix
  int M = pattern.length();
  int * h = new int[M];
  h[0] = 0; // h[0] is always 0
  int i = 1; // the loop calculates h[i] for i = 1 to M-1
  
  while (i < M) {
    if (pattern[i] == pattern[len]) {
      len++;
      h[i] = len;
      i++;
    }
    else // (pattern[i] != pattern[len])
    {
      if (len != 0) {
        len = h[len - 1];

        // Also, note that we do not increment
        // i here
      }
      else // if (len == 0)
      {
        h[i] = 0;
        i++;
      }
    }
  }
  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  // Prints occurrences of text[] in pat[]
  int M = pattern.length();
  int N = text.length();

  // create hMatrix[] that will hold the longest prefix suffix
  // values for pattern
  hMatrix = computeHMatrixForKMP(pattern);

  // Preprocess the pattern (calculate hMatrix[] array)

  int i = 0; // index for text[]
  int j = 0; // index for pat[]
  while ((N - i) >= (M - j)) {
    if (pattern[j] == text[i]) {
      j++;
      i++;
    }

    if (j == M) {
      return (i - j);
      j = hMatrix[j - 1];
    }

    // mismatch after j matches
    else if (i < N && pattern[j] != text[i]) {
      // Do not match hMatrix[0..hMatrix[j-1]] characters,
      // they will match anyway
      if (j != 0) j = hMatrix[j - 1];
      else i = i + 1;

    }
  }
  return -1;
}

#endif
