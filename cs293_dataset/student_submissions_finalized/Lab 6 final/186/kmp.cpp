#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

// Computing H_MATRIX of given pattern for KMP Algortihm 
int *Planner::computeHMatrixForKMP(string pattern) {

  int match = 0, i = 1; 
  int *H_Matrix = new int[pattern.length()];
  H_Matrix[0] = 0;       // H Matrix of 0 is always 0

  for(int k = 0; k < pattern.length(); k++){      // FOR CASE INSENSITIVE KMP
    pattern.at(k) = toupper(pattern.at(k));
  }

  while(i < pattern.length()){           
    if(pattern[i] == pattern[match]){         // If pattern matches with its prefix
      match++;
      H_Matrix[i] = match;                    // Set H matrix value
      i++;                                    // Traverse further
    }
    else{                                     // Else if it does not match
      if(match == 0){                         // If match is zero, set H matrix to zero and traverse further
        H_Matrix[i] = 0;
        i++;
      }
      else{      // else Recursively call function till match becomes zero
        match = H_Matrix[match-1];
      }
    }
  }

  //printing H_Matrix
  /*
  cout << "H MATRIX\n";
  for(int p = 0; p < pattern.length(); p++){
    cout << H_Matrix[p] << " ";
  }
  cout << endl;
  */

  return H_Matrix;
  
}

// Finding first occurence of pattern in text
int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int i = 0;                // index for traversing through text
  int j = 0;                // index for traversing through pattern
  int found = -1;           // first index of pattern found
  int textlen = text.length(), patlen = pattern.length();    // length of text and pattern

  for(int k = 0; k < textlen; k++){         // FOR CASE INSENSITIVE KMP 
    text.at(k) = toupper(text.at(k));
  }
  for(int k = 0; k < patlen; k++){          // FOR CASE INSENSITIVE KMP
    pattern.at(k) = toupper(pattern.at(k));
  }

  while ((textlen - i) >= (patlen - j)) {
        if (pattern[j] == text[i]) {  // Traverse forward if match is found
            j++;
            i++;
        }
 
        if (j == patlen) {            // set found to first occurence
            found = i - j;
            j = hMatrix[j - 1];       // return if word is found to get first occurence
            return found;
        }
 
        // If Mismatch occured after j matches are done
        else if (i < textlen && pattern[j] != text[i]) {
            if (j != 0)
                j = hMatrix[j - 1];   // set j to hMatrix of j-1 and start from there of j is not zero
            else
                i = i + 1;            // else increment i and traverse further 
        }
    }

  //cout << "RETURNED INDEX : "  << found  << endl;

  return found;

}

#endif
