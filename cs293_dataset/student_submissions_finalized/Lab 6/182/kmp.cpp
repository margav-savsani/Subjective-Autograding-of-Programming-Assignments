#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {

   int* pi=new int[pattern.length()];
   int j=0 ;
   for (int i=0;i<pattern.length();i++){
      while (j>=0 && pattern[j]!=pattern[i])
         if (j-1>=0)
                j=pi[j-1];
         else
                j=-1 ;
      j+=1;
      pi[i]=j;
      }
   return pi;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  
  return 0;
}

#endif
