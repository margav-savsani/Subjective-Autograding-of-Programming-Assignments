#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

// h[i] is the length of the longest proper prefix of pattern 
// which is also the suffix of pattern[0..i-1].
// It doesn't require the condition that pattern[i] != pattern[h[i]]
// 
// The hmatrix if 1-indexed
int *Planner::computeHMatrixForKMP(string pattern) {
    int* h = new int[pattern.size()+1];
    h[1] = 0;
    int k = 0;
    for (int i=2; i<=pattern.size(); i++) {
        while (k && (int)pattern[k]%32 != (int)pattern[i-1]%32) k = h[k];
        if (k || (int)pattern[k]%32 == (int)pattern[i-1]%32) h[i] = ++k;
    }

    return h;
}


int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
    int* h = computeHMatrixForKMP(pattern);
    int j = 0;
    for (int i=0; i<text.size(); i++) {
        while ((int)text[i]%32 != (int)pattern[j]%32 && j) j = h[j];

        if ((int)text[i]%32 == (int)pattern[j]%32) {
            if (j == pattern.size()-1) return i-j;
            j++;
            continue;
        }
    }

    return -1;
}

#endif