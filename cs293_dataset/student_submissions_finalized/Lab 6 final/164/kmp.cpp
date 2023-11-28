#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {

  int *h= new int[pattern.length()];
  h[0]=0;
  for(int i=1;i<pattern.length();i++)
  { int j=i;
  bool b=false;
    while(j>0){
    if(pattern[i]==pattern[h[j-1]])
    {
      h[i]=h[j-1]+1;
    b=true;
      break;
    }
    else {
      j=h[j-1];
    }
  }
  if(!b)
  {h[i]=0;}
  }
  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
 int a=0;
  int j=0;
  while(a<text.length()-1){
    for(int i=0;i<pattern.length();i++)
    {
      if(pattern[i]!=text[a+i])
      {
        if(hMatrix[i]==0)
        {
            a=a+1;
            break;
        }
        else {a=a+i-hMatrix[i];
        break;}
      }
    if(i==pattern.length()-1)
    {
        return a;
    }
    }
    
  }
  return -1;
}

#endif
