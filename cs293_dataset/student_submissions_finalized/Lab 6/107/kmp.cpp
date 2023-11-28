#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  if(pattern.length()==0)
    return nullptr;

  // The failure function or array for KMP algorithm
  int hMatrix=new int[pattern.length()];
  hMatrix[0]=0;
  for(int i=1; i<pattern.length(); i++)
  {
    int highestmatch=hMatrix[i-1];
    bool found=false;
    while(!found && highestmatch>0)
    {
      if(pattern[highestmatch]==pattern[i])
      {
        hMatrix[i]=highestmatch+1;
        found=true;
      }
      else
      {
        highestmatch=hMatrix[highestmatch-1];
      }
    }
    if(highestmatch==0)
    {
      if(pattern[0]==pattern[i])
      {
        hMatrix[i]=1;
      }
      else
      {
        hMatrix[i]=0;
      }
    }
  }
  return hMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  if(hMatrix==nullptr || text.length()==0 || pattern.length()==0)
    return -1;
  int currpatternpos=0;
  int currtextpos=0;
  while(currtextpos<text.length())
  {
    if(text[currtextpos]==pattern[currpatternpos])
    {
      currpatternpos++;
      currtextpos++;
      if(currpatternpos==pattern.length())
        return currtextpos-pattern.length();
    }
    else if(hMatrix[currpatternpos-1]!=0)
    {
      currpatternpos=hMatrix[currpatternpos-1];
    }
    else
    {
      if(text[currtextpos]==pattern[0])
      {
        currpatternpos=1;
      }
      else
      {
        currpatternpos=0;
      }
      currtextpos++;
    }
  }
  return -1;
}

#endif
