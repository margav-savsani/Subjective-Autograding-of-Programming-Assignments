#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
  //Calculate length of pattern
  int len = pattern.length();
  int *h=new int[len]; //h matrix for KMP
  h[0] = 0;
  int j = 0;

  //Parse through pattern to calculate h
  for(int i = 1; i < len; i++)
  {
    //As long as ith and jth elements of pattern do not match, keep updating j, unless it becomes 0
    while(j > 0 && pattern[j] != pattern[i])
    {
      j = h[j-1];
    }

    //If ith and jth elements of pattern are 0
    if(pattern[j] == pattern[i])
    {
      j++; 
    }

    h[i] = j;
  }
  //Return h matrix
  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
  //Store length of pattern and text
  int n = text.length();
  int m = pattern.length();
  int i = 0,j = 0;

  while(i < n)
  {// Parse through text
    //If jth element of pattern and ith element of text become equal
    if(pattern[j] == text[i])
    {
      i++;
      j++;
    }

    //If j becomes equal to the length of the pattern
    if(j == m)
    {
      return (i - m);
    }
    
    //If a mismatch is found
    else if(i < n && pattern[j] != text[i])
    {
      //Increase value of i by 1 if j is zero
      if(j == 0)
      {
        i++;
      }

      //Update value of j if nonzero
      else
      {
        j = hMatrix[j-1];
      }
    }
  }
  return -1;
}

#endif
