#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;
 bool function(string pattern,int j,int m)
{
  bool k = false;
  for(int i = j;i<=m;i++){
    if(pattern[i-j] != pattern[i]){
      k = true;
    }
  }
  return k;
} 
int *Planner::computeHMatrixForKMP(string pattern) {
   int m = pattern.size();
  int* array = new int[m];
  array[0] = 0;
  if(pattern[0]==pattern[1]){
    array[1] = 1;
  }
  else array[1] = 0;
  for (int j = 2;j<m; j++){
    for(int i= 1;i<=j;i++)
    {
      if(pattern[0]==pattern[i]){
        bool b = function(pattern,i,j);
        if(!b){
          array[j]= j-i+1;
          break;
        }
      }
    }
  } 

  
  return array;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
 int lenText = text.length();
  int lenPat = pattern.length();

  int indexInText, indexInPat;

  indexInText = indexInPat = 0;

  while ((lenText - indexInText) >= (lenPat - indexInPat)) {
    if (pattern.at(indexInPat) == text.at(indexInText)) {
      indexInPat ++;
      indexInText ++;
    }
    if (indexInPat == lenPat) {
      int startMatch = indexInText - lenPat;
      logFile << "Found match at index " << startMatch << endl;
      return startMatch;
    }
    else {
      if ((indexInText < lenText) && (pattern.at(indexInPat) != text.at(indexInText))) {
	if (indexInPat != 0) {
	  indexInPat = hMatrix[indexInPat - 1];
	}
	else {
	  indexInText = indexInText + 1;
	}
      }
    }
  }
  return -1;
}

#endif
