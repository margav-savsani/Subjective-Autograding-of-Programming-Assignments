#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int len=pattern.size();
  int* h_arr=new int[len];
  h_arr[0]=0;
  int border_len=0;
  for(int i=1;i<len;i++){
    while(border_len >= 1 && toupper(pattern[border_len]) != toupper(pattern[i])){
      border_len=h_arr[border_len-1];
    }
    if(toupper(pattern[border_len]) == toupper(pattern[i])) border_len++;
    h_arr[i]=border_len;
  }
  return h_arr;  
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int t = text.size();
  int p = pattern.size();
  int j=0;
  int l=1;
  while(j <= t-p){
    int k=j;    
    if(toupper(pattern[0]) != toupper(text[j])) {j++;}
    else for(int i=l;i<p;i++){      
      if(toupper(pattern[i]) != toupper(text[i+j])){
        j = j+i-hMatrix[i-1];
        l = hMatrix[i-1];
        break;
      }
    }
    if(j == k) return j ;
  }    
  return -1;  
}

#endif
