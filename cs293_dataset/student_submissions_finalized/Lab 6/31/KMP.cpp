#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {

  int *hMatrix = new int[pattern.length()];

  hMatrix[0]=0;
  if(pattern[0]==pattern[1])
    hMatrix[1]=1;
  else hMatrix[1]=0;
  for(int i=2; i<pattern.length(); i++){
    if(pattern[i]==pattern[hMatrix[i-1]])
      hMatrix[i]=hMatrix[i-1]+1;
    //To Be Continued

  }

  return nullptr;
}

int searchind(string text, string pattern, int textind){
  assert(pattern.length() <= text.length());
  for(int i=0; i<pattern.length(); i++){
    if(text[textind+i]!=pattern[textind+i])
      return i;
  }

  //if pattern matched, return -1
  return -1;
}
int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  int ind=0;
  while(ind<=text.length()-pattern.length()){
    int r = searchind(text,pattern,0);

    if(r==-1)
      return 1;
    else
      ind=ind+r-hMatrix[r-1];

  }
  return 0;
}

#endif
