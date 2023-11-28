#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
   int len = 0;
    int gap=pattern.length();
    int lps[gap];
    lps[0] = 0; 
    int i = 1;
    while (i < gap) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
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
int Planner::KMPMatch(string txt, int *hMatrix, string pattern) {
    int len = pattern.length();
    int len1 = txt.length(); 
    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while ((len1 - i) >= (len - j)) {
        if (pattern[j] == txt[i]) {
            j++;
            i++;
        }
 
        if (j == len) {
            return i-j;
            j = hMatrix[j - 1];
        }
        else if (i < len1 && pattern[j] != txt[i]) {
            if (j != 0)
                j = hMatrix[j - 1];
            else
                i = i + 1;
        }
    }
    return 0;
}
#endif
