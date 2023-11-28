#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {

  int patternSize = pattern.size();
  if(patternSize == 0) return nullptr;

  int* hmatrix = new int[patternSize];
  //No proper prefix for first element of pattern
  hmatrix[0] = 0;

  for(int i = 1; i < patternSize; i++){
    // Length of prefix matched for one character behind
    int matchPrefixSuffix = hmatrix[i-1]; 

    while(true){
      //If no prefix for last character
      if(matchPrefixSuffix == 0){
        pattern[0] == pattern[i] ? hmatrix[i] = 1 : hmatrix[i] = 0;
        break;
      }

      else{
        //If last character matched, length of prefix matched is one more than for last character
        if(pattern[i] == pattern[matchPrefixSuffix]){
          hmatrix[i] = matchPrefixSuffix + 1;
          break;
        }

        else{
          //Find next largest prefix to match with
          matchPrefixSuffix = hmatrix[matchPrefixSuffix - 1];
        }
      }
    }
  }

  return hmatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int textLength = text.size();
  int patternLength = pattern.size();
  //patternHead->Index of text which is matched with first character of pattern
  //Current index of pattern to be matched 
  int patternHead = 0, indexPattern = 0; 
  while(patternHead < textLength - patternLength + 1){
    //Try to match pattern for current position of pattern in while loop
    while(true){
      //If end of pattern reached
      if(indexPattern == patternLength){
        return patternHead;
      }

      //If current character matched with text, check for next character
      if(toupper(text[patternHead + indexPattern]) == toupper(pattern[indexPattern])){
        indexPattern++;
      }

      //Jump pattern according to h matrix
      else{
        //If at first character of pattern
        if(indexPattern == 0){
          patternHead += 1;
          indexPattern = 0;
          break;
        }
        
        else{
            //If jump not possible, move pattern one step forward and start with first character
            if(indexPattern == hMatrix[indexPattern - 1]){
                patternHead++;
                indexPattern = 0;
                break;
            }
          patternHead += indexPattern - hMatrix[indexPattern - 1];
          indexPattern = hMatrix[indexPattern - 1];
          break;
        }
      }
    }
  }
  return -1;
}

#endif
