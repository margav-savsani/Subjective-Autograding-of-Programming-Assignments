#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
    int n = pattern.length();
    int next[n+1];                   //next[i] stores the index of the next best partial match
    int shift;
    for (int i = 0; i < n+1; i++){
      next[i] = 0;                        //initialising the array to 0
    }

    for (int i = 1; i < n; i++){
        int j = next[i + 1];
        while (j > 0 && pattern[j] != pattern[i]){
            j = next[j];
        }
        if (j > 0 || pattern[j] == pattern[i]) next[i + 1] = j + 1;
    }
  return next;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
    int lentext = text.length();
    int n = pattern.length();
    int next[n+1];                   //next[i] stores the index of the next best partial match
    int shift;
    for (int i = 0; i < n+1; i++)
    {
      next[i] = 0;                        //initialising the array to 0
    }

    for (int i = 1; i < n; i++)
    {
        int j = next[i + 1];
 
        while (j > 0 && pattern[j] != pattern[i]) {
            j = next[j];
        }
 
        if (j > 0 || pattern[j] == pattern[i]) {
            next[i + 1] = j + 1;
        }
    }

    for (int i = 0, j = 0; i < lentext; i++)
    {
        if (text[i] == pattern[j])
        {
            if (++j == n) {
                shift = i - j + 1;           //this is the shift with which the pattern occurs
            }
        }
        else if (j > 0)
        {
            j = next[j];
            i--;    // since `i` will be incremented in the next iteration
        }
    }
  return shift;
}

#endif
