#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int* hMatrix = new int[pattern.length()]; //hmatrix contains the values of longest prefix suffix
  int len=0;      //length of the previous longest prefix suffix
  hMatrix[0] = 0; //first elem is always 0
  int i=1;
  // this loop calculates the values of longest prefix suffix
  // for i=1 to M-1
  while(i<pattern.length())
  {
    //till it matches
    if(pattern[i] == pattern[len])
    {
      len++;
      pattern[i] = len;
      i++;
    }
    //at this point it doesn't match
    //and now we have to jump, store how much jump is needed
    else
    {

      //when jump length is not 0, then i doesn't get incremented
      if(len!=0) len = hMatrix[len-1];
      
      //incrementing i too when jump length is 0
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
  int patlen = pattern.length();
  int txtlen = text.length();
  int t = 0; //for iterating over text
  int p = 0; //for iterating over pattern
  while(t<txtlen)
  {
    //till it matched
    if(text[t]==pattern[p]){  t++; p++; }
    //unmatch
    else
    {
      if(p!=0)  p = hMatrix[p-1];
      //when first is not matching move one step right
      else t++;
    }
    if(p==patlen)
    {
      return t-p; //returns the match start index
    }
  }
  return -1; // return value -1 indicates no match
}

#endif
