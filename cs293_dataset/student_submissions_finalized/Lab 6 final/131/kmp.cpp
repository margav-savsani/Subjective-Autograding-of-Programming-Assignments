#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int  hMatrix[100000];// initailise hMatrix as a global variable because if defined in function the scope became limited

int *Planner::computeHMatrixForKMP(string pattern) {
  int longest = 0;
  int pat = pattern.length();
  hMatrix[0] = 0; //for first letter of pattern
    int i = 1;//represents the index of the pattern 
    while (i < pat) { 
      if (pattern[i] == pattern[longest]) {//match happens
        longest++;
        hMatrix[i] = longest;
        i++;
      }
      else //
        {
          if (longest != 0) { //there is a mismatch
            longest = hMatrix[longest - 1];
         }
          else // no prefix possible for that index
          {
             hMatrix[i] = 0;
             i++;
          }
        }
    }
  return hMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int i = 0; 
  int j = 0; 
  int pat = pattern.length();
  int texts = text.length();

  while ((texts - i) >= (pat - j)) {
    if (pattern[j] == text[i]) {
        i++;
        j++;
    }
    if (j == pat) { //pattern found in text
      return i-j;
    }
    else if (i < texts && pattern[j] != text[i]) {// mismatch after j matches
      if (j != 0) // shift the pattern according to the value in the hMatrix
        j = hMatrix[j - 1];
      else
        i ++; //increment index of the text 
     }
  }
  return -1;
}
 
#endif
