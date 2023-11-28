#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int len = 0;
  int patternLength = pattern.length();
    int HMatrix[patternLength];
    HMatrix[0] = 0;
 
    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < patternLength) {
        if (pattern[i] == pattern[len]) {
            len++;
            HMatrix[i] = len;
            i++;
        }
        else // (pattern[i] != pattern[len])
        {
            if (len != 0) {
                len = HMatrix[len - 1];
            }
            else // if (len == 0)
            {
                HMatrix[i] = 0;
                i++;
            }
        }
    }
  return nullptr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int M = pattern.length();
  int N = text.length();

  for (int i = 0; i < M; i++) {
    pattern[i] = toupper(pattern[i]);
  }

  for(int i = 0; i < N; i++){
    text[i] = toupper(text[i]);
  }

  // create lps[] that will hold the longest prefix suffix
  // values for pattern
  int HMatrix[M];

  // Preprocess the pattern (calculate lps[] array)
  computeHMatrixForKMP(pattern);

  int i = 0; // index for txt[]
  int j = 0; // index for pattern[]
  while ((N - i) >= (M - j)) {
      if (pattern[j] == text[i]) {
          j++;
          i++;
      }

      if (j == M) {
          return (i-j);
      }

      // mismatch after j matches
      else if (i < N && pattern[j] != text[i]) {
          if (j != 0)
              j = HMatrix[j - 1];
          else
              i = i + 1;
      }
    }
  return 0;
}

#endif
