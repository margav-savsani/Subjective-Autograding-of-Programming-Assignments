#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int* hMatrix = new int(pattern.size());
  int len=0; //length of the previous longest prefix suffix
  hMatrix[0] = 0; //first elem is always 0
  int i=1;
  while(i<pattern.size())
  {
    if(pattern[i] == pattern[len])
    {
      len++;
      hMatrix[i] = len;
      i++;
    }
    else
    {
      if(len!=0) len = hMatrix[len-1];
      else
      {
        hMatrix[i]=0;
        i++;
      } 
    }
  }
  return hMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int patlen = pattern.size();
  int txtlen = text.size();
  int matchstartindex;
  int t = 0; //for iterating over text
  int p = 0; //for iterating over pattern
  while((txtlen-t) >= (patlen-p))
  {
    if(pattern[p] == text[t]){t++;p++;}
    if(p==patlen)
    {
      matchstartindex = t-p;
      p = hMatrix[p-1];
    }
    else if(t<txtlen && pattern[p]!=text[t])
    {
      //this means hmatrix[0,1,2..j-1] all characters will get matched anyways
      //so no need to check
      if(p!=0) p = hMatrix[p-1];
      else t=t+1;
    }
  }
  return matchstartindex;
}

#endif
