#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  
  if(pattern.length()==0){return nullptr;}

  //matrix would be of the size of length of the pattern
  int *h = new int[pattern.length()];
  
  //to compute hmatrix according to the method given in prof. naveen garg's slides , we
  //would first have to create a text that is same as the pattern given but just the
  //first letter of the pattern is replaced by some character that we are sure would not appear
  //in the given text so let's use $ in our case 
  string text = pattern;
  text[0]= '$';

  //i goes from i to pattern.length();
  int i=1;
  
  //this variable stores the index where the 0th index of pattern is at
  //wrt the text string
  int start=1;

  //to make use in the loop
  bool just_shifted=false;
  
  //now let us create a for loop that calculates the values to be stored in the matrix
  while(i<=pattern.length()){

    //if the pattern matches then the value of h[i-1] needs to be updated accordingly
    if(pattern[i-start]==text[i]){
      if(start==i){
        h[i-1]==1;
        i++;
        continue;
      }
      else{
        if(just_shifted){
          //if it has been shifted then this definition holds else the one in the 
          //else condition would hold
          h[i-1]=h[h[i-2]]+1;
          just_shifted = false;
        }
        else{
          h[i-1]=h[i-2]+1;
          i++;
        }
        continue;
      }
    }

    //if pattern does not match then start has to be updated accordingly
    else{
      if(start==i){
        i++;
        start++;
        h[i-1]=0;
      }
      else{
        start=start+h[i-1]-h[h[i-2]-1];
        just_shifted = true;
      }
    }
  }

  return h;
}

//for new assuming we have to return the number of occurences of the pattern in the text
int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  
  //this variable stores the number of occurences of the pattern found in the text
  int occurences = 0;
  long long int i = 0;
  int nmatch=0;
  int pattern_start_at=0; 

  // we would have to initialize a variable to store the number of chars matching and when it 
  // becomes equal to the pattern inc.occurence by 1 and shift by h[pattern.length()-1] , else if
  // mismatch occurs before the pattern fully matches shift the pattern by i-h(i-1) if mismatch 
  // occured at i+1 
  while(i<text.length()){
    if(nmatch==pattern.length()){
      occurences+=1;
      pattern_start_at+=hMatrix[pattern.length()-1];
    }
  }

  return occurences;
}

#endif
