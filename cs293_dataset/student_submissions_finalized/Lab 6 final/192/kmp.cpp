#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {

  int n = pattern.length();
  int *h = new int[n]; //define the prefix matrix

  h[0] = 0; 
  //compute the values of the prefix matrix 
  for (int i = 1; i < n; i++){
    int j = h[i - 1];


    bool found = false;
    while(j != 0){
      //if the next character of the last matched prefix matches with the next character of the text.
      if (pattern[j] == pattern[i]){
        //simply update the value of of h[i]
        h[i] = j + 1;

        found = true; // pattern was found
        break;
      } else {
        j = h[j - 1]; //find the largest matching proper prefix of the last matched prefix
                      //equivalent to shifting the pattern appropriately       
      }
    }
    if(!found){
      // we know that j = 0 so just check the matching of the current character with the first character of the pattern.
      if (pattern[i] != pattern[j]){
        h[i] = 0;
      } else {
        h[i] = 1;
      }
    }
  }

  


  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int tlength = text.length();
  int plength = pattern.length();
  int count = 0;
  
  int* hmatrix = computeHMatrixForKMP(pattern);
  
  int i = 0;
  int j = 0;
  while (i < tlength){
    if (text[i] == pattern[j]){
      //if matching characters found, just advance the pattern and the text to the next character.
      i++;
      j++;

      if (j == plength){
        //if match found, return the first index of the found match
        return (i-j);
        break;
      }
    } else {
      if (j == 0){
        //if no prefix matches, start with the next character.
        
        i++;
      } else {
        j = hMatrix[j-1];
      }
    }
  }


  return -1;
}

#endif
