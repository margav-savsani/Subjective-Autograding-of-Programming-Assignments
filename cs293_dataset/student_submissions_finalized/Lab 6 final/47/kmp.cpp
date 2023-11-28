#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif
#include<bits/stdc++.h>
using namespace std;


// MADE BOTH PATTERN case insensitive
int *Planner :: computeHMatrixForKMP(string pattern) { // to get array
  
  transform(pattern.begin(), pattern.end(), pattern.begin(), ::tolower);// convert pattern into lowerstring
  int n = pattern.length();
  int *arr;
  arr = new int[n];
  arr[0] = 0; // initialize initial index of array to "0"
  int checker = 0;
  
  for( int index =1 ; index < n; index++){ // starts from index '0'
  
  	while ( checker > 0 && pattern[checker] != pattern[index] ){ // if both doesn't match do untill u get first element or when they are equal
  	
  		checker = arr[checker];
  	}
  	
  	if ( pattern[checker] == pattern[index] ) { // next level check
  	
  		checker = checker+1;
  	}
  	
  	arr[index] = checker; // equate arr[index] to checker.
  }
  return arr;
  
}
 

// MADE TEXT AND PATTERN CASE INSESTITIVE - BONUS 2 MARKS.

int Planner :: KMPMatch(string text, int *hMatrix, string pattern) { // to get mathched string index.


  transform(pattern.begin(), pattern.end(), pattern.begin(), ::tolower);// convert pattern into lower case
  transform(text.begin(), text.end(), text.begin(), ::tolower);// convert text into lower case
  int n = pattern.length();
  int m = text.length();
  int *Matrix = computeHMatrixForKMP(pattern);// find the hmatrix of the pattern 
  int checker = 0;// repeat the process same as pattern.
  
  for( int index =0 ; index < m; index++){ // start with index '0'
  
  	while ( checker > 0 && pattern[checker] != text[index] ){// if both doesn't match do untill u get first element or when they are equal
  	
  		checker = Matrix[checker];
  	}
  	
  	if ( pattern[checker] == text[index] ) { //next level check
  	
  		checker = checker+1;
  	}
  	
  	if ( checker == n ) { // found the pattern
  	
  		return index+1-n;
  	}
  	
  }
  
  
  return -1;
}


#endif
