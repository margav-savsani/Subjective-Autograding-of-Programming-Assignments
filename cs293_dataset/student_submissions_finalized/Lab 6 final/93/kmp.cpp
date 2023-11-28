#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern){
	if(pattern == "")
		return NULL;
	int* hmatrix = new int[pattern.size()];
	int m = pattern.size();
	hmatrix[0] = 0;
	int k = 0;
	for(int q = 1; q<m; q++){
		// cout<<k<<" "<<m<<endl;
		while(k>0 && toupper(pattern.at(k)) != toupper(pattern.at(q)))
			k = hmatrix[k-1];
		if(toupper(pattern.at(k))==toupper(pattern.at(q)))
			k+=1;
		hmatrix[q] = k;
	}
	return hmatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern){
	int n = text.size();
	int m = pattern.size();
	int q = 0;
	for(int i{0}; i<n; i++){
		while(q>0 && toupper(pattern.at(q)) != toupper(text.at(i)))
			q = hMatrix[q-1];
		if(toupper(pattern.at(q)) == toupper(text.at(i)))
			q+=1;
		if(q==m)
			return (i-m+1);
	}
	return -1;
}

#endif