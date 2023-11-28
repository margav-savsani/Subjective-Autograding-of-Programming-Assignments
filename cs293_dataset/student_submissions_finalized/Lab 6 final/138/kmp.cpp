#ifndef KMP_CPP
#define KMP_CPP
#include <string>
using namespace std;
#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {

  // i is index of pattern
  //initialising length to 0
  // and the toral numver of elements in matrix to pattern.length()
  int leng = 0,i=1,total=pattern.length();

  // this is the matrix which will be returned
  int* HMatrix;
  HMatrix=new int[pattern.length()];
  HMatrix[0] = 0; // HMatrix[0] is set to 0

  // while loop for computing the Hmatrix
  while (1) {
    //breaking the loop
    if(i >= total){
      break;
    }

    //SEARCH IS MADE CASE INSENSITIVE BY CONVERTING ALL LETTERS TO LOWER CASE
    // in case of mismatch
    if (tolower(pattern[i]) != tolower(pattern[leng])) {
      switch (leng){
        case 0:
          //if length is 0 i gets incremented and h matrix for that i is set to 0
          HMatrix[i] = 0;
          i=i+1;
          break;
        default:
          //using KMP like shift finding longest prefix which matches with the suffix
          leng = HMatrix[leng - 1];
      }  
    }

    // in case of match
    else {
      //length gets incremented and h matrix for that i is filled
      leng=leng+1;
      HMatrix[i] = leng;
      i=i+1;
    }
  }
  return HMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  // i is index for text and j is index of pattern
  int i = 0,j=0; 
  while (1) {

    //condition for breaking of loop that is match is not found
    if((text.length() - i) < (pattern.length() - j)){
      break;
    }

    //SEARCH IS MADE CASE INSENSITIVE BY CONVERTING ALL LETTERS TO LOWER CASE
    // in case match is found
    if (tolower(pattern[j]) == tolower(text[i])) {
      //increment i and j
      j=j+1;
      i=i+1;
    }

    //if full match is found
    if (j == pattern.length()) {
      return i-j;
    }

    // in case of mismatch and no further match with the pattern i of text is incremented
    if ((i < text.length() && tolower(pattern[j]) != tolower(text[i]))&&(j == 0)){
      i = i + 1;
    }
    //in case of mismatch j gets shifted with the use of hmatrix
    else if (i < text.length() && tolower(pattern[j]) != tolower(text[i])){
      j = hMatrix[j - 1];
    }    
  }  
  return -1;
}


#endif




