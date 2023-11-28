#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
    int M = pattern.length();
  // length of the previous longest prefix suffix
    int len = 0;
    int *lps = new int[M];

    lps[0] = 0; // lps[0] is always 0
 
    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pattern[i] != pattern[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0) {
                len = lps[len - 1];
 
                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }

    }
    return lps;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

    int M = pattern.length();
    int N = text.length();
 
    int i = 0; // index for text[]
    int j = 0; // index for pattern[]
    while ((N - i) >= (M - j)) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }
 
        if (j == M) {
            int index = i-j;
            return index;
            j =hMatrix[j - 1];
        }
 
        // mismatch after j matches
        else if (i < N && pattern[j] != text[i]) {
            // Do not match hMatrix[0..hMatrix[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = hMatrix[j - 1];
            else
                i = i + 1;
        }
    }

  return 0;
}

#endif
