#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#include <vector>
#include "codes.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
	int * hMatrix = new int[pattern.length()];
	hMatrix[0] = 0;
	int len = 0, i = 1;
	while (i < pattern.length()){
		if(toupper(pattern[len]) == toupper(pattern[i])){
			len++;
			hMatrix[i] = len;
			i++;
		}

		else{
			if(len==0){
				hMatrix[i] = 0;
				i++;
			}
			else{
				len = hMatrix[len -1];
			}
		}

	}
	return hMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
	vector<int> match(0);
	int j=0, i=0;
	while(text.length()-i >= pattern.length()-j){
		if(j==pattern.length()){
			match.push_back(i-pattern.length());
			j=0;
		}
		else if(toupper(pattern[j]) == toupper(text[i])){
			i++;
			j++;
		}
		else if(j==0 || i==0){
			i++;
		}
		else if(toupper(pattern[j]) != toupper(text[i])){
			j = hMatrix[j-1];
		}
	}
	if(match.size() == 0) return -1;
	return match[0];
}
#endif
