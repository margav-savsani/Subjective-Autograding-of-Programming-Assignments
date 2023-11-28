#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {

  int m = pattern.length();
  int *h = new int[pattern.size()];
  h[0]=0;
  
  for(int i=1;i<m;i++){
  	int j = h[i-1];
  	while(j>0 && pattern[i]!=pattern[j]){
  		j=h[j-1];
    }
  	
  	if(pattern[i]==pattern[j]){
  	j++;
  	h[i]=j;
    }
  }
  return h;

}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  int count = 0;
  int m = pattern.length();
  int n = text.length();
  hMatrix = computeHMatrixForKMP(pattern);

  int i =0;
  int j =0;

  while ((n - i) >= (m - j)) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }
 
        if (j == m) {
            count++;
            j = hMatrix[j - 1];
        }
 
        // mismatch after j matches
        else if (i < n && pattern[j] != text[i]) {
            // Do not match hmatrix[0..hmatrix[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = hMatrix[j - 1];
            else
                i = i + 1;
        }
    }

  return count;
}

#endif

