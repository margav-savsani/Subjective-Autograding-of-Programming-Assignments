#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) 
{
  int *Hmatrix; //matrix for shifting
  int len=pattern.length();
  Hmatrix=new int[len];
  int start=1;
  int prevlargest=0;
  while(true)
  {
    if (start == len) //end of matrix
      return Hmatrix;
    if (pattern[start] == pattern[prevlargest])
    {//checking for same char i.e., shift by k
      prevlargest++;
      Hmatrix[start]=prevlargest;
      start++;
    }
    else if (prevlargest!=0)
    {//shift
      prevlargest=Hmatrix[prevlargest-1];
    }
    else
    {//if not found
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
  int st=0,sp=0;
  while(true)
  {// at last
    if(lent-st < lenp-sp)
      return -1;
    if (pattern[sp]==text[st])
    {//checking for same chars
      sp++;
      st++;
    }
    if (sp==lenp)
    {//if pattren is found
      return st-sp;
    }
    else if(st<lent && pattern[sp] != text[st])
    {//if some are same the shift the i and j
      if (sp!=0)
        sp=hMatrix[sp-1];
      else
        st++;
    }
  }
  return -1;
}

#endif
//by saran 210050036