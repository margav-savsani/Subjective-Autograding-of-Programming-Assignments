#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int Planner::matcher(string pattern, int p){
	int k;
	if(p==0||p==pattern.length()-1){return 0;}
	for(int i=p; i<pattern.lenght-1; i++){
		if(pattern[i-p]==pattern[p]){k=p;}
		else{k=0; break;}
	}
}

int *Planner::computeHMatrixForKMP(string pattern) {
	if(pattern.length()=0) return nullptr;
	
	int* A=new int[pattern.length()][2];
	
	for(int i=0; i<pattern.length(); i++){
		A[i][0]=i+1;//since in kmp, we use indexing starting from 1 not 0
	}
	A[0][1]=0;
	A[1][1]=0;//the failure fuction is 0 for bothe the first and second alphabet on the string
	
	for(int i=2; i<pattern.length(); i++){
		int k=0;
		for(int j=i; j>0; j--){
			m=matcher(pattern.resize(i+1), j);//matches 
			if(m>=k){k=m;}
		}
		A[i][1]=k;
	}

	return A;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

	return 0;
}

#endif
