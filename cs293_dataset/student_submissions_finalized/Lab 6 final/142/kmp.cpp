#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;
int i = 0;

int *Planner::computeHMatrixForKMP(string pattern) {
  int M =pattern.length();
  int *hMatrix;
//   int(pattern[i]);
  // for(int i = 0; i < strlen(pattern); i++){
  //   hMatrix[i] = ;
  // }
    // length of the previous longest prefix suffix
    int len = 0;
    hMatrix[0] = 0; // lps[0] is always 0
 
    // the loop calculates hMatrix[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pattern[i] == pattern[len]) {
            len++;
            hMatrix[i] = len;
            i++;
        }
        else
        {
            if (len != 0) 
            {
                len = hMatrix[len - 1];
 
                // we do not increment i here
            }
            else // if (len == 0)
            {
                hMatrix[i] = 0;
                i++;
            }
        }
    }
  return hMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  // void KMPSearch(char* pat, char* txt)

    int M = pattern.length();
    int N = text.length();
 
    // create hMatrix[] that will hold the longest prefix suffix values for pattern
 
    // Preprocess the pattern (calculate hMatrix[] array)
    hMatrix = computeHMatrixForKMP(pattern);
 
    int i = 0; // index for text[]
    int j = 0; // index for pattern[]
    while ((N - i) >= (M - j)) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }
 
        if (j == M) {
            // Found pattern at index  i - j
            j = hMatrix[j - 1];
        }
 
        // mismatch after j matches
        else if (i < N && pattern[j] != text[i]) {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = hMatrix[j - 1];
            else
                i = i + 1;
        }
    }
    return i;
}
//////////////////////////////////////////////////////////////////
  // int pattern_length = strlen(pattern);
  // int text_length = strlen(text);
  // while((text_length-i)>= (pattern_length-j)){
  //   if(pattern[j]==text[i]){
  //     j++;
  //     i++;
  //   }
  //   if(j == pattern_length){
  //     j = 
  //   }
  // }
  // while(i == strlen(pattern))return i;
  // computeHMatrixForKMP(text,hMatrix,pattern);
  // while(!strcmp(text[i],pattern[i])){
  //   i++;
  // }
  // i += i - hMatrix[i];
  // KMPMatch(text[i],hMatrix,pattern);
  // return i;


#endif
// #ifndef KMP_CPP
// #define KMP_CPP

// #ifndef PLANNER_H
// #include "planner.h"
// #endif

// using namespace std;

// int *Planner::computeHMatrixForKMP(string pattern) {

//   return nullptr;
// }

// int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

//   return 0;
// }

// #endif
