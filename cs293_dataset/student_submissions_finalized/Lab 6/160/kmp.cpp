#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern){
	int m;
	m=pattern.length();
	if(m==0) return nullptr;
	int* h=new int[m];
	int c=0;
	h[0]=0; 
	int i=1;
	while(i<m){
		if(pattern[i]==pattern[c]){
			c++;
			h[i]=c;
			i++;
		}
		else{
			if(c!=0){
				c=h[c-1];
			}
			else{
				h[i]=0;
				i++;
			}
		}
	}
	return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
	int c=0,i=0,j=0;
	int m=pattern.length();
	int n=text.length();
	if(m==0||n==0) return -1;
	int* h;
	h=computeHMatrixForKMP(pattern);
	while((n-i)>=(m-j)){
		if(pattern[j]==text[i]){
			j++;
			i++;
		}
		if(j==m){
			c++;
			j=h[j - 1];
		}
		else if((i<n)&&(pattern[j]!=text[i])){
			if(j!=0) j = h[j - 1];
			else i++;
		}
	}
	return c;
}

#endif
