#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *computeHMatrixForKMP2(string pattern){

  int len = pattern.length();
  
  int *hmatrix;
  hmatrix = new int[len];

  for(int i=0; i<len; i++) hmatrix[i] = 0;

  // Note that hmatrix[0] must be 0. 
  // Hence i will start from index 1.
  hmatrix[0] = 0;

  for(int i=1; i<len; i++){
    int pre_value = hmatrix[i-1];
    int curr_char = pattern[i];
    

    while(true){

      // Base Case
      if(pre_value == 0){
        if( curr_char == pattern[0]) hmatrix[i] = 1;
        else hmatrix[i] = 0;

        break;
      }


      if( curr_char == pattern[pre_value] ){
        hmatrix[i] = pre_value + 1;
        break;
      }

      pre_value = hmatrix[pre_value - 1];
    }
    

  }

  // // Remove this part after verification
  // for(int i=0; i<len; i++) cout << hmatrix[i];
  // cout << endl;
  for(int i=0; i<len; i++) cout << pattern[i];
  cout << endl;







  return hmatrix;

}

int KMPMatch2(string text, int *hMatrix, string pattern){

  // TODO
  int i = 0;
  int j = -1;

  int lenText = text.length();
  int lenPattern = pattern.length(); 

  while(true){
    
    // Base cases
    if( i >= lenText+1){
      // No match found
      return -1;
    }
    else if( j >= lenPattern - 1 ){
      // Match found
      
      // Remove it later on
      for(int k=0; k<lenText; k++) cout << text[k];
      cout << endl;
      for(int k=0; k<lenText; k++){
        if(k >= i - lenPattern && k <= i - 1) cout << "*";
        else cout << " ";
      }
      cout << endl;


      return (i - lenPattern);
    }


    // Main Body
    if( text[i] == pattern[j+1] ){
      i++;
      j++;
    }
    else if( j == -1 ){
      // not matched and j is at starting position, so just move i
      i++;
    }
    else{
      // not matched but j is not at starting position, so move j backwards.
      j = hMatrix[j] - 1;
    }

  }

  return 0;
}




int *Planner::computeHMatrixForKMP(string pattern) {

  return computeHMatrixForKMP2(pattern);
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  return KMPMatch2(text, hMatrix, pattern); 
}

#endif
