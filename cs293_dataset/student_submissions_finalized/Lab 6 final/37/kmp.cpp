#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;
int count_sim(string text,string pattern,int i){  //counting no of matching characters with the pattern from the start of the pattern
  int j=0;
  for(j;j<pattern.length();j++){
    if(text[i+j]!=pattern[j]) return j;
  }
  return pattern.length();
}

int *Planner::computeHMatrixForKMP(string pattern) {
  int * Hmatrix = new int[pattern.length()];
  int j=0,i=1;
  Hmatrix[0]=0;
  while ( i < pattern.length()){
    if (pattern[i] == pattern[j]){   //since j is the length of suffix to i-1 element which matches a prefix of pattern, if pattern[i] == pattern[j] holds                                      
      j++;                    //suffix of i-1 + ith element will match with prefix of pattern with length j+1.i.e Hmatrix[i]=j+1
      Hmatrix[i] = j;   
      i++;
    }

    else if(j != 0){     // if p[i] and p[j] doesnt match we have to check if a suffix of the previous suffix(previous j length prefix) + ith element 
                      //works as suffix for pattern upto element i as well as prefix.
      j=Hmatrix[j-1];
    }

    else{
      Hmatrix[i]=0;   //after repeatedly taking suffixes of suffixes eventually j becomes zero ,i.e no suffix works.
      i++;

    }

  }

  return Hmatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int i=0,j;
  while(i< text.length()){
    if(text[i]==pattern[0]){
      j=count_sim(text,pattern,i);
      if(j == pattern.length()) return i;
      i+=(j-hMatrix[j]);
    }
    else i++;


  }
  return -1;
}

#endif
