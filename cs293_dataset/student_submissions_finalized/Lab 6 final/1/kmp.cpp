#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  //the array values h[i] represent k for which P_k is the 
  //longest prefix which is also a suffix for P_i
  //P[0], P[1] ... P[k] === P[i-k], P[i-k+1] ... P[i]
  int len = pattern.length();
  int *h = new int[len];
  h[0] = -1; //-1 represents match with an empty string prefix
  int matched = -1;
  for(int i = 1; i < len; i++){
    //make all comparisons in uppercase
    //so that for eg. aBc is the same ABC
    while(matched >= 0 && toupper(pattern[matched + 1]) != toupper(pattern[i])){
      matched = h[matched + 1];
    }
    if(toupper(pattern[matched + 1]) == toupper(pattern[i])) matched++;
    h[i] = matched;
  }
  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int t = text.length();
  int p = pattern.length();
  int matched = -1, curr = 0;
  for(int i = 0; i < t; i++){
    //the while loop runs only O(t) times
    //make all comparisons in uppercase to make it case insensitive
    while(matched >= 0 && toupper(text[i]) != toupper(pattern[matched + 1])){
      matched = hMatrix[matched];
    }
    if(toupper(text[i]) == toupper(pattern[matched + 1])){
      matched++;
    }
    //a match with the pattern found.
    //returning the index of the beginning of the match.
    if(matched == p - 1){return i - p + 1;}
  }
  //no match
  return -1;
}

#endif
