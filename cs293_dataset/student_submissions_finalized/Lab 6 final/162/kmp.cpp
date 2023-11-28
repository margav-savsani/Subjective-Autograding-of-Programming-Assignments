#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {

  int stringLength = pattern.size();

  //convert to lowercase
  for (int i = 0; i < stringLength; i++)
  {
    pattern[i] = pattern[i] >='a'?pattern[i]:pattern[i] -'A' +'a';
  }
  

  int* hMatrix = new int[stringLength];
  
  hMatrix[0] = 0;

  int maxPrefixLength = 0;

  for (int i = 1; i < stringLength; i++)
  {
    pattern[i] = pattern[i] >='a'?pattern[i]:pattern[i] -'A' +'a';
    pattern[maxPrefixLength] = pattern[maxPrefixLength] >='a'?pattern[maxPrefixLength]:pattern[maxPrefixLength] -'A' +'a';
    while(maxPrefixLength > 0 && pattern[maxPrefixLength] != pattern[i] )
    {
      maxPrefixLength = hMatrix[maxPrefixLength-1];
    }

    if(pattern[maxPrefixLength] == pattern[i])
    {
      maxPrefixLength++;
    }
    hMatrix[i] = maxPrefixLength;
  } 

  return hMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{

  int n = text.size();
  int m = pattern.size();

  int maxPrefixLength = 0;
  int index  = 0;
  for (int i = 0; i < n; i++)
  {
    text[i] = text[i] >='a'?text[i]:text[i] -'A' +'a';
    pattern[maxPrefixLength] = pattern[maxPrefixLength] >='a'?pattern[maxPrefixLength]:pattern[maxPrefixLength] -'A' +'a';
    while(maxPrefixLength > 0 && pattern[maxPrefixLength] != text[i])
    {
      maxPrefixLength = hMatrix[maxPrefixLength-1];
    }
    if(pattern[maxPrefixLength] == text[i])
    {
      maxPrefixLength++;
    }
    if(maxPrefixLength == m-1)
    {
      index = (i+2-m);
      return index;
    }
  }
  
  return -1;
}

#endif
