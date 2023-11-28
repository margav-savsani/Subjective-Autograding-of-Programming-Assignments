#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  //length of the longest prefix suffix found so far.
  
  int n=pattern.size();
  //pattern size

  int Hmatrix[n];
  //Hmatrix to stores 

  Hmatrix[0]= 0;
  int i = 1;
  int lst =n-1;
	while (i < n) {
    int j=i;
    int len=0;
		while (pattern[j] == pattern[lst])
    { lst--;
      j--;
			len++;
			Hmatrix[i] = len;
			
    }
  }
  return Hmatrix;
  
}

int Planner:: KMPMatch(string text, int *hMatrix, string pattern) {

 int l = text.size();
 int m = pattern.size();


 int i = 0; // index for txt[]
 int j = 0; // index for pat[]
	while ((l - i) >= (m - j)) {
		if (pattern[j] == text[i]) {
			j++;
			i++;
    }

   return 0;
  }
}
#endif
