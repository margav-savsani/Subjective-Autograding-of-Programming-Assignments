#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int l=pattern.length();
  int hm[l];
  int len=0;
  hm[0]=0;
  cout<<"hbgvchy"<<endl;
  for(int i=1;i<l;i++){
  	if(pattern[i]==pattern[len]){
  		len++;
  		hm[i]=len;
  	}
  	else if(len!=0){
  		len=hm[len-1];
  		i--;
  	}
  	else hm[i]=0;
  }
  return h;

}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int t=text.length();
	int p=pattern.length();
	int h[p];
	h=ComputeHMatrixForKMP(pattern);
	int i=0;
	int j=0;
	while((N-i)>=(M-j)){
		if(pat[j]==txt[i]){
			j++;
			i++;
		}
		if(j==M){
			return i-j;
			j=h[j-1];
		}
		else if(i<N && pat[j]!=txt[i]){
			if(j!=0) j=hm[j-1];
			else i++;
		}
	}
  return -1;

 
}

#endif
