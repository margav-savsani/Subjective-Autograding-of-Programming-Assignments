#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int hvalue(string pattern){
  int l = pattern.size();
  int m = 0;
  if(l==1)return m;
  string preffix[l-1];
  string suffix[l-1];
  for(i=1;i<l-1;i++){
    preffix[i-1]=pattern.substr(0,i);
    suffix[i-1]=pattern.substr(l-i);
  }
  for(i=0;i<l-1;i++){
    if(preffix[i]=suffix[i]){
      if(m<i+1)m=i+1;
    }
  }
  return m;
}
int *Planner::computeHMatrixForKMP(string pattern) {
  int *lps = new int(pattern.size());
  for(int i=0;i<pattern.size();i++){
    lps[i]= hvalue(pattern.substr(0,i+1));
  }  
  return lps;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  hMatrix = computeHMatrixForKMP(pattern);
  int i = 0;
  int j = 0;
  while(true){
    if(pattern[i]==text[j]){
      i++;
      j++;
    }  
    else
  }
  return 0;
}

#endif
