#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
   // length of the previous longest prefix suffix
    int shift = 0;
    int * lps = new int[pattern.length()];
    lps[0] = 0; // lps[0] is always 0
 
    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < pattern.length()) {
        if (pattern[i] == pattern[shift]) {
            shift++;
            lps[i] = shift;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            
            if (shift != 0) {
                shift = lps[shift - 1];
 
                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
  return lps;
}
return lps;//for pattern.length=1 case
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

 int M = pattern.length();
    int N = text.length();
    int * lps = computeHMatrixForKMP(pattern) ;
    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    int count=-1;
    while ((N - i) >= (M - j)) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }
 
        if (j == M) {//pattren is found sucessfully.
            count=i-j;
            break;
        }
 
        // mismatch after j matches
        else if (i < N && pattern[j] != text[i]) {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
  return count;

}

#endif
