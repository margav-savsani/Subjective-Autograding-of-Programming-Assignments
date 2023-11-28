#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
 	int l=pattern.size();
	int A[l];
	A[0]=0;
	for(int i=1; i<l; i++){
		if (pattern[i] != pattern[i-1]){
			if (pattern[i] != pattern[0]) A[i]=0;
			else A[i]=1;
		}
		else A[i]+=A[i-1];		
	}		
  	return A;
}	
	
int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  return 0;
}	
	
#endif	
