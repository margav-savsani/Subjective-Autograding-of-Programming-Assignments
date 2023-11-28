#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern){
    int m = pattern.size();
    int* h = new int[m];
    h[0] = 0;
    h[1] = (pattern[1]==pattern[0] ? 1 : 0);
    // Match of length h[i] means that the match is from 0 ... h[i]-1
    for (int i=1; i<m-1; i++) {
        if (pattern[h[i]]==pattern[i+1]){
            h[i+1] = h[i] + 1;
        }
        else {
            int k = h[i]-1;
            while (k>=0){
                if (pattern[i+1] == pattern[h[k]]){
                    h[i+1] = h[k] + 1;
                    break;
                }
                else {
                    k = h[k]-1;
                }
            }
            if (k<0){
                h[i+1] = 0;
            }
        }
    }
    return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
    int start = 0, match=0;
    int n = text.length(), m = pattern.length();
    for (int i=0; i<n; i++) {
        if (toupper(text[i])==toupper(pattern[match])){
            match++;
            if (match==m){
                return start;
            }
        }
        else {
            if (match==0){
                start++; continue;
            }
            int shift = match - hMatrix[match-1];
            start += shift;
            match = hMatrix[match-1];
            i--;
        }
    }
    return -1;
}

#endif
