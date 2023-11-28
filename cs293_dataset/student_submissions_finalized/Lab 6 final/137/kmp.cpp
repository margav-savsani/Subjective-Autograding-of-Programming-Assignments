#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  //function to compute H matrix for the KMP.
  if(pattern != "")
  {
    int len = pattern.length();
    int l = 0;
    int *hMatrix = new int[len];
    hMatrix[0] = 0;
    int i = 1;
    while(i<len)
    {
      if(int(pattern[i]) - 65 == int(pattern[l]) - 65 || int(pattern[i]) - 65 == int(pattern[l]) - 97 || int(pattern[i]) - 97 == int(pattern[l]) - 65 || int(pattern[i]) - 97 == int(pattern[l]) - 97)    //checkin if the suffix matches with the prefix.
      {
        hMatrix[i] = l + 1;   //updating the value of element in ith postion of H matrix. 
        l += 1;
        i += 1;
      }
      else
      {
        if(l!=0)
        {
          l = hMatrix[l-1];
        }
        else
        {
          hMatrix[i] = 0;
          i += 1;
        }
      }
    }
    return hMatrix;
  }
  return nullptr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  //function to find the pattern in text.
  int n = text.length();
  int m = pattern.length();
  int j = 0;
  int i = 0;
  while(i<n-m+1)
  {
    if(int(text[i]) - 65 == int(pattern[j]) - 65 || int(text[i]) - 65 == int(pattern[j]) - 97 || int(text[i]) - 97 == int(pattern[j]) - 65 || int(text[i]) - 97 == int(pattern[j]) - 97)   //matching the elements of text with elements of pattern.
    {
      i += 1;
      j += 1;
    }
    else
    {
      if(j != 0)
      {
        j = hMatrix[j-1];   //shifting the pattern if there's a mismatch.
      }
      else
      {
        i += 1;
      }
    }
    if(j == m)
    {
      return i - j;   //returning the starting index of the word.
    }
  }
  return -1;
}

#endif
