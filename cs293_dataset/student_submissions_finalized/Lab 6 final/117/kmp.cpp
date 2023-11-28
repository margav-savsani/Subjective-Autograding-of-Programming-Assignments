#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int* hArr = new int [pattern.length()];// h matrix
  hArr[0] = 0;
  int lengthOfPrefix=0;//harr of prev is used
  for(int i = 1; i < pattern.length();i++){
    while(true){
      if(tolower(pattern[i]) == tolower(pattern[lengthOfPrefix])){//case insensitive
        lengthOfPrefix++;
        hArr[i] = lengthOfPrefix;
        break;
      }
      else{
        if(lengthOfPrefix == 0){
          hArr[i] = 0;
          break;
        }
        else{
          lengthOfPrefix = hArr[lengthOfPrefix-1]; 
        }
      }
    }
  }



  return hArr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int index = 0,patternindex = 0;
  
  while(true){
    if(tolower(text[index])==tolower(pattern[patternindex])){// letter match
      if(patternindex == pattern.length()-1){// full pattern matched
        return index-patternindex;
        index++;
        patternindex = 0;
        continue;
      }
      else{//not full pattern match
        patternindex++;
        index++;
        continue;
      }
      
    }
    else{//letter not match
      if(patternindex == 0){//first letter of pattern not matching
        index++;
      }
      else{// i'th letter mismatch
        patternindex = hMatrix[patternindex];
      }

    }
    if(index >= text.length()) break;
  }
  return -1;
}

#endif
