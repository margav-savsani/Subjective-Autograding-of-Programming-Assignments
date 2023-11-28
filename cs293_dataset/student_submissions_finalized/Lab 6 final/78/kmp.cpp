#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int size=pattern.length();
  int *hmatrix = new int[size];
  hmatrix[0]=0;
  int pre_len=0;
  
  int i=1;
  //going on matching the patterns and collecting count of matched characters 
  while (i<size){
    if(pattern[i]==pattern[pre_len]){
      pre_len++;
      pattern[i]=pre_len;
      i++;
    }
    else{
      if(pre_len==0){
        hmatrix[i]=0;
        i++;
      }
      else{
        pre_len=hmatrix[pre_len-1];
      }
    }
  }
  return hmatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int t_cnt,p_cnt=0,match=-1;
  int t_len=text.length();
  int p_len=pattern.length();
  int *h_func_arr = computeHMatrixForKMP(pattern);
  while(t_cnt<t_len){
    if(text[t_cnt]==pattern[p_cnt]){
      p_cnt++;
      t_cnt++;
    }
    else{
      if(p_cnt!=0){
        p_cnt=h_func_arr[p_cnt-1];
      }
      else{
        t_cnt++;
      }
    }
    if(p_cnt==p_len){
      match=t_cnt - p_cnt;
      break;
    }
  }
  return match;
}

#endif
