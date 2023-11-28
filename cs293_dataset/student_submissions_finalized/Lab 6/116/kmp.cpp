#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  //length of the longest prefix suffix found so far.
    int len=0;
    int n=pattern.size();
    //index at 0 is always 0
   int Hmatrix[n];
    Hmatrix[0]= 0;
    int i = 1;
	while (i < n) {
		if (pattern[i] == pattern[len]) {
			len++;
			Hmatrix[i] = len;
			i++;}
  return nullptr;
}

int Planner:: KMPMatch(string text, int *hMatrix, string pattern) {

 int l=strlen(text);
 int m= strlen(pattern);




	int i = 0; // index for txt[]
	int j = 0; // index for pat[]
	while ((l - i) >= (m - j)) {
		if (pattern[j] == text[i]) {
			j++;
			i++;


  return 0;
}

#endif
