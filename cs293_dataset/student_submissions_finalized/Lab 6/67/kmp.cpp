#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
	int len=pattern.length();
	int* hMatrix=new int[len];
	hMatrix[0]=0;
	for(int i=1;i<len;i++){
		if(hMatrix[i-1]==0){
			if(pattern[0]==pattern[i]){
				hMatrix[i]==1;
			}
		}
	return hMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

	return 0;
}

#endif
