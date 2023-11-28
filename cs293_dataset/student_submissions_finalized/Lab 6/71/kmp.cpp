#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {

  int j = 0,lps[pattern.length()];
 
  lps[0] = 0;
  int i = 1;
  while (i < pattern.length()) {
    if(pattern[i] == pattern[j]) {
      j++;
      lps[i] = j;
      i++;
    }
    else
    {
      if (j != 0) {
        j = lps[j - 1];
      }
      else 
      {
        lps[i] = 0;
        i++;
      }
    }
  }
  return lps;
}



int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  int j=0,i=0,ans=0;
  while ((text.length()-i) >= (pattern.length()-j)) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        } 
        if (j == pattern.length()) {
            ans++;
            j = hMatrix[j - 1];
        }
        else if (i < text.length() && pattern[j] != text[i]) {
            if (j != 0)
                j = hMatrix[j - 1];
            else
                i = i + 1;
        }
    }
  return ans;
}

#endif
