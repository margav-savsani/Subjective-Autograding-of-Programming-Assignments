#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int m = pattern.size();
  int h[m];
  h[0] = 0;

  return nullptr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int n = text.size();
  int m = pattern.size();
  int i = 0;
  int j = 0;
  while(m-1 < n-i){
    int ini = j;
    for(; ini < m; ini++){
      if(text[i+j] == pattern[j]) continue;
      else break;
    }
    if(ini == m) return 0;
    else{
      j = hMatrix[ini-1];
      i = i+ini-j;
    }
  }
  return -1;
}

// int main(){
//   string s, p;
//   s = "aabacaabaabdef";
//   p = "aabaab";
//   int h[6];
//   h[0] = 0;
//   h[1] = 1;
//   h[2] = 0;
//   h[3] = 1;
//   h[4] = 2;
//   h[5] = 3;
// }

#endif
