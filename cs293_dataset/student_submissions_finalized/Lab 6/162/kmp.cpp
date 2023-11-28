#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {

  int stringLength = pattern.size();
  int* hMatrix = new int[stringLength];
  
  hMatrix[0] = 0;

  int maxPrefixLength = 0;

  for (int i = 1; i < stringLength; i++)
  {
    
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

  int i = 0;
  int j = 0;
  int count = 0;
  while(text[i] != '\0')
  { 
    
    if(text[i] == pattern[j])
    {
      j++; 
      if(j == pattern.size())
      {
        count++;
      }
    }
    else
    { 
      if(j != 0)
      {
        j = (j-1) - hMatrix[j-1];
      }
      
    }
    i++;
  }
  return count;
}

#endif
