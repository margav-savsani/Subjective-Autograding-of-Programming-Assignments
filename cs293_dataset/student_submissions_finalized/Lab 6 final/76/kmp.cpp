#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {

  int n=pattern.size();
  int *pat = new int[pattern.size()];
  pat[0]=0;

  for(int i=1;i<n;i++){
    int j=pat[i-1];
    while(j>0 && pattern[i]!=pattern[j])  //if not matched
      j=pat[j-1];//update j
    
    if(pattern[i]==pattern[j])  //if matched
      j++;
      pat[i]=j;
     
  }
  return pat;//return hmatrix
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int p=pattern.length();
  
  int t=text.length();
  int i=0,j=0;
  while(i<t){//iterating till we reach end
      if(pattern[j]==text[i]){i++;j++;} // If  matched continue.
      if (j == p) {    // if j==p we return index of text
            return i - p ;
                                 
            j = hMatrix[j - 1]; 
        } 
      else if (i < t && pattern[j] != text[i]) {//if not matched
          if (j == 0)          // if j becomes 0 then i=i+1
              i++;
            else
                j = hMatrix[j - 1];  //Update j 
        }
    }
return -1;
}

#endif
