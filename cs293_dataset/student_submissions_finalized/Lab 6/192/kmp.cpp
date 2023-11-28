#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {

  int n = pattern.length();
  int * h = new int[n];

  h[0] = 0;
  

  for (int i = 1; i < n; i++){
    if (pattern[h[i-1]] == pattern[i]){
        h[i] = h[i-1] + 1;
    } else {
        int k = h[h[i-1]];
        while (k > 0){
          if (pattern[k+1] == pattern[i]){
            h[i] = k + 1;
            break;
          } else {
            k = k[h];
          }
        }
        if (k > 0) break;
        else {
          if (pattern[i] == pattern[0]){
            h[i] = 0;
          } else {
            h[i] = 1;
          }
        }
    }

    return h;
  }

  return nullptr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int count = 0;
  int strLength = text.length();
  int patLength = pattern.length();

  int* hMatrix = computeHMatrixForKMP(pattern);


  int i = 0;
  int j = 0;
  for(; i < strLength - patLength + 1;){
    if (text[i+j] == pattern[j]){
      if (j+1 == patLength){
        count++;
        i = i + j + 1;
        j = 0;
        continue;

      } else {
        j++;
      }

    } else {
        i = i + j - hMatrix[j];
        j = hMatrix[j];


      
    }
  }

  return 0;
}

#endif
