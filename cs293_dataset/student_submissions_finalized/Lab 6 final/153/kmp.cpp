#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#include "codes.h"

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int pat_len = pattern.length();
  int* res = (int*) malloc(pat_len * sizeof(int));
  fill_n(res, pat_len, 0);
  int h_val=0, itr=1;

  while(itr < pat_len){
    if(pattern.at(h_val) == pattern.at(itr)){
      h_val++;
      res[itr] = h_val;
      itr++;
    }else{
      if(h_val == 0){
        res[itr] = h_val;
        itr++;
      }else h_val = res[h_val-1];
    }
  }

  for(itr=1; itr<pat_len-1; itr++){
    while(res[itr]!=0 && pattern.at(itr+1)==pattern.at(res[itr])){
      res[itr] = res[res[itr]-1];
    }
  }

  return res;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int pat_begin=0, pat_len_matched=0, ti=0, i;
  int plen=pattern.length(), tlen=text.length();

  for(i=0; i<plen; i++) pattern[i]=tolower(pattern.at(i));
  for(i=0; i<tlen; i++) text[i]=tolower(text.at(i));

  while(pat_len_matched < plen && ti<tlen){
    if(text.at(ti) == pattern.at(pat_len_matched)){
      pat_len_matched++;
      ti++;
    }else{
      if(pat_len_matched == 0) ti++;
      else pat_len_matched = hMatrix[pat_len_matched - 1];
    }
  }

  if(pat_len_matched == plen) return ti-plen;
  else return -1;
}

#endif
