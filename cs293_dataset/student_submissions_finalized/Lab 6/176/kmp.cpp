#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
    int* h = new int[pattern.length()];
    h[0] = 0;
    int prev = 0, i = 1;
    while(i < pattern.length()){
        if(pattern[i] == pattern[prev]) {
            prev++;
            h[i] = prev;
            i++;
        }
        else {
            if(prev != 0)
                prev = h[prev-1];
            else {
                h[i] = 0;
                i++;
            }
        }
    }
    return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
    int m = pattern.length();
    int n = text.length();
    for(int i=0, j=0;  (n-m)>=(i-j);) {
        if(pattern[j] == text[i]) {
            i++;
            j++;
        }

        if(j == m)
            return i-j;
        else if(i < n  &&  pattern[j] != text[i]) {
            if (j != 0)
                j = hMatrix[j-1];
            else
                i++;
        }
    }
    return -1;
}

#endif
