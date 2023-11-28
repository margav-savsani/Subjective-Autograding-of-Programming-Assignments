#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pat) {
 int len = 0;
 int M =pat.length();
 int lps[M];
    lps[0] = 0;
 
    
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else { 
            if (len != 0) {
                len = lps[len - 1];
 
                
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

int Planner::KMPMatch(string txt, int *hMatrix, string pat) {
  int M = (pat.length());
    int N = (txt.length());
 
    
    int lps[M];
 
    
    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while ((N - i) >= (M - j)) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
 
        if (j == M) {
            printf("Found pattern at index %d ", i - j);
            j = lps[j - 1];
        }
 
        // mismatch after j matches
        else if (i < N && pat[j] != txt[i]) {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }

  return 0;
}

#endif
