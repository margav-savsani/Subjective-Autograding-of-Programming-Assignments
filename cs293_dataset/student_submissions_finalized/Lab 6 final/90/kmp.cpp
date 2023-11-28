#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#include <algorithm>

using namespace std;

//Returns the failure matrix corresponding to the pattern given as input
int *Planner::computeHMatrixForKMP(string pattern) {

  //transforming the string pattern to entirely upper case
  //This is done in order to have case insensitivity.
  transform(pattern.begin(), pattern.end(), pattern.begin(), ::toupper);
  
  int* Hmatrix = new int[pattern.length()]; //Hmatrix of length same as that of pattern
  Hmatrix[0] = 0; //Initiating the starting 
  int len = 0; //length of the previous longest prefix suffix

  // Calculating failure values for all i = 1 to pattern.length()-1
  int k = 1; //Iterating index variable
  while(k<pattern.length()){
    if(pattern[k] == pattern[len]){
      //If the next char matches, then value of failure matrix
      //is 
      Hmatrix[k++] = (++len);
    }
    else{
      if(len!=0){
        //We don't increment k by 1 here!
        len = Hmatrix[len-1];
      }
      else{
        //when len!=0
        Hmatrix[k++]=0;
      }
    }
  }
  return Hmatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int M = pattern.length(),N = text.length();
  
  //transforming the string pattern and text to entirely upper case
  transform(pattern.begin(), pattern.end(), pattern.begin(), ::toupper);
  transform(text.begin(), text.end(), text.begin(), ::toupper);  
  
  int i = 0, j = 0; // i,j = index for text, index for pattern respectively
  while ((N - i) >= (M - j)){
      if (pattern[j] == text[i]){
        //Successful Match
          i++;
          j++;
      }

      if (j == M) {
        //Complete match
          return i-j;
      }

      // Unsuccessful match after j successful matches
      else if (i < N && pattern[j] != text[i]) {
          // Do not match failure matrix for 0...j-1 indices
          if (j != 0)
              j = hMatrix[j - 1];
          else
              i++;
      }
    }
    return -1;
  //returns -1 if not found, else returns index of position where the pattern has occured
}

#endif
