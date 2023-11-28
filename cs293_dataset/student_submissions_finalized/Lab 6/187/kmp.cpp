#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern){
     int len = 0;
     int *h;
     int M = pattern.length();
    h[0] = 0; 
    int i = 1;
    while (i < M) {
        if (pattern[i] == pattern[len]) {
            len++;
            h[i] = len;
            i++;
        }
            if (len != 0) {
                len = h[len - 1];
            }
            else // if (len == 0)
            {
                h[i] = 0;
                i++;
            }
        }
        return h;
    }

int Planner::KMPMatch(string text, int *hMatrix, string pattern){
  return 0;
}

#endif
