#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {

 int m=pattern.length();
  int* H = new int[m];
  int j=0;
  for (int k=0; k<m; k++) H[k]=0;     // initialized H to zero vector
  
  for (int i=1; i<m; i++)
 	{
 		while (j>=0 && pattern[j]!=pattern[i])
 		{
 			if (j-1>=0) j=H[j-1];
 			else j=-1;
 		}
 		
 		j++;
 		H[i]=j;
 	}
 	return H;
  // return nullptr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  int numOcc=0;
  int n=text.length();
  int m=pattern.length();
  int j=0;
  for (int i=0; i<n; i++)
  {
  	while(j>=0 && text[i]!=pattern[j])
  	{
  		if (j>0) j=hMatrix[j-1];
  		else j=-1;
  	}
  	j++;
  	if (j==m)
  	{
  		j=hMatrix[m-1];
  		numOcc++;
  	}
  }
  return numOcc;
  return 0;
}

#endif
