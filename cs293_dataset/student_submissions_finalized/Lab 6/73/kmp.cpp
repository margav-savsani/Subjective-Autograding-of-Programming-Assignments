#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) 
{
  int *Hmatrix;
  int len=pattern.length();
  Hmatrix=new int[len];
  int start=1;
  int prevlargest=0;
  while(start<len)
  {
    if (pattern[start] == pattern[prevlargest])
    {
      prevlargest++;
      Hmatrix[start]=prevlargest;
      start++;
    }
    else if (prevlargest!=0)
    {
      prevlargest=Hmatrix[prevlargest-1];
    }
    else
    {
      Hmatrix[start]=0;
      start++;
    }
  }
  return Hmatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) 
{
  int lenp=pattern.length();
  int lent=text.length();
  hMatrix=computeHMatrixForKMP(pattern);
  int i=0,j=0;
  while((lent-i)>=(lenp-j))
  {
    if (pattern[j]==text[i])
    {
      j++;
      i++;
    }
    if (j==lenp)
    {
      return i-j;
    }
    else if(i<lent && pattern[j] != text[i])
    {
      if (j!=0)
        j=hMatrix[j-1];
      else
        i++;
    }
  }
  return 0;
}

#endif
