#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int reduce(int a){    //this function converts the char to uppercase to compare with case-insensitivity
  if(a>=97){
    return a-97+65;
  }
  else{
    return a;
  }
}

int *Planner::computeHMatrixForKMP(string pattern) {
  int len=pattern.length();   //the length of the pattern
  int *h=new int[len];        //the hMatrx that is to be computed
  h[0]=0;     
  int k=0;    
  for(int i=1;i<len;i++){
    while (k>0 && reduce(pattern.at(k))!=reduce(pattern.at(i))){
      k=h[k-1];   //computing h matrix using the previously computed values.
    }
    if(reduce(pattern.at(k))==reduce(pattern.at(i))){
      k++;
    }
    h[i]=k;
  }
  return h;   //returns the h matrix
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern){
  int textLength=text.length();   //length of the text.
  int patternLength=pattern.length();   //length of the pattern.
  int x=0;    

  for (int i=0;i<textLength;i++){
    while(x>0 && reduce(pattern.at(x))!=reduce(text.at(i))){
      x=hMatrix[x];   
    }
    if(reduce(pattern.at(x))==reduce(text.at(i))){
      x++;
    }
    if(x==patternLength){
      return i-patternLength+1;    //found
    }
  }
  return -1;    //not found
}

#endif
