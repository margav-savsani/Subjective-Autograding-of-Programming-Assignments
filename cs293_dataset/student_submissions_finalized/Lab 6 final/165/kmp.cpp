#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int len = 0;//length of previous longest suffix which is also a prefix
  int *lps;//hmatrix
  lps = new int [pattern.length()];
  lps[0] = 0;
  int i = 1;
  while(i<pattern.length()){
    if(tolower(pattern[i]) == tolower(pattern[len])){//case insensitive
      len++;
      lps[i] = len;
      i++;
    }
    else{
      if(len!=0)//if index 0 is not reached
        len = lps[len-1];//go to index stored in the previous lps index
      else{
        lps[i] = 0;//if index is 0
        i++;//update i
      }
    }
  }

  return lps;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  int i = 0,j=0;
  while(text.length()-i>=pattern.length()-j){//traverse the text
    if(tolower(pattern[j])==tolower(text[i])){//while pattern and text are same
      j++;
      i++;
    }
    if(j==pattern.length()){//if j reaches end, pattern is matched
      return i-j;
    }
    else if(i < text.length() && pattern[j]!=text[i]){//else
      if(j!=0)//if pattern end not reached
        j=hMatrix[j-1];//shift pattern on text with help of lps array
      else  
        i++;
    }
  }
  return -1;
}

#endif
