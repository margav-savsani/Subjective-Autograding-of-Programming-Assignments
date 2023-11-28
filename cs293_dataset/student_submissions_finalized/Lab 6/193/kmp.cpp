#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int* HM = new int[pattern.length()]; //H matrix.
  HM[0] = 0;

  int lenofpattern = 0; //Subpattern length to be alloted to the H matrix.
  
  // Note here i can be the thought of as both an index and a length accounter.
  for(int i = 1; i < pattern.length();i++){ //Computing the HM[i] using the previous computed
    if(pattern[i] == pattern[lenofpattern]){ //IF the pattern matches again then we return HM[i-1] + 1 (which is lenofpattern+1)
      lenofpattern++;
      HM[i] = lenofpattern; //mismatch of this is equal to length
    }
    else{ //In this case the next text doesnt match
      if(lenofpattern != 0){ //means already a match has been found for a suffix 
        lenofpattern = HM[lenofpattern - 1]; 
        i--; //Decrementing the index so that it doesnt increase in the next loop.
      } 
      else{ //In this case none of the pattern has yet not matched and hence all distinct elems are appearing.
        HM[i] = 0; // case when pattern is a,b,c,d,e,f ....
      }
    }
  }
  return HM;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int indpat = 0; //The current index of the pattern being checked.
  int indtxt = 0; //The cuurent index of the text being checked.

  //Checking while the length of the patten being checked is less than or equal length of the text
  while(text.length() - indtxt >= pattern.length() - indpat){
    //If Index of pattern and text match then continue for next indices
    if(text[indtxt] == pattern[indpat]){
      indtxt++;
      indpat++;
    }
    //After incrementing the indices check whether the pattern is over
    if( indpat == pattern.length()) //If the whole pattern matches then just return the index
    {
      return (indtxt - indpat);
    }
    else if (indtxt < text.length() && pattern[indpat] != text[indtxt]){ 
      //Case when we need to shift the pattern.
      //Mismatch found
      if(indpat != 0){    //If the pattern has been matched earlier then.                                            
        indpat = hMatrix[indpat -1];
      }
      else{ //The pattern has not matched yet for any index of text
        indtxt++;
      }
    }
  }
}
#endif
