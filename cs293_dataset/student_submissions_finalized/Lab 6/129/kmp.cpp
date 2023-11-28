#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;


int *Planner::computeHMatrixForKMP(string pattern) {
  int l =pattern.length();
  int z[l];
  int x=0;
  if(l == 0) return nullptr;
  z[0]=0;
  for(int i=1;i<l;i++){
    if(pattern[z[i-1]]==pattern[i]){
      z[i]=z[i-1]+1;
      x=l[i];
    }
    else{
      while(x!=0){
        if(pattern(z[x-1])==pattern[i]){
          z[i]=z[x-1]+1;
          x=z[i];
          break;
        }
        x=z[x-1];
        


      }
    }}
    return z;
    

  }
  


int Planner::KMPMatch(string text, int *hMatrix, string pattern) {


  return 0;
}

#endif
