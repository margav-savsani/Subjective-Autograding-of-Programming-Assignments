#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {

  if ( pattern.length() == 0 )
  
  	return nullptr;
  else {
  
  	int h[pattern.length()];
  	int first = 0;
  	int second = 1;
  	h[0] = 0;
  }
  	
  	
  return nullptr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  return 0;
}

#endif
