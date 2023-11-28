#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int* Hfunc = new int[pattern.length()];
  Hfunc[0] = 1;
  int shift = 1;

  for( int assigner = 1; assigner < pattern.length(); assigner++){

    while( pattern[assigner - shift] != pattern[assigner] && shift < assigner){
      shift += Hfunc[assigner - shift];
    }
    if( pattern[assigner - shift] != pattern[assigner] ){
      shift++;
    }
    Hfunc[assigner] = shift;
  }

  return Hfunc;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  //int count = 0;
  int shift = 0;

  while(shift < text.length() ){
    bool mismatch = false;
    for(int i=0 ; i < pattern.length(); i++){
      if(text[shift + i] != pattern[i]){
        shift += hMatrix[i];
        mismatch = true;
        break;
      }
    }
    if(!mismatch){
      //count++;
      shift += pattern.length();
      return shift;
    }
  }
  return -1;
}

#endif
