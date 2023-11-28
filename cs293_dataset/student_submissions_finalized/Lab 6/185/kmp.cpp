#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int len_p = pattern.size();
  int *mat = new int[len_p];
  mat[0] = 0;
  int itr = 0;

  for(int i=1; i<len_p; i++){

    //if(i==1){
      //pattern[i]= pattern[itr-1];
    //}
    if(pattern[i]==pattern[itr]){
      itr++;
      mat[i]=itr;
    }
    else{
      if(itr != 0){
        itr = mat[itr - 1];
      }
      else{
        mat[i] = 0;
      }
    }
  }

  return mat;
  //return nullptr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {



  return 0;
}

#endif
