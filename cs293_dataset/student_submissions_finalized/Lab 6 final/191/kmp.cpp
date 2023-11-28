#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#include<cstring>

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
	
	int pattern_length = pattern.length(); // length of the pattern
	if(pattern_length == 0)
		return nullptr;
	int *h = new int[pattern_length]; // the HMatrix we want to construct
	h[0]=0; // the obvious value for index 0
	for(int i=1;i<pattern_length;i++){
		int j = h[i-1]; //finding hMatrix recursively
		while(true){
			if(pattern[j] == pattern[i]){
				h[i] = j+1; //updating h[i] 
				break;
			}
			
			else if(j==0){
				h[i]=0;
				break;
			}
			
			else{
				j = h[j-1]; // recursively going downwards in the index
			}
		}
	}
	
	return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

	if(hMatrix == nullptr){
		return -1;
	}	
	int j=0;
	int i=0;
	int pattern_length = pattern.length();
	int text_length = text.length(); // text length
	while(true){
		if(toupper(text[i])==toupper(pattern[j])){ //condition for character equality in text and pattern strings 
			i++;
			j++;
		}
		else{
			if(j==0)
				i++;
			j = hMatrix[j-1];
		}
		
		if(j==pattern_length){
			return i-j;
			//cout<<i-j <<endl;
			//j = hMatrix[j-1];
		}
		
		if(i == text_length){
			break;
		}
	}
	return -1;
}

#endif
