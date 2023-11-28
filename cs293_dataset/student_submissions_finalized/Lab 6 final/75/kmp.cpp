#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif
#include <string>
#include <algorithm>
using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int n = 0; //stores the length of the pattern
  // cout<<"I am here"<<endl;
  n = pattern.length();
  int* H = new int[n]; // declare an array for storing the H matrix

  H[0] = 0;
  int k = 0;

  for (int q = 2; q<=n; q++){
    while (k>0 && pattern[k]!=pattern[q-1]){
      k = H[k];
    }
    if (pattern[k]==pattern[q-1]){
      k++;
    }
    H[q-1] = k;
  }

  return H;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int n, m;
  //n stores the length of the text
  // m stores the length of the pattern
  transform(text.begin(), text.end(), text.begin(), ::tolower);
  transform(pattern.begin(), pattern.end(), pattern.begin(), ::tolower);

  n = text.length();
  m = pattern.length();
  hMatrix = computeHMatrixForKMP(pattern);
  int q = 0;

  for (int i = 1; i<=n; i++){
    while(q>0 && pattern[q]!=text[i-1]){
      q = hMatrix[q-1];
    }
    if (pattern[q]==text[i-1]){
      q++;
    }
    if (q==m){
      return (i - m); // returns the first occurrence of the word within the given text
    }
  }
  return -1;// returns -1 if no match found
}

#endif
