#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int* hmatrix=new int[pattern.size()];
  string matching_pattern=pattern;
  hmatrix[0]=0;
  hmatrix[1]=0;
  int i=1,j=0;
  while(i<pattern.size()){
      if(pattern[i]==matching_pattern[j]){
         hmatrix[i+1]=j+1;
         j=j+1;
      }
      else{
         j=hmatrix[hmatrix[i]];
         while(j!=0){
            if(pattern[i]==matching_pattern[j]){
               hmatrix[i+1]=j+1;
               j=j+1;
               break;
            }   
            j=hmatrix[j];    
         }
         if(j==0){
            if(pattern[i]==matching_pattern[j]){
               hmatrix[i+1]=j+1;
               j=j+1;
            }   
            else{
               hmatrix[i+1]=0;
            }
         }
      }
      i=i+1;
  }
  return hmatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  
  return 0;
}

#endif

