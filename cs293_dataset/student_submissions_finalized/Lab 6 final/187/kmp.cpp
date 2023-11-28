#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;
int *Planner::computeHMatrixForKMP(string pat)
{
    // length of the previous longest prefix suffix
    int len = 0;
    int M = pat.length();
    int *A;
    A = new int[M];
    A[0] = 0;
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            A[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            if (len != 0) {
                len = A[len - 1];
            }
            else
            {
                A[i] = 0;
                i++;
            }
        }
    }
    return A;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern){
    int M = pattern.length();
    int N = text.length();
    int count = 0;// number of matchings of pattern with text.
    int index;
    int i = 0;
    int j = 0;
    while ((N - i) >= (M - j)) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }
 
        if (j == M) {
            j = hMatrix[j - 1];
        }
        else if (i < N && pattern[j] != text[i]) {
            if (j != 0){
                index = i-j;
                count++;
                j = hMatrix[j - 1];
            }
            else{
                i = i + 1;
            }
            }
    }
    if(count == 0){
        return -1;
    }
    else{
        return index;
    }
}
#endif
