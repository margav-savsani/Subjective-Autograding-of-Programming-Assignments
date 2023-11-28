#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  
  int len = pattern.length();
  int *hMatrix = new int[len];

  hMatrix[0] = 0; //This is always true. Used to compute upcoming entries.

  int i=1; 
  int matchIndex = hMatrix[0];
  while(i<len)
  {
    if(pattern[i]==pattern[matchIndex])
    {
      hMatrix[i] = matchIndex+1; //If match is found, total no. of matches increases by 1, thus increasing the length of matching suffic-prefix by 1.
      matchIndex = hMatrix[i];
      i++;
    }
    else //If ther is a mismatch, we shift the pattern until match is found.
    {
      
      if(matchIndex !=0) matchIndex = hMatrix[matchIndex];

      else //If no match is found and pattern is exhausted, failure function of that index gets assigned 0 as value.
      {
        hMatrix[i] = 0;
        i++;
      }
    }
    
  }
  

  return hMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  

  int pLen = pattern.length(), tLen=text.length();

  for(int i=0;i<tLen;i++)
  {
    text[i] = toupper(text[i]); //Converts the text to UPPERCASE
  }

  for(int i=0;i<pLen;i++)
  {
    pattern[i] = toupper(pattern[i]); //Converts the pattern to UPPERCASE. This makes KMPMatch case insensitive.
  }

  int i=0; //Index for text
  int j=0; //index for pattern

  while(tLen-i >= pLen-j) //The condition that length of matching part of Text should be greater than or equal to the length of matching part of pattern. 
  {
    if(pattern[j]==text[i]) //If match is found, check for a match b/w the next indices of both pattern and string.
    {
      i++;j++;
    }

    if(j==pLen) //if j is equal to pattern length, a match for pattern is found.
    {
      return i-j; //Index of where the match was found.
    }

    else if(i<tLen && pattern[j]!= text[i]) //If j is not equal to pattern length and there's a mismatch
    {
      if(j!=0) //If j is not 0, we shift the pattern by h(j-1)
      {
        j = hMatrix[j-1];
      }
      else i++; //If j is 0, we shift it by 1;
    }
  }
  return -1; //When no match is found.
}

#endif
