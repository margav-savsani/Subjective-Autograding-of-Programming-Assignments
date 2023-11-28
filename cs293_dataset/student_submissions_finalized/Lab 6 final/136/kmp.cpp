#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;


int* computeHMatrixForKMP(string pattern) {
  int length=pattern.length();
  int* p=new int[length];
  p[0]=0;
  for(int j=1;j<length;j++){  
    int a=j-1;
    int next=pattern[j];
    while(true){
      if(a==-1){
        if(next==pattern[0]){
            p[j]=1;
        }
        else{
            p[j]=0;
        }
        break;
      }
      if(next==pattern[p[a]]){
        p[j]=p[a]+1;
        break;
      }
      a=p[a]-1;
    }
  }
  return p;
}

int KMPMatch(string text, int *hMatrix, string pattern) {
  int p = pattern.length();
  int q = text.length();
  int i = 0; 
  int j = 0; 
  while ((q - i) >= (p - j)) {
    if (pattern[j] == text[i]) {
      j++;
      i++;
    }
    if (j == p) {
      return i-j;
      j = hMatrix[j - 1];
    }
    else if (i < q && pattern[j] != text[i]) {
      if (j != 0)
        j = hMatrix[j - 1];
      else
        i = i + 1;
    }
  }
}

#endif
