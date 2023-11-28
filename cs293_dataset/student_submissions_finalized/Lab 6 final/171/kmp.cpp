#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int *h;
  h[0]=0;
  int k=0;
  for(int i=1;i<pattern.length();i++){
    if(pattern[k]==pattern[i]){
      k=k+1;
      h[i]=k;
    }
    if(pattern[k]!=pattern[i]){
      if(k!=0){
        k=h[k-1];
        i=i-1;
      }
      else{
        h[i]=0;
      }
    }
  }
  return h;

}
int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int N=text.length();
	int M=pattern.length();
	int *h;
	h=computeHMatrixForKMP(pattern);
	int i=0;
	int j=0;
	while((N-i)>=(M-j)){
		if(pattern[j]==text[i]){
			j++;
			i++;
		}
		if(j==M){
			return i-j;
			j=h[j-1];
		}
		else if(i<N && pattern[j]!=text[i]){
			if(j!=0) j=h[j-1];
			else i++;
		}
	}
  return -1;
}

#endif