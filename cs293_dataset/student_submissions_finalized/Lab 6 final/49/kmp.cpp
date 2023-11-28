#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int hvalue(string pattern){// to calculate h value of a string
  int l = pattern.size();
  int m = 0;
  if(l==1)return m;
  string preffix[l-1];// array of strings to store preffixes of string
  string suffix[l-1];// array of strings to store suffixes of string
  for(int i=1;i<l;i++){
    preffix[i-1]=pattern.substr(0,i);
    suffix[i-1]=pattern.substr(l-i);    
  }
  for(int i=0;i<l-1;i++){
    if(preffix[i]==suffix[i]){// comparing both and returning hvalue
      if(m<preffix[i].size())m=preffix[i].size();
    }
  }
  return m;
}

int *Planner::computeHMatrixForKMP(string pattern) {// hmatrix calculation using hvalue function
   int *lps = new int[pattern.size()];
  for(int i=0;i<pattern.size();i++){
    lps[i]= hvalue(pattern.substr(0,i+1));
  }  
  return lps; 
}

// KMPMatch function returns first index if text is present in pattern otherwise it returns -1
int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int txtsz = text.size();                                        
  int patsz = pattern.size();
  int i = 0,j=0; 
  while((txtsz-j)>=(patsz-i)){
    if(pattern[i]==text[j]){
      i++;
      j++;
      if(i==patsz){
        return j-i;
        i = hMatrix[i-1];
      }
    }  
    else if((j<txtsz)&&(pattern[i]!=text[j])){
      if(i!=0) 
        i = hMatrix[i-1];
      else
        j = j+1;  
    }
  }
  return -1;  
}

#endif
