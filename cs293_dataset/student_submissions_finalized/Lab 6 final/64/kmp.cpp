#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;
//Here we compute the array which is used in KMP algorithm. It is formed by preprocessing the pattern.
int *Planner::computeHMatrixForKMP(string pattern) {
  int n=pattern.length();
  int *h = new int;
  for(int i=0; i<n; i++){
    h[i]=0;
  }
  for(int i=1; i<n; i++){
    int j=h[i-1];
    while(j>0 && toupper(pattern[i])!=toupper(pattern[j])){    //Here we match the keyword at index j with i recursively
      j=h[j-1];                              //we use the values that have already been computed in the H matrix and use them to compute
    }                                        //current value.
    if(toupper(pattern[j])==toupper(pattern[i])){
      j++;
    }
    h[i]=j;
  }
  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int n=text.length();
  int i=0;
  int j=0;
  bool found = false;
  while(i<n){
    if(toupper(text[i])==toupper(pattern[j])){          //if letter and i and j matches then we increment both
      i++;
      j++;
    }
    else{
      if(j!=0){                       //else we go to the value of the hmatrix of previous j and set this value to j
        j=hMatrix[j-1];               //if j is 0 then we increment i
      }else{
        i++;
      }
    }
    if(j==pattern.length()){          //if the pattern is finished i.e. j reaches to the end of pattern then
      found = true;                   //the pattern is found in the text
      return i-pattern.length();
    }
  }
  if(found==false){
    return -1;
  }
}

#endif
