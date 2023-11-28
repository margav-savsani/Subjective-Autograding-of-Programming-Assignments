#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;


int *Planner::computeHMatrixForKMP(string pattern) {
  // empty pattern so return nullptr
  if(pattern.length()==0)
    return nullptr;

  // The failure function or array/matrix for KMP algorithm
  int* hMatrix=new int[pattern.length()];
  hMatrix[0]=0;  // no matching proper suffix found leading to hMatrix[0]=0
  for(int i=1; i<pattern.length(); i++)
  {
    int highestmatch=hMatrix[i-1];  // this is 1 less than highest value which hMatrix[i] can take at any point of time
    bool found=false; // if we have found hMatrix[i]
    while(!found && highestmatch>0) // exit happens if found or highestmatch becomes 0... but not both
    {
      // case insensitive KMP
      if(pattern[highestmatch]==toupper(pattern[i]) || pattern[highestmatch]==tolower(pattern[i])) // we have found hMatrix[i] as proper suffix matches prefix of pattern
      {
        hMatrix[i]=highestmatch+1;
        found=true;
      }
      else  // we decrease highestmatch to hMatrix[highestmatch-1] which will be next highestmatch
      {
        highestmatch=hMatrix[highestmatch-1];
      }
    }
    if(highestmatch==0) // this means we still haven't found hMatrix[i]
    {
      if(pattern[0]==toupper(pattern[i]) || pattern[0]==tolower(pattern[i]))  // hMatrix[i] is 1 as longest proper suffix is pattern[i] which has length 1
      {
        hMatrix[i]=1;
      }
      else  // no matching proper suffix found leading to hMatrix[i]=0
      {
        hMatrix[i]=0;
      }
    }
  }
  return hMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  // trivial checks
  if(hMatrix==nullptr || text.length()==0 || pattern.length()==0)
    return -1;
  int currpatternpos=0; // pattern position at which comparision will take place next
  int currtextpos=0;  // text position at which comparision will take place next
  while(currtextpos<text.length())  // searching through entire text
  {
    // case insensitive KMP
    if((text[currtextpos]==toupper(pattern[currpatternpos])) || (text[currtextpos]==tolower(pattern[currpatternpos])))  // successful comparision
    {
      currpatternpos++;
      currtextpos++;
      if(currpatternpos==pattern.length())  // pattern match found
        return currtextpos-pattern.length();
    }
    else if(currpatternpos==0)  // no shift in pattern possible as we are already at beginning of pattern
    {
      currtextpos++;
    }
    else if(hMatrix[currpatternpos-1]!=0) // shift the pattern aptly
    {
      currpatternpos=hMatrix[currpatternpos-1];
    }
    else  // hMatrix[currpatternpos-1]=0
    {
      if((text[currtextpos]==toupper(pattern[0])) || (text[currtextpos]==tolower(pattern[0])))
      {
        currpatternpos=1;
        currtextpos++;
        if(currpatternpos==pattern.length())  // pattern match found
          return currtextpos-pattern.length();
      }
      else  // no match and also no further shift possible in pattern
      {
        currpatternpos=0;
        currtextpos++;
      }
    }
  }
  return -1;
}

#endif
