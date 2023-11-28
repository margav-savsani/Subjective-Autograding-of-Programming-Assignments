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
		int curr=hMatrix[i-1];
		bool cont=false;
		while(curr!=0){
			if((pattern[curr]|32)==(pattern[i]|32)){
				hMatrix[i]=curr+1;
				cont=true;
				break;
			}
			curr=hMatrix[curr-1];
		}
		if(cont)	continue;
		if((pattern[0]|32)==(pattern[i]|32)){
			hMatrix[i]=1;
			continue;
		}else{
			hMatrix[i]=0;
		}
	}
	return hMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

	int len=text.length();
	int len_pattern=pattern.length();
	if(len_pattern==0)	return 0;
	int matched=0;
	int ans=-1;
	for(int i=0;i<len;i++){
		if((pattern[matched]|32)==(text[i]|32)){
			matched++;
			if(matched==len_pattern){
				ans=i-matched+1;
				break;
			}
			continue;
		}
		if(matched==0)	continue;
		int curr=hMatrix[matched];
		while(curr){
			if((pattern[curr]|32)==(text[i]|32)){
				matched=curr;
				break;
			}
			curr=hMatrix[curr-1];
		}
		if(curr==0){
			if((pattern[0]|32)==(text[i]|32)){
				matched=1;
			}
		}
		if(matched==len_pattern){
			ans=i-matched+1;
			break;
		}
	}

	return ans;
}

#endif
