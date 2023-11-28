#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {

  int m = pattern.length();

  int* h = new int[m];
  h[0] = 0;
  int len = 0;

  int i = 1;

  while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            h[i] = len;
            i++;
        }
        else
        {
            if (len != 0) {
                len = h[len - 1];
            }
            else
            {
                h[i] = 0;
                i++;
            }
        }
    }

  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  int M = pattern.length();
  int N = text.length();

  int i = 0;
  int j = 0;
    while ((N - i) >= (M - j)) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }
 
        if (j == M) {
            return i-j;
        }
 
        else if (i < N && pattern[j] != text[i]) {
            if (j != 0)
                j = hMatrix[j - 1];
            else
                i = i + 1;
        }
    }

  return -1;
}

#endif
