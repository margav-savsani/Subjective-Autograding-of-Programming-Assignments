#ifndef KMP_CPP
#define KMP_CPP
#include<algorithm>

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

// CONSTRUCTING the failure matrix
// following naveen garg's lecture.
int *Planner::computeHMatrixForKMP(string pattern) {
  transform(pattern.begin(), pattern.end(), pattern.begin(), ::toupper);
  int *h=new int[pattern.length()];
  h[0]=0;
  // point representing the pattern moving to fill h matrix
  int point =0;
  // representing index whose htable is being filled
  int index=1;

  while(index<pattern.length()){
      // if match is found its  simply has one more match than its prev value 
        if (pattern[index]==pattern[point]){
            point++;
            h[index]=point;
            index++;
        }
        // if match don't found moving the hmatrix of match to again start matching
        else if (point !=0){
            point = h[point-1];
        }

        // if point reaches zero then setting its h value 0 and moving ahead
        else if (point == 0){
             h[index]=0;
             index++;
        }
  }
  return h;
}

// returning index in text of first pattern match
// following naveen garg's lecture
int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  transform(pattern.begin(), pattern.end(), pattern.begin(), ::toupper);
  transform(text.begin(), text.end(), text.begin(), ::toupper);
  // pattern index moving left to right matching with text
  int pat_index=0;
  // representing the text index.
  int text_index=0;

  while (!(text.length()-text_index<pattern.length()-pat_index))
  {
      // if match is found moving to next index for match
     if (pattern[pat_index]==text[text_index]){
          text_index++;
          pat_index++;
     }
     // this will mean pattern_length of text and pattern are already matched
     // .i.e, just send the answer match is already found. 
     if (pat_index==pattern.length()){
        return text_index-pattern.length();
     }

     // if there is no match moving the pat_index acc. to failure matrix.
     // if pat_index reaches zero means no match substring so moving simply
     // to next index and starting from start.
     else if(text_index < text.length() && pattern[pat_index]!=text[text_index]){
         if (pat_index!=0)
          pat_index= hMatrix[pat_index-1];
         else{
           text_index++;
         }
     }
     
  }
  // finally return -1 if no match is found i.e, no return till now.
  return -1;
}

#endif
