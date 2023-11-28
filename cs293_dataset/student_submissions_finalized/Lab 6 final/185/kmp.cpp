#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int len_p = pattern.size();
  int *mat = new int[len_p];
  mat[0] = 0;
  int itr = 0;

  for(int i=1; i<len_p; i++){
    if(pattern[i]==pattern[itr]){
      itr++;
      mat[i]=itr;
    }
    else{
      if(itr != 0){
        itr = mat[itr - 1];
        i--;
      }
      else{
        mat[i] = 0;
      }
    }
  }

  return mat;
  //return nullptr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int txt = text.size();
  int patt = pattern.size();

  int match = 0;

  int idx_text = 0;
  int idx_patt = 0;

  while((txt-idx_text) >= (patt - idx_patt)){
    if(pattern[idx_patt] == text[idx_text]){
      idx_patt++;
      idx_text++;
    }
    if(idx_patt == patt){
      match++;
      return idx_patt;  //returns the index of the first match
      idx_patt = hMatrix[idx_patt-1];
    }
    else if(idx_text < txt && pattern[idx_patt] != text[idx_text]){
      if(idx_patt != 0){
        idx_patt = hMatrix[idx_patt-1];
      }
      else{
        idx_text += 1;
      }
    }
  }
  return match;

}

// int main(){

//   string text = "aabbccddcc";
//   string pattern = "cc";

//   int matc = KMPMatch(text, computeHMatrixForKMP(pattern), pattern);

// }

#endif
