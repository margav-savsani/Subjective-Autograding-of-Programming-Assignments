#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

//computes memoizing matrix for given pattern
int *Planner::computeHMatrixForKMP(string pattern) {
  int len=0;
  int *harr=new int[pattern.length()];
  harr[0]=0;

  //computes for every letter in pattern
  for(int i=1;i<pattern.length();){
    //if suffix matches with prefix then simply make one more than previous
    if(pattern[i]==pattern[len]){
      len++;
      harr[i]=len;
      i++;
    }

    //if it doesn't matches then check for another smaller prefix
    else{
      if(len!=0){
        len=harr[len-1];
      }
      else{
        harr[i]=0;
        i++;
      }
    }
  }
  return harr;
}

//does pattern matching using kmp algorithm
//shifting in pattern is done by elements of hmatrix values at position of missmatch
int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int n=text.length(),m=pattern.length();
  int i=0,j=0;
  while(n-i>=m-j){      
    if(pattern[j]==text[i]){            //looking upto missmatch doesn't found
      i++;
      j++;
    }
    else if(i<n && pattern[j]!=text[i]){        //shifts pattern after missmatch
      if(j!=0)j=hMatrix[j-1];
      else i++;
    }
    if(j==m){
      return i-j;
    }
  }
  return -1;
}

#endif
