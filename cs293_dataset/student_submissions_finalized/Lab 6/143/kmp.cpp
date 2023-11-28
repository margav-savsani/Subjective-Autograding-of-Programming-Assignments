#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern){
  int *h;
  int l = pattern.length();
  h = new int[l];
  h[0]=0;
  int i =1;
  int j = 0;
  while (i<l){
    if (pattern[i]==pattern[j]){
      h[i] = h[i-1] + 1;
      i++;
      j++;
    }
    else{
      j =  h[h[i-1]-1];
      if (pattern[i]==pattern[j]){
        h[i] = h[h[i-1]-1]+1;
        i++;
        j++;

      }
      else{
        h[i] = 0;
        i++;
      }
    }
  }
  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int i = 0;
  int j = 0;
  int count = -1;
  while(i<text.length()){
    if(text[i]==pattern[j]){
        if(j == pattern.length()-1){
            count++;
            j=0;
            i++;
            i = i-hMatrix[pattern.length()-1];
        }
        else{
            i++;
            j++;
        }
    }
    else if(j!=0){
        if(i==text.length()-1){
            break;
        }
        j = j-1 - hMatrix[j-1];

    }
    else{
        if(text[i]!=pattern[0]){
            i++;
        }
    }
  }
  return count;

}

#endif
