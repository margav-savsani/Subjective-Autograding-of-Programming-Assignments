#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
    int len = 0;
    int length=pattern.length();
    int* lps=new int[length];
    lps[0] = 0;   
       int i = 1;
    while (i < length){
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else{
           if (len != 0) {
                len = lps[len - 1];
           }
            else             {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

int Planner::KMPMatch(string text, int *hMatrix, string patterntern) {

  return 0;
}

#endif
