#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) { // Order ( m ) => m is lenght of the pattern  
  // h[i] => computes the maximum length of the proper prefix which is also a suffix of pattern[0...i]
  int* h = new int[pattern.length()] ; 
  h[0] = 0 ; 
  int last = 0 ; 
  for ( int i =1 ; i < pattern.length() ; i++ ) {
      while ( last > 0 && pattern[i] != pattern[last] )  { 
         last = h[last] ; 
      }
      if ( pattern[i] == pattern[last] )  last ++ ; 
      pattern[i] = last ;  
  }
  return h ;
}


int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int i = 0 ; 
  int match = 0 ; // stores the number of element matched from 0 to n-1 index and nth index is not match 
  while ( i < text.length() )  {
     while( match < pattern.length() && text[i+match] == pattern[match] )  match ++ ;
     if ( match == pattern.length() ) return i ; 
     i += 1 + match - hMatrix[match] ; 
     match = hMatrix[match] ;
  }
  return -1 ;
}

#endif
